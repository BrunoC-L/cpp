#include "json.h"
#include "json.cpp"
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
	std::vector<std::string> args;
	args.reserve(argc - 1);
	for (int i = 1; i < argc; ++i)
		args.emplace_back(argv[i]);

	const auto& mode = args.at(0);
	if (mode == "help") {
		std::cout << "Usage: `jsonedit.exe <read|write|help> <filename> <key> <value?>` keyvalue for writing, key for reading\n"
			"example keys: `['names'][0]['firstname']`, `\"['key with spaces']\"\n"
			"example values: `true`, `undefined`, `'Hello world!'`\n"
			"note: any `'` can be replaced with `\"`";
		return 0;
	}

	const auto& filename = args.at(1);
	const auto& key = args.at(2);

	std::stringstream ss;

	{
		std::ifstream file(filename);
		if (!file.is_open())
			return 1;
		ss << file.rdbuf();
		file.close();
	}
	JSON json(ss.str());

	std::string keybuffer;
	JSON* p = &json;

	for (const auto& c : key) {
		switch (c) {
		case '[':
			keybuffer = "";
			break;
		case ']':
			switch (keybuffer.at(0)) {
			case '\'':
			case '"':
				p = &(*p)[keybuffer.substr(1, keybuffer.length() - 2)];
				break;
			default:
				p = &(*p)[atoi(keybuffer.c_str())];
				break;
			}
			break;
		default:
			keybuffer += c;
			break;
		}
	}

	if (mode == "read") {
		std::cout << p->asString();
	}
	else if (mode == "write") {
		std::string value = args.at(3);
		(*p) = value;

		{
			std::ofstream file(filename, std::ofstream::out);
			if (!file.is_open())
				return 1;
			std::string content = json.asString(false);
			file.write(content.c_str(), content.length());
		}
	}
}
