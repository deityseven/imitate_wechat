#include <file_util.h>
#include <string>
#include <fstream>
#include <json.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 3) return -1;

	nlohmann::json root;

	std::string fileDir(argv[1]);
	std::string outFile(argv[2]);

	std::string content = FileUtil::readAllText(fileDir);

	for (size_t currentPos = 0; currentPos < content.size(); ++currentPos)
	{
		currentPos = content.find("tr(\"", currentPos);

		if (currentPos != std::string::npos)
		{
			auto begin = content.begin();
			auto left = begin + currentPos + 4;

			size_t rightPos = content.find("\")", currentPos);

			auto right = begin + rightPos;

			std::string key(left, right);

			std::string value = "undefine";

			nlohmann::json keyAndValue;
			keyAndValue["english"] = key;
			keyAndValue["chinese"] = value;

			root.push_back(keyAndValue);
		}
	}

	FileUtil::saveToText(root.dump(), outFile);

	return 0;

	size_t pos = content.find("tr(") + 4;
	size_t pos2 = content.find("\")");
	std::string str;
	while (pos != pos2)
	{
		str.push_back(content[pos]);
		++pos;
	}
	FileUtil::saveToText(str, "D:/GithubProject/imitate_wechat/configs/EN_to_CN.ts");

	return 0;
}