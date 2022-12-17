#include "json.h"
#include <algorithm>

void parseAndStringify();
void manipulations();

int testCase = 0;
auto expect = [&](bool b) { if (!b) std::cerr << "Test " << ++testCase << " Failed\n"; else std::cout << "Test " << ++testCase << " Passed\n"; };

int main() {
	std::cout << "--- parseAndStringify ---\n";
	parseAndStringify();
	std::cout << "--- manipulations ---\n";
	manipulations();
}

std::string replace(const std::string& s) {
	std::string r;
	for (const auto& c : s)
		if (c == '\'')
			r += '"';
		else
			r += c;
	return r;
}

void simpleReplaceTest(const std::string& s1) {
	std::string s2 = JSON(s1).asString("", false);
	std::string s3 = replace(s1);
	std::string s4 = JSON(s3).asString("", false);
	expect(s2 == s3 && s3 == s4);
}

void parseAndStringify() {
	{
		simpleReplaceTest("{}");
	}
	{
		simpleReplaceTest("{'name': [1]}");
	}
	{
		simpleReplaceTest("{'name': 'star wars', 'occupation': 'runescape gold seller', 'hobbies': ['erm'], 'bank accounts': {}, 'what is that': [[[[]]]]}");
	}
	{
		// same test but different order, to check that order is indeed respected, unlike previous versions
		simpleReplaceTest("{'occupation': 'runescape gold seller', 'name': 'star wars', 'bank accounts': {}, 'hobbies': ['erm'], 'what is that': [[[[]]]]}");
	}
	{
		// testing with tabulations
		std::string s1(
			"{\n"
			"    'name': 'star',\n"
			"    'occupation': 'runescape gold seller',\n"
			"    'hobbies': [\n"
			"        'xd'\n"
			"    ],\n"
			"    'bank accounts': {},\n"
			"    'xd': [\n"
			"        [\n"
			"            [\n"
			"                []\n"
			"            ]\n"
			"        ]\n"
			"    ]\n"
			"}");
		std::string s2 = replace(s1);
		std::string s3 = JSON(s1).asString("    ", false);
		std::string s4 = JSON(s3).asString("    ", false);
		expect(s2 == s3 && s3 == s4);
	}
	{
		JSON escapeSequences("{'hello':'world!\\n', 'boom':'bop\\t\\n\\\\'}");
		expect(escapeSequences["hello"].asString("", false) == "world!\\n");
		expect(escapeSequences["hello"].asString("", true)  == "world!\n");
		expect(escapeSequences["boom"].asString("", false) == "bop\\t\\n\\\\");
		expect(escapeSequences["boom"].asString("", true) == "bop\t\n\\");
	}
	{
		std::cout << JSON(
			"{\n"
			"\t'test': true\n"
			"}"
		).asString(4) << "\n";
		expect(
			JSON(
				"{\n"
				"\t'test': true\n"
				"}"
			).asString(4) == "{\n"
				"\t'test': 'true'\n"
			"}");
	}
}

void manipulations() {
	testCase = 0;
	{
		JSON json;
		json["dog"] = "dog";
		json["dogs"] = "[]";
		json["dogs"].push(json["dog"]);
		expect(json["dogs"][0].asString() == json["dog"].asString());
	}
	{
		JSON json;
		json["dog"] = "dog";
		expect(json["dog"].asString() == json.at("dog").asString());

		json["dog"] = "";
		expect(json["dog"].asString() == "");

		json["dog"] = JSON();
		expect(json["dog"].asString() == "{}");
	}
	{
		JSON json;
		json["numbers"] = "[]";
		for (int i = 0; i < 100; ++i)
			json["numbers"].push(std::to_string(i));
		expect(json.size() == 1 && json["numbers"].size() == 100 && json["numbers"][67].asInt() == 67 && json["numbers"].at(33).asString() == "33");
	}
	{
		int K = 3, N = 6;
		JSON json;
		std::string s = "numbers";
		json[s + std::to_string(0)] = "[0]";
		for (int i = 1; i < N; ++i) {
			auto u = s + std::to_string(i);
			json[s + std::to_string(i)] = "[]";
			for (const auto& child : json[s + std::to_string(i - 1)].getChildren()) {
				for (int j = 0; j < K; ++j)
					json[s + std::to_string(i)].push(child);
			}
		}
		expect(json["numbers" + std::to_string(N - 1)].size() == std::pow(K, N - 1));
	}
	{
		std::vector<JSON> falses;
		falses.push_back(JSON());
		falses.push_back(JSON(""));
		falses.push_back(JSON("''"));
		falses.push_back(JSON("{}"));
		falses.push_back(JSON("[]"));
		falses.push_back(JSON("0"));
		falses.push_back(JSON("'0'"));
		falses.push_back(JSON("false"));
		falses.push_back(JSON("undefined"));
		falses.push_back(JSON("'undefined'"));
		falses.push_back(JSON("null"));
		falses.push_back(JSON("'null'"));
		bool anytrue = false;
		for (const auto& json : falses)
			anytrue |= json.asBool();
		expect(anytrue == false);
	}
	{
		std::vector<JSON> jsons;
		jsons.push_back(JSON("{'a':1}"));
		jsons.push_back(JSON("[0]"));
		jsons.push_back(JSON("1"));
		jsons.push_back(JSON("'1'"));
		jsons.push_back(JSON("true"));
		jsons.push_back(JSON("defined"));
		jsons.push_back(JSON("'!'"));
		std::vector<bool> expectedTrue = {};
		for (const auto& json : jsons)
			expectedTrue.push_back(json.asBool());
		expect(std::find(expectedTrue.begin(), expectedTrue.end(), false) == expectedTrue.end());
	}
}
