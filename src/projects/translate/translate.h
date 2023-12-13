#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <unordered_map>
#include <string>

//翻译
class Translate
{
public:
	template<typename T>
	static T tr(const T& what)
	{

	}

	static std::unordered_map<std::string, std::string> data;
};

#endif // !TRANSLATE_H