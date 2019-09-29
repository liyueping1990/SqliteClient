#include "SqliteClient.h"

int main(int argc, char* argv[])
{
	SqliteClient::Ptr sqlite_client(new SqliteClient);
	int result = sqlite_client->OpenDb("../../gb_server.db");
	if (result)
	{
		return result;
	}

	DataListPtr data_list;
	sqlite_client->GetData("SELECT * FROM GB_platform WHERE platform_ID = 1", data_list);

	return result;
}