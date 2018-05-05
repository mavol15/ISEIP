#pragma once
#include <mysql.h>
#include <string>
#include <stdio.h>

using namespace std;

/*
* Send data to Database
* Input: Data that should be send to the Database
* Output: Gives a 1 if an error occurred and a 0 if no error occurred
*/
int to_Database(string SQLstr);


