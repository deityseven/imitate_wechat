#include <common/ini_config.h>

#include <iostream>
#include <map>
#include <string>

int main(int argc, char *argv[])
{
	//ConfigParser cp("./configs/system.ini");
    //
	//std::cout << cp.getValue("key2");
	//std::cout << cp.getValue("sysytem","ip");
    //
    //std::string& content = FileUtil::readAllText("./configs/system.ini");

    ConfigFile* ic = new IniConfig("./configs/system.ini");


	return 0;
}

