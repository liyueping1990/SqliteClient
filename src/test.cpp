#include "SqliteClient.h"

int main(int argc, char* argv[])
{
	SqliteClient::Ptr sqlite_client(new SqliteClient);
	int result = sqlite_client->OpenDb("demodb");
	if (result)
	{
		return result;
	}

	DataListPtr data_list;
	sqlite_client->GetAllData("client", data_list);
	sqlite_client->GetData("select * from client", data_list);
	return result;
}