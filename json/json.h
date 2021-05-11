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

	std::string arrayAsString() const;
	std::string objectAsString() const;

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
	std::unordered_map<std::string, unsigned> indices;
public:
	std::vector<JSON> children;
	void setType(Primitives type);
	void setSelf(std::string str);

	JSON();
	JSON(std::string&& json);
	JSON(const std::string& json);
	JSON(const std::string& json, std::string propertyName);
	JSON(JSON&& other);
	JSON(const JSON& other) = default;

	void operator=(const JSON& other);
	void operator=(const std::string& other);

	JSON& operator[](std::string propertyName);
	JSON& operator[](int x);

	const JSON& get(std::string propertyName) const;
	const JSON& get(int x) const;

	void push(JSON&& json);
	void push(std::string str);

	bool asBool() const;
	int asInt() const;
	double asDouble() const;
	std::string asString() const;
};
