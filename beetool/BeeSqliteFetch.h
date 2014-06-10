//
//  BeeSqliteFetch.h
//  virtualLife
//
//  Created by ChainZ on 2014/06/08.
//
//

#ifndef __BEE_SQLITE_FETCH_H__
#define __BEE_SQLITE_FETCH_H__

#include "Bee.h"
#include "BeeSqlite.h"

BEE_NS_BEGIN;

class SqliteFetch
{
public:
    friend class Sqlite;
    
    SqliteFetch(const std::string &sql);
    ~SqliteFetch();
    std::function<void(std::map<std::string, std::string>)>get;
    std::string getSql();
    
private:
    std::string _sql;
};


BEE_NS_END;

#endif /* defined(__virtualLife__BeeSqliteFetch__) */
