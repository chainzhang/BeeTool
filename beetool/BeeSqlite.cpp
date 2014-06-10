//
//  BeeSqlite.cpp
//  virtualLife
//
//  Created by 張程 on 2014/06/06.
//
//

#include "BeeSqlite.h"

USING_NS_BEE;

Sqlite* Sqlite::_instance = nullptr;
const char* Sqlite::ID               = " INTEGER PRIMARY KEY AUTOINCREMENT";
const char* Sqlite::PRIMARY          = " PRIMARY";
const char* Sqlite::KEY              = " KEY";
const char* Sqlite::AUTOINCREMENT    = " AUTOINCREMENT";
const char* Sqlite::DEFAULT(char *default_value) {
    std::string temp = " DEFAULT ";
    return temp.append(default_value).c_str();
}


const char* Sqlite::_NULL            = " NULL";
const char* Sqlite::INTEGER          = " INTEGER";
const char* Sqlite::REAL             = " REAL";
const char* Sqlite::TEXT             = " TEXT";
const char* Sqlite::BLOB             = " BLOB";

Sqlite::Sqlite():
_db(nullptr),
_result(0),
_error_msg(NULL)
{
}

Sqlite::~Sqlite()
{
    if (_db){
        sqlite3_close(_db);
    }
}

Sqlite* Sqlite::getInstance()
{
    if (!_instance) {
        _instance = new Sqlite;
    }
    return _instance;
}

bool Sqlite::setDB(const char *db_path)
{
    _result = sqlite3_open(db_path, &_db);
    if (_result != SQLITE_OK)
    {
        CCLOG("データベース%sを初期化できませんでした。エラー：%s", db_path, _error_msg);
        return false;
    }
    
    return true;
}

int Sqlite::query(const std::string &query)
{
    return sqlite3_exec(_db, query.c_str(), NULL, NULL, &_error_msg);
}

bool Sqlite::tableIsExist(const std::string &name)
{
    if (_db != NULL)
    {
        bool tableExist = 0;
        _query_string = "SELECT name FROM sqlite_master WHERE type = 'table' AND name = '"+ name +"'";
        _result = sqlite3_exec(_db, _query_string.c_str(), _isExist, &tableExist, &_error_msg);
        CCLOG("%s is %i", name.c_str(), tableExist);
        return tableExist;
    }
    CCLOG("pDB is NULL");
    
    return false;
}

void Sqlite::createTable(const std::string &name, char* scheme)
{
    if (!tableIsExist(name))
    {
        std::string the_scheme(scheme);
        std::string sql = "CREATE TABLE " +name+ " (" +the_scheme+ ")";
        delete [] scheme;
        _result = this->query(sql);
        if (_result != SQLITE_OK)
        {
            CCLOG("新規テーブルできませんでした。エラー%d：%s", _result, _error_msg);
        }
    }
}

void Sqlite::deleteTable(const std::string &name)
{
    if (tableIsExist(name))
    {
        std::string sql = "DELETE FROM " + name;
        _result = this->query(sql);
        if (_result != SQLITE_OK)
        {
            CCLOG("エラー%d：%s", _result, _error_msg);
        }
    }
}
/*
void Sqlite::fetch(const std::string &query, int (*callback)(void *, int, char **, char **), void *sender)
{
    sqlite3_exec(_db, query.c_str(), callback, sender, &_error_msg);
}

void Sqlite::fetch(const std::string &table_name, const int count, int (*callback)(void *, int, char **, char **), void *sender)
{
    std::string sql = "SELECT * FROM " + table_name + " LIMIT " + std::to_string(count);
    sqlite3_exec(_db, sql.c_str(), callback, sender, &_error_msg);
}
*/

void Sqlite::fetch(Bee::SqliteFetch *query)
{
    _fetch_pipeline.push_back(query);
    std::string sql = query->getSql();
    sqlite3_exec(_db, sql.c_str(), Sqlite::_callBack, this, &_error_msg);
    delete query;
    _fetch_pipeline.pop_front();
    
}

int Sqlite::_callBack(void *para, int num_col, char **col_value, char **col_name)
{
    std::map<std::string, std::string>table;
    for(int i=0; i<num_col; i++){
        table[col_name[i]] = col_value[i] ? col_value[i] : "NULL";
    }
    _instance->_fetch_pipeline.front()->get(table);
    return 0;
}

void Sqlite::insertRecord(const std::string &table_name, std::map<std::string, std::string> string_values)
{
    std::string cols = "";
    std::string values = "";
    
    std::map<std::string, std::string>::iterator it = string_values.begin();
    while (it != string_values.end()) {
        cols.append('\''+(*it).first+'\'');
        cols.append(",");
        values.append('\''+(*it).second+'\'');
        values.append(",");
        it++;
    }
    cols.pop_back();
    values.pop_back();
    
    
    std::string sql = "INSERT INTO "+ table_name +" (" + cols + ") VALUES (" + values + ")";
    _result = this->query(sql);
    if (_result != SQLITE_OK)
    {
        CCLOG("エラー%d：%s", _result, _error_msg);
    }
}


int Sqlite::_isExist(void *para, int n_col, char ** col_value, char ** col_name)
{
    bool *isExist_ = (bool*)para;
    *isExist_ = (**col_value) != 0;
    return 0;
}

char* Sqlite::createCol(const char *str, ...)
{
    va_list args;
    std::string temp = "";
    for (va_start(args, str); str != NULL; str = va_arg(args, const char*)) {
        temp.append(str);
    }
    char * returnChar = new char[temp.size()+1];
    std::copy(temp.begin(), temp.end(), returnChar);
    returnChar[temp.size()] = '\0';
    
    return returnChar;
}

char* Sqlite::createColSet(char *str, ...)
{
    va_list args;
    std::string temp = "";
    for (va_start(args, str); str != NULL; str = va_arg(args, char*)) {
        temp.append(str);
        delete [] str;
        temp.append(",");
    }
    temp.pop_back();
    char * returnChar = new char[temp.size()+1];
    std::copy(temp.begin(), temp.end(), returnChar);
    returnChar[temp.size()] = '\0';
    return returnChar;
}
