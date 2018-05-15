#include "MySQL_lib.h"

int to_Database(string SQLstr) {

	MYSQL_RES *result;

	MYSQL_ROW row;

	MYSQL *connection, mysql;


	int state;
	string str;

	

	const char * c = SQLstr.c_str();

	//Start communication
	mysql_init(&mysql);

	connection = mysql_real_connect(&mysql, "localhost", "AutoUser", "2imprezsAutoPWD", "sensorDB", 0, NULL, 0);

	if (connection == NULL) {
		/*
		printf("Init gave ");
		printf(mysql_error(&mysql));
		printf("\n");
		*/
		return 1;
	}

	//Send data
	state = mysql_query(connection, c);

	if (state != 0) {
		/*
		printf("Send gave ");
		printf(mysql_error(connection));
		printf("\n");
		*/

		return 1;
	}

	//Terminate connection
	mysql_close(connection);

	return 0;
}
