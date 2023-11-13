#ifndef TYPE_STRUCT_H
#define TYPE_STRUCT_H

#include <string>
#include <list>
#include <map>
#include "data.h"

typedef std::list<std::string> StringList;
typedef std::map<std::string, std::map<std::string, Data>> ConfigData;

#endif // !TYPE_STRUCT_H