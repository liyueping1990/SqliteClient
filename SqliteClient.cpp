#include "SqliteClient.h"

SqliteClient::SqliteClient()
{
	sql_db_ = nullptr;
}

SqliteClient::~SqliteClient()
{
	if (sql_db_ != nullptr)
	{
		sqlite3_close(sql_db_);
		sql_db_ = nullptr;
	}
}

int SqliteClient::OpenDb(const char * db_name)
{	
	int result = -1;
	if (db_name == nullptr)
	{
		return result;
	}

	result = sqlite3_open(db_name, &sql_db_);
	if (result != 0)
	{
		printf("can't open db: %s\r\n", sqlite3_errmsg(sql_db_));
		sqlite3_close(sql_db_);
	} 
	else
	{
		db_name_ = db_name;
		printf("db open successfully!\r\n");
	}
	return result;
}

int SqliteClient::CloseDb()
{
	printf("close db!\r\n");
	if (sql_db_)
	{
		sqlite3_close(sql_db_);
		sql_db_ = nullptr;
	}
	return 0;
}

int SqliteClient::InsertData(const char * sql_str)
{
	return ExecSql(sql_str);
}

int SqliteClient::DeleteData(const char * sql_str)
{
	return ExecSql(sql_str);
}

int SqliteClient::UpdateData(const char * sql_str)
{
	return ExecSql(sql_str);
}

int SqliteClient::GetData(const char * sql_str, DataListPtr& data_list)
{
	if (data_list == nullptr)
	{
		data_list.reset(new DataList);
	}

	char** datas = nullptr;
	char* err_msg = nullptr;

	int   rows = 0;
	int   cols = 0;

	int error = sqlite3_get_table(sql_db_, sql_str, &datas, &rows, &cols, &err_msg);
	if (error != 0)
	{
		printf("err_msg:%s", err_msg);
		sqlite3_free(err_msg);
	}
	else
	{		
		int index = 0;
		for (int i = 1; i <= rows; i++)
		{
			KeyValuePtr key_value(new KeyValue);
			for (int j = 0; j < cols; j++)
			{
				index = i * cols + j;
				char* key = datas[j];
				char* value = datas[index];
				if (key == nullptr || value == nullptr)
				{
					continue;
				}
				key_value->insert(std::pair<std::string, std::string>(key, value));
			}
			data_list->push_back(key_value);
		}		
	}

	sqlite3_free_table(datas);
	sqlite3_free(err_msg);
	return error;
}

int SqliteClient::GetAllData(const char * tbl_name, DataListPtr & data_list)
{
	char temp[32] = { 0 };
	sprintf(temp, "select *from %s", tbl_name);
	return GetData(temp, data_list);
}

int SqliteClient::ExecSql(const char * sql_str)
{
	char* err_msg = nullptr;
	int error = sqlite3_exec(sql_db_, sql_str, nullptr, nullptr, &err_msg);
	if (error != 0)
	{
		printf("err_msg:%s", err_msg);
	}

	sqlite3_free(err_msg);
	return error;
}
