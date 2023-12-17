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

std::string scan(const std::vector<std::string>& inputFiles, const std::list<std::string>& targetLanguageList)
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

				for (auto& targetLanguage : targetLanguageList)
				{
					keyAndValue[targetLanguage] = value;
				}

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
	std::string out = getarg("./out.ts", "-o", "--out");
	std::string dir = getarg("", "-d", "--dir");
	std::string type = getarg("cpp", "-t", "--type");
	std::string target_language = getarg("chinese", "-l", "--target_language");

	std::vector<std::string> needScanFiles;

	if (!singleFile.empty())
	{
		needScanFiles.push_back(singleFile);
	}

	if (!dir.empty())
	{
		auto temp = getAllFiles(dir);
		needScanFiles.insert(needScanFiles.begin(), temp.begin(), temp.end());
	}

	auto typeList = StringUtil::split(type, '/');
	auto targetLanguageList = StringUtil::split(target_language, '/');

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

	std::string content = scan(inputFile, targetLanguageList);

	FileUtil::saveToText(content, out);

	return 0;
}