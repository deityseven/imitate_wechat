#include <file_util.h>
#include <string>
#include <fstream>
#include <json.hpp>
#include <stdio.h>
#include <iostream>
#include <getopt.hpp>
#include <platform_util.h>
#include <string_util.h>
#include <algorithm>

std::vector<std::string> getAllFiles(std::string dir)
{
	std::vector<std::string> result;

	if (!dir.empty())
	{
		auto fileAndDirs = PlatformUtil::directoryContent(dir);

		for (auto& item : fileAndDirs)
		{
			if (PlatformUtil::isFile(item))
			{
				result.push_back(item);
			}
			else if (PlatformUtil::isDirectory(item))
			{
				std::vector<std::string> temp = getAllFiles(item);
				result.insert(result.begin(), temp.begin(), temp.end());
			}
		}
	}

	return result;
}

std::string scan(std::vector<std::string> inputFiles)
{
	nlohmann::json root;

	for (const auto& item : inputFiles)
	{
		std::string content = FileUtil::readAllText(item);

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
			else
			{
				break;
			}
		}
	}

	return root.dump(0);
}

int main(int argc, char* argv[])
{
	std::string singleFile = getarg("", "-s", "--singlefile");
	std::string outFile = getarg("./out.ts", "-o", "--out");
	std::string scanDir = getarg("", "-d", "--dir");
	std::string typeFile = getarg("cpp", "-t", "--type");

	std::vector<std::string> needScanFiles;

	if (!singleFile.empty())
	{
		needScanFiles.push_back(singleFile);
	}

	if (!scanDir.empty())
	{
		auto temp = getAllFiles(scanDir);
		needScanFiles.insert(needScanFiles.begin(), temp.begin(), temp.end());
	}

	auto typeList = StringUtil::split(typeFile, '/');

	std::vector<std::string> inputFile;

	for (auto item : needScanFiles)
	{
		for (auto type : typeList)
		{
			if (item.find(type) != std::string::npos)
			{
				inputFile.push_back(item);
				break;
			}
		}
	}

	std::string content = scan(inputFile);

	FileUtil::saveToText(content, outFile);

	return 0;
}