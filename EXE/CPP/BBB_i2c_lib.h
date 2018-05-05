#pragma once
//includes
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdint.h>
#include <time.h>

#include <signal.h>
#include <stdbool.h>

using namespace std;


/*
* Class for communication with a I2C device through Beaglebone Black
* Expects the I2C devices slave address and the I2C Bus data as initialization parameter
*/
class i2cDeviceBBB {
public:

	i2cDeviceBBB(int adr, int fil);

	//* Init communication with the I2C device
	//* Has to be used when communicating with a new device
	int init_device();

	/*
	* Reads from I2C device
	* Input: *buf = array to read data to. bytes = bytes to read from I2C device
	*/
	int read_i2c(char *buf, int bytes);

	/*
	* Write to I2C device
	* Input: data[] = array of bytes to send. bytes = bytes to write
	* Register address is put in position [0] in the array
	*/
	int write_i2c(char data[], int bytes);

private:
	int file;
	int addr;
};

//* Init the Beaglebones I2C Bus 2 (Should only be used once)
//* Returns the Bus data
int init_i2c_BBB2();