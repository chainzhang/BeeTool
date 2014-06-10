//
//  BeeJson.cpp
//  virtualLife
//
//  Created by 張程 on 2014/06/10.
//
//

#include "BeeFile.h"

Json::Value Bee::File::readJSON(const std::string &filename)
{
    Json::Value temp;
    Json::Reader reader;
    
    if (!reader.parse(cocos2d::FileUtils::getInstance()->getStringFromFile(filename), temp))
    {
        CCLOG("error");
        return NULL;
    }
    
    return temp;
}

bool Bee::File::writeJSON(const std::string &path_to_file)
{
    Json::StyledWriter writer;
    
}