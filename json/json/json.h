#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class JSONException : public std::exception {
public:
	JSONException(std::string msg) : std::exception(msg.c_str()) {}
	JSONException() : std::exception() {}
};

enum class Primitives { STRING, NUMBER, ARRAY, OBJECT };

class JSON {
private:
	unsigned index;
	std::string self;
	Primitives type;
	bool defined = true;

	std::string _arrayAsString(std::string tabulation, int indent, bool replaceEscapeSequences) const;
	std::string _objectAsString(std::string tabulation, int indent, bool replaceEscapeSequences) const;
	std::string _asString(std::string tabulation, int indent, bool replaceEscapeSequences) const;
	std::string replaceEscapeSequences() const;

	void parse(const std::string& str);
	void parseJSON();
	void parseArray();
	JSON readElement();
	JSON readString();
	JSON readNumber();
	JSON readJSONOrArray();
	std::string parseJSONOrArray();
	void parseSpaces();
	JSON getInactive(std::string propertyName);
	std::string propertyName;
	std::vector<std::string> properties;
	std::vector<JSON> children;
	void setType(Primitives type);
	void setSelf(std::string str);
	void assertType(Primitives type) const;
	bool isNumber() const;
	JSON(const std::string& json, std::string propertyName);
	const std::string& getName() const;
public:

	// following the rule of 0
	JSON(): JSON("{}") {}
	JSON(const JSON&) = default;
	JSON& operator=(const JSON&) = default;
	JSON(JSON&&) = default;
	JSON& operator=(JSON&&) = default;
	~JSON() = default;

	// other constructors

	JSON(std::string&& json);
	JSON(const std::string& json);
	JSON& operator=(const std::string& other);

	// manipulations

	void reserve(int size);

	std::vector<std::string>::const_iterator find(const std::string& propertyName) const;

	const JSON& at(const std::string& propertyName) const;
	const JSON& at(int x) const;
	JSON& operator[](const std::string& propertyName);
	JSON& operator[](int x);

	void push(JSON&& json);
	void push(const JSON& json);
	void push(const std::string& str);

	// views

	unsigned size() const;

	const std::vector<std::string>& getProperties() const;
	const std::vector<JSON>& getChildren() const;

	// using "as" instead of "to" since its similar to a cast, it can fail

	bool asBool() const;
	int asInt() const;
	double asDouble() const;

	std::string asString() const;
	std::string asString(bool replaceEscapeSequences) const;
	std::string asString(std::string tabulation, bool replaceEscapeSequences) const;
};
