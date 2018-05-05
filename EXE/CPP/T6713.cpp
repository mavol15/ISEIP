#include "t6713_5k_i2c_lib.h"
#include "MySQL_lib.h"

#include <thread>         // std::this_thread::sleep_until
#include <chrono>         // std::chrono::system_clock
#include <ctime>          // std::time_t, std::tm, std::localtime, std::mktime

using namespace std;



int main(void) {

	int CO2_meas = 0;

	int file;

	char data[2] = { 0 };//for temp

	string SQLstr;

	file = init_i2c_BBB2();



	i2cDeviceBBB CO2_Sen(T6713_5K, file);



	//Get CO2 sensor data
	CO2_meas = T6713_5K_get_CO2(CO2_Sen);
	if (CO2_meas == 1) {
		return 2;
	}

	//If CO2 sensor returned 0, wait Define and try again
	if (CO2_meas == 0) {
		nanosleep((const struct timespec[]) { {0, I2C_COMM_DELAY} }, NULL);
		CO2_meas = T6713_5K_get_CO2(CO2_Sen);
		if (CO2_meas == 1) {
			return 3;
		}
	}

	if (CO2_meas == 0) {
		SQLstr = "INSERT INTO sensorTB (time, co2) VALUES (NOW() - INTERVAL MOD((EXTRACT(SECOND FROM NOW())), 10) SECOND, NULL) ON DUPLICATE KEY UPDATE co2 = NULL";
	}
	else {
		SQLstr = "INSERT INTO sensorTB (time, co2) VALUES (NOW() - INTERVAL MOD((EXTRACT(SECOND FROM NOW())), 10) SECOND, " + to_string(CO2_meas) + ") ON DUPLICATE KEY UPDATE co2 = " + to_string(CO2_meas);
	}

	//Send to database. If equal to 1 an error has occured
	if (to_Database(SQLstr) == 1) {
		return 4;
	}

	return 0;
}
