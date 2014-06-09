//
//  BeeSqlite.h
//  virtualLife
//
//  Created by 張程 on 2014/06/06.
//
//

#ifndef __BEE_SQLITE__
#define __BEE_SQLITE__

#include "Bee.h"
#include "sqlite3.h"
#include "BeeSqliteFetch.h"

BEE_NS_BEGIN;

class SqliteFetch;

class Sqlite
{
public:
    enum FetchType{
        FETCHTYPE_MAP
    };
    
    
    Sqlite();
    ~Sqlite();
    
    static Sqlite* getInstance();
    static char* createCol(const char* str, ...);
    static char* createColSet(char* str, ...);
    
    
    bool setDB(const char* db_path);
    int query(const std::string &query);
    
    bool tableIsExist(const std::string &name);
    
    void createTable(const std::string &name, char* scheme);
    void createTable(const std::string &query);
    
    void deleteTable(const std::string &name);
    
    void fetch(const std::string &table_name, const int count, int (*callback)(void *, int, char **, char **), void *sender);
    void fetch(const std::string &query, int (*callback)(void *, int, char **, char **), void *sender);
    
    void fetch(SqliteFetch* fetch);
    
    
    
    void insertRecord(const std::string &table_name, const std::map<std::string, std::string>string_values);
    //void insertRecord(const std::string &table_name, const std::map<std::string, int>int_value);
    //void deleteRecord();
    //void updateRecord();
    
    
    static const char* ID;
    static const char* PRIMARY;
    static const char* KEY;
    static const char* AUTOINCREMENT;
    
    static const char* _NULL;
    static const char* INTEGER;
    static const char* REAL;
    static const char* TEXT;
    static const char* BLOB;
    
    
    
private:
    static int _isExist(void *para, int n_col, char ** col_value, char ** col_name);
    static Sqlite* _instance;
    static int _callBack(void *para, int num_col, char ** col_value, char ** col_name);
    std::list<SqliteFetch*>_fetch_pipeline;
    
    sqlite3 * _db;
    int _result;
    char* _error_msg;
    std::string _query_string;
};

BEE_NS_END;

#endif /* defined(__virtualLife__BeeSqlite__) */
