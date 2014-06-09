//
//  BeeSqliteFetch.cpp
//  virtualLife
//
//  Created by ChainZ on 2014/06/08.
//
//

#include "BeeSqliteFetch.h"

USING_NS_BEE;

SqliteFetch::SqliteFetch(const std::string &sql):
_sql(sql)
{
}

SqliteFetch::~SqliteFetch()
{
    
}

std::string SqliteFetch::getSql()
{
    return _sql;
}