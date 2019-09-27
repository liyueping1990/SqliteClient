#ifndef SQLITECLIENT_H_
#define SQLITECLIENT_H_
#include <iostream>
#include <map>
#include <list>
#include "sqlite3.h"

#define KeyValue    std::map<std::string, std::string>
#define KeyValuePtr std::shared_ptr<KeyValue>
#define DataList    std::list<KeyValuePtr>
#define DataListPtr std::shared_ptr<DataList>

class SqliteClient
{
public:
	typedef std::shared_ptr<SqliteClient> Ptr;

	SqliteClient();
	virtual ~SqliteClient();

	int OpenDb(const char* db_name);
	int CloseDb();

	int InsertData(const char* sql_str);
	int DeleteData(const char* sql_str);
	int UpdateData(const char* sql_str);
	int GetData(const char * sql_str, DataListPtr& data_list);
	int GetAllData(const char * tbl_name, DataListPtr& data_list);
private:
	int ExecSql(const char* sql_str);

	sqlite3* sql_db_;
	std::string  db_name_;
};
#endif // SQLITECLIENT_H_

