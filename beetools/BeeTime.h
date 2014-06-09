//
//  BeeTime.h
//  virtualLife
//
//  Created by 張程 on 2014/06/09.
//
//

#ifndef __BEE_TIME_H__
#define __BEE_TIME_H__

#include "Bee.h"

BEE_NS_BEGIN;

class Time
{
public:
    static std::string sNow( const char* format = "%Y-%m-%d %H:%M:%S" );
};



BEE_NS_END;

#endif /* defined(__virtualLife__BeeTime__) */
