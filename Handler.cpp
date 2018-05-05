#include <thread>         // std::this_thread::sleep_until
#include <chrono>         // std::chrono::system_clock
#include <ctime>          // std::time_t, std::tm, std::localtime, std::mktime
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <vector>
using namespace std;

int main(void) {
	string STOPfile = "STOP";
	string PYTHON_INITfile = "PYTHON_INIT";
	string line;
	int err = 0;
	vector<string> exeVect;

	using chrono::system_clock;
	time_t tt = system_clock::to_time_t(system_clock::now());

	struct tm * ptm = localtime(&tt);

	ifstream fileToRead("EXE.txt");

	while (getline(fileToRead, line)) {
		exeVect.push_back(line);
	}

	//Wait for next minute to start
	++ptm->tm_min;
	ptm->tm_sec = 0;
	this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

	//If stop.txt exists, delete it and stop the program
	while (true) {
		//err = system("./EXE/CPP/T6713.out");

		for (int i = 0; i < exeVect.size(); i++) {
			err = system(exeVect[i].c_str());
		}

		//err = system("./EXE/PYTHON/BME680.py");

		if (0 == access(STOPfile.c_str(), 0)) {
			remove(STOPfile.c_str());
			remove(PYTHON_INITfile.c_str());
			exit(EXIT_SUCCESS);
		}

		//Waiting for the next 10 sec to begin...
		ptm->tm_sec = ptm->tm_sec + 10;
		this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
		//Time reached!
	}
}
