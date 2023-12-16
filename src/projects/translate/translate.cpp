#include "translate.h"
#include <fstream>
#include <string>
#include <string_util.h>
#include <type_struct.h>

std::string Translate::content = std::string();
void Translate::load(const std::string& filePath)
{
	
}
std::map<std::string, std::string> Translate::data = std::map<std::string, std::string>();
std::string Translate::tr(const std::string& str)
{
	return Translate::data[str];
}

//void Translate::parse()
//{
//	
//
//}
//