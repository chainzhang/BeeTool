//
//  BeeJson.h
//  virtualLife
//
//  Created by 張程 on 2014/06/10.
//
//

#ifndef __BEE_JSON_H__
#define __BEE_JSON_H__

#include "Bee.h"
#include "json.h"

BEE_NS_BEGIN;

class File
{
public:
    static Json::Value readJSON(const std::string &filename);
    static bool writeJSON(const std::string &path_to_file);
    
};

BEE_NS_END;

#endif /* defined(__virtualLife__BeeJson__) */
