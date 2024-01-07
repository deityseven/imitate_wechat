#include "driver.h"
#include <util/platform_util.h>

Driver::Driver()
    :drivers(PlatformUtil::compactDiscList())
{
}

Driver::~Driver()
{
}

std::list<std::string> Driver::getDrivers()
{
    return this->drivers;
}

bool Driver::popup(std::string driver)
{

    return false;
}

