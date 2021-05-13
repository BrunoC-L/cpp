#include "json.h"

void parseAndStringify();
void manipulations();

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

void parseAndStringify() {
	int testCase = 0;
	auto expect = [&](bool b) { if (!b) std::cerr << "Test " << ++testCase << " Failed\n"; else std::cout << "Test " << ++testCase << " Passed\n"; };
	{
		std::string s1("{}");
		std::string s2 = JSON(s1).asString();
		std::string s3 = replace(s1);
		std::string s4 = JSON(s3).asString();
		expect(s2 == s3 && s3 == s4);
	}
	{
		std::string s1("{'name': [1]}");
		std::string s2 = JSON(s1).asString();
		std::string s3 = replace(s1);
		std::string s4 = JSON(s3).asString();
		expect(s2 == s3 && s3 == s4);
	}
	{
		std::string s1("{'name': 'star wars', 'occupation': 'runescape gold seller', 'hobbies': ['erm'], 'bank accounts': {}, 'what is that': [[[[]]]]}");
		std::string s2 = JSON(s1).asString();
		std::string s3 = replace(s1);
		std::string s4 = JSON(s3).asString();
		expect(s2 == s3 && s3 == s4);
	}
	{
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
		std::string s2 = JSON(s1).asString(4);
		std::string s3 = replace(s1);
		std::string s4 = JSON(s3).asString(4);
		expect(s2 == s3 && s3 == s4);
	}
}

void manipulations() {
	int testCase = 0;
	auto expect = [&](bool b) { if (!b) std::cerr << "Test " << ++testCase << " Failed\n"; else std::cout << "Test " << ++testCase << " Passed\n"; };
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
		expect(json["dog"].asString() == json.get("dog").asString());

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
		expect(json.size() == 1 && json["numbers"].size() == 100 && json["numbers"][67].asInt() == 67 && json["numbers"].get(33).asString() == "33");
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
		std::vector<JSON> jsons;
		jsons.push_back(JSON());
		jsons.push_back(JSON(""));
		jsons.push_back(JSON("''"));
		jsons.push_back(JSON("{}"));
		jsons.push_back(JSON("[]"));
		jsons.push_back(JSON("0"));
		jsons.push_back(JSON("'0'"));
		jsons.push_back(JSON("false"));
		jsons.push_back(JSON("undefined"));
		jsons.push_back(JSON("'undefined'"));
		jsons.push_back(JSON("null"));
		jsons.push_back(JSON("'null'"));
		std::vector<bool> expectedFalse = {};
		for (const auto& json : jsons)
			expectedFalse.push_back(json.asBool());
		expect(std::find(expectedFalse.begin(), expectedFalse.end(), true) == expectedFalse.end());
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
	{
		JSON bigObject;
		std::string bestName = "some property added by someone somewhere";
		bigObject[bestName] = JSON("whatever this might be");
		const JSON& jsonReferencedSomewhere1MileAwayInTheProgram = bigObject[bestName];
		expect(jsonReferencedSomewhere1MileAwayInTheProgram.getName() == bestName);
	}
}
