#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <map>
#include <string>

//翻译
class Translate
{
public:

	static void load(const std::string& filePath);
	
	static std::string tr(const std::string& str);
	

private:
	static std::string content ;

	static std::map<std::string, std::string> data;

};

#endif // !TRANSLATE_H