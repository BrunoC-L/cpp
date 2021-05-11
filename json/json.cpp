#include "json.h"

JSON::JSON(const std::string& json) {
	self = json;
	parse(self);
}

JSON::JSON() {
	self = "{}";
	parse(self);
}

JSON::JSON(std::string&& json) {
	std::swap(self, json);
	parse(self);
}

JSON::JSON(const std::string& json, std::string propertyName) {
	this->propertyName = propertyName;
	self = json;
	parse(self);
}

JSON::JSON(JSON&& other) {
	std::swap(children, other.children);
	std::swap(indices, other.indices);
	std::swap(self, other.self);
	type = other.type;
	defined = other.defined;
}

void JSON::operator=(const JSON& other) {
	type = other.type;
	self = other.self;
	indices = other.indices;
	children = other.children;
	defined = true;
}

JSON JSON::getInactive(std::string propertyName) {
	JSON json;
	json.defined = false;
	json.propertyName = propertyName;
	return std::move(json);
}

JSON& JSON::operator[](std::string propertyName) {
	if (!defined)
		throw JSONException("Attempting to access inactive property");
	if (type != Primitives::OBJECT)
		throw JSONException("this JSON is either an array, string or number");
	try {
		auto index = indices.at(propertyName);
		return children[index];
	}
	catch (...) {
		children.emplace_back(std::move(getInactive(propertyName)));
		indices.insert(make_pair(propertyName, children.size() - 1));
		return children[indices.at(propertyName)];
	}
};

const JSON& JSON::get(std::string propertyName) const {
	if (!defined)
		throw JSONException("Attempting to access inactive property");
	if (type != Primitives::OBJECT)
		throw JSONException("this JSON is either an array, string or number");
	auto index = indices.at(propertyName);
	return children[index];
}

JSON& JSON::operator[](int x) {
	if (!defined)
		throw JSONException("Attempting to access inactive property");
	if (type != Primitives::ARRAY)
		throw JSONException("this JSON is not an array");
	return children[x];
}

const JSON& JSON::get(int x) const {
	if (!defined)
		throw JSONException("Attempting to access inactive property");
	if (type != Primitives::ARRAY)
		throw JSONException("this JSON is not an array");
	return children[x];
}

void JSON::push(JSON&& json) {
	if (type != Primitives::ARRAY)
		throw JSONException("this JSON object is not an array");
	this->children.emplace_back(json);
}

void JSON::push(std::string str) {
	push(JSON(str));
}

std::string JSON::asString() const {
	switch (type) {
	case Primitives::ARRAY:
		return arrayAsString();
	case Primitives::OBJECT:
		return objectAsString();
	case Primitives::STRING:
	case Primitives::NUMBER:
	default:
		return self;
	}
}

std::string JSON::arrayAsString() const {
	std::string out = "[";
	bool hasChildren = false;
	for (const auto& json : children) {
		if (!json.defined)
			continue;
		hasChildren = true;
		switch (json.type) {
		case Primitives::STRING:
			out += '"' + json.asString() + '"';
			break;
		default:
			out += json.asString();
			break;
		}
		out += ", ";
	}
	if (hasChildren)
		out.erase(out.length() - 2, out.length());
	out += ']';
	return out;
}

std::string JSON::objectAsString() const {
	std::string out = "{";
	bool hasChildren = false;
	for (const auto& pair : indices) {
		const JSON& json = children[pair.second];
		if (!json.defined)
			continue;
		hasChildren = true;
		switch (json.type) {
		case Primitives::STRING:
			out += '"' + pair.first + "\" : " + '"' + json.asString() + '"';
			break;
		default:
			out += '"' + pair.first + "\" : " + json.asString();
			break;
		}
		out += ", ";
	}
	if (hasChildren)
		out.erase(out.length() - 2, out.length());
	out += '}';
	return out;
}

bool JSON::asBool() const {
	try {
		return stod(self);
	}
	catch (...) {}
	return self != "{}" && self != "[]" && self != "" && self != "undefined" && self != "null" && self != "false";
};

int JSON::asInt() const {
	return stoi(self);
};

double JSON::asDouble() const {
	return stod(self);
};

void JSON::operator=(const std::string& other) {
	*this = JSON(other);
}

void JSON::setType(Primitives type) {
	this->type = type;
}

void JSON::setSelf(std::string str) {
	self = str;
}

void JSON::parse(const std::string& str) {
	index = 1;
	switch (self[0]) {
		case '{':
			setType(Primitives::OBJECT);
			parseJSON();
			break;
		case '[':
			setType(Primitives::ARRAY);
			parseArray();
			break;
		case '\'':
		case '"':
			self.erase(0, 1);
			if (self[self.length() - 1] == '\'' || self[self.length() - 1] == '"')
				self.erase(self.length() - 1);
			setSelf(self);
			setType(Primitives::STRING);
			break;
		default:
			setType(Primitives::NUMBER);
			break;
	}
}

void JSON::parseJSON() {
	parseSpaces();
	while (index < self.length() - 1) {
		bool inString = false;
		std::string propertyName = "";
		while (index < self.length()) {
			char c = self[index];
			if (c == '\'' || c == '"')
				if (inString)
					break;
				else
					inString = true;
			else if (inString)
				propertyName += c;
			++index;
		}
		if (!inString || propertyName.length() == 0)
			throw JSONException(("No property name in json while parsing " + self).c_str());
		inString = false;
		++index;
		bool found = false;
		parseSpaces();
		if (self[index] != ':')
			throw JSONException(("could not find ':' associated with \"" + propertyName + "\" in " + self).c_str());
		++index;
		parseSpaces();
		found = false;
		char next = self[index];
		std::string buffer = "";
		std::vector<char> stack;
		switch (next) {
		case '[':
		case '{':
			buffer = parseJSONOrArray();
			break;
		case '\'':
		case '"':
			buffer = "'";
			++index;
			while (index < self.length()) {
				char c = self[index];
				buffer += c;
				if (c == '\'' || c == '"')
					break;
				++index;
			}
			++index;
			break;
		default:
			while (index < self.length()) {
				char c = self[index];
				if (c != ' ' && c != ',' && c != '}')
					buffer += c;
				else
					break;
				++index;
			}
			break;
		}
		if (indices.find(propertyName) != indices.end())
			throw JSONException("Duplicated property name " + propertyName);
		children.emplace_back(buffer, propertyName);
		indices.insert(make_pair(propertyName, children.size() - 1));
		parseSpaces();
		if (self[index] == '}')
			break;
		else if (self[index] == ',')
			continue;
		else {
			std::cout << self;
			throw JSONException("no stop character found after property: " + propertyName + " in " + self);
		}
	}
}

void JSON::parseArray() {
	while (index < self.length()) {
		parseSpaces();
		if (self[index] == ']')
			break;
		children.emplace_back(std::move(readElement()));
		parseSpaces();
		if (self[index] != ',')
			break;
		++index;
		parseSpaces();
	}
}

JSON JSON::readElement() {
	if (self[index] == '\'' || self[index] == '"')
		return readString();
	else if (self[index] == '{' || self[index] == '[')
		return readJSONOrArray();
	else
		return readNumber();
}

JSON JSON::readString() {
	std::string buffer = "\"";
	++index;
	while (index < self.length()) {
		char c = self[index];
		if (c == '\'')
			c = self[index] = '"';
		buffer += c;
		++index;
		if (c == '"')
			break;
	}
	return JSON(buffer);
}

JSON JSON::readNumber() {
	std::string buffer = "";
	while (index < self.length()) {
		char c = self[index];
		switch (c) {
		case ',':
		case ' ':
			return JSON(buffer);
		}
		buffer += c;
		++index;
	}
	return JSON(buffer);
}

JSON JSON::readJSONOrArray() {
	return JSON(parseJSONOrArray());
}

std::string JSON::parseJSONOrArray() {
	std::string buffer = "";
	std::vector<char> stack;
	while (index <= self.length()) {
		char c = self[index];
		++index;
		buffer += c;
		switch (c) {
		case '{':
		case '[':
			stack.push_back(c);
			break;
		case '}':
			if (stack.back() == '{')
				stack.pop_back();
			break;
		case ']':
			if (stack.back() == '[')
				stack.pop_back();
			break;
		case '\'':
		case '"':
			if (stack.back() == '\'' || stack.back() == '"')
				stack.pop_back();
			else
				stack.push_back(c);
			break;
		}
		if (stack.size() == 0)
			break;
	}
	return buffer;
}

void JSON::parseSpaces() {
	while (index < self.length()) {
		char c = self[index];
		if (c != ' ' && c != '\n' && c != '\t')
			break;
		++index;
	}
}
