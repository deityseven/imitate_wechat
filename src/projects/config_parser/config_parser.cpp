#include "config_parser.h"
#include <fstream>
#include <iostream>
#include <vector>

ConfigParser::ConfigParser(std::string filePath)
{
	std::string data;

	//打开文件
	std::ifstream ifs;

	ifs.open(filePath, std::ios::in);

	if (!ifs.is_open()) {
		//打开失败
		return;
	}
	else {
		//打开成功
		//第四种方式
		char ch;
		//循环意思是一次读取一个字符，一直读到文本最后
		while ((ch = ifs.get()) != EOF) {//EOF代表文件尾

			data.push_back(ch);
		}

		std::string newData;
		bool needPushBack = true;
		for (char& ch : data)
		{
			if (ch == '#')
			{
				needPushBack = false;
			}

			if (needPushBack == false)
			{
				if (ch == '\n')
				{
					needPushBack = true;
					continue;
				}
			}

			if (needPushBack)
			{
				newData.push_back(ch);
			}
		}
		//5.关闭文件
		ifs.close();
		newData.push_back('\n');

		std::string sectionData;
		std::string defaultData;

		bool isSectionData = false;
		for (char& ch : newData)
		{
			if(ch == '[') isSectionData = true;

			if (isSectionData == true)
			{
				sectionData.push_back(ch);
			}
			else
			{
				defaultData.push_back(ch);
			}
		}

		//处理sectionData，以[分割数据得到每个section
		std::vector<std::string> sectionVec;
		std::string temp;
		for (char& ch : sectionData)
		{
			if (ch == '[')
			{
				if (temp.size() <= 0)
				{
					temp.push_back(ch);
				}
				else
				{
					sectionVec.push_back(temp);
					temp.clear();
					temp.push_back(ch);
				}
			}
			else
			{
				temp.push_back(ch);
			}
		}

		sectionVec.push_back(temp);

		for (auto& sectionData : sectionVec)
		{
			std::string line;
			std::vector<std::string> lines;

			for (char& ch : sectionData)
			{
				line.push_back(ch);

				if (ch == '\n')
				{
					lines.push_back(line);
					line.clear();
				}
			}

			//第一步
			std::string firstLine = lines[0];

			firstLine.pop_back();
			firstLine.pop_back();

			std::string sectionName(firstLine.c_str() + 1);

			//第二步，解析key，value
			for (int i = 1; i < lines.size(); ++i)
			{
				std::string keyValueString = lines[i];

				size_t pos = keyValueString.find('=');

				if (pos == std::string::npos)
				{
					continue;
				}
				else
				{
					std::string key(keyValueString.begin(), keyValueString.begin() + pos);
					std::string value(keyValueString.begin() + pos + 1, keyValueString.end() - 1);

					this->data[sectionName][key] = value;
				}
			}
		}
		
		//处理defaultData
		std::string defaultSectionName = "default";

		std::string line;
		std::vector<std::string> lines;

		for (char& ch : defaultData)
		{
			line.push_back(ch);

			if (ch == '\n')
			{
				lines.push_back(line);
				line.clear();
			}
		}

		for (int i = 1; i < lines.size(); ++i)
		{
			std::string keyValueString = lines[i];

			size_t pos = keyValueString.find('=');

			if (pos == std::string::npos)
			{
				continue;
			}
			else
			{
				std::string key(keyValueString.begin(), keyValueString.begin() + pos);
				std::string value(keyValueString.begin() + pos + 1, keyValueString.end() - 1);

				this->data[defaultSectionName][key] = value;
			}
		}
	}
}

std::string ConfigParser::getValue(std::string key)
{
	return this->data["default"][key];
}

std::string ConfigParser::getValue(std::string section, std::string key)
{
	return this->data[section][key];
}

ConfigParser::~ConfigParser()
{
}
