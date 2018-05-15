#include "t6713_5k_i2c_lib.h"

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

	printf("CO2 = %d ", CO2_meas);

	return 0;
}
