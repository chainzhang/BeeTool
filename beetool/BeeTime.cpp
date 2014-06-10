//
//  BeeTime.cpp
//  virtualLife
//
//  Created by 張程 on 2014/06/09.
//
//

#include "BeeTime.h"

std::string Bee::Time::sNow(const char *format)
{
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];
    
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    
    std::strftime(buffer,80, format ,timeinfo);
    std::puts(buffer);
    
    return buffer;
}