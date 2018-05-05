#include "BBB_i2c_lib.h"


i2cDeviceBBB::i2cDeviceBBB(int adr, int fil) : addr(adr), file(fil) {}


int i2cDeviceBBB::init_device() {
	int rV = 0;

	if (ioctl(file, I2C_SLAVE, addr) < 0) {
		/*
		printf("Failed to acquire bus access and/or talk to slave. \n%s\n", strerror(errno));
		//ERROR HANDLING; you can check errno to see what went wrong
		exit(1);
		*/
		rV = 1;
	}
	return rV;
}


int i2cDeviceBBB::read_i2c(char *buf, int bytes) {
	int rV = 0;
	//read(device to read, data to read, bytes to read)
	if (read(file, buf, bytes) != bytes) {
		/* ERROR HANDLING: i2c transaction failed */
		/*
		printf("Failed to read from the i2c bus: %s.\n", strerror(errno));
		printf("\n\n");'
		*/
		rV = 1;
	}
	else {
		rV = 0;
		//Successfully read
		/* Device specific stuff here */
		//Return acquired data maybe?
	}
	return rV;
}


int i2cDeviceBBB::write_i2c(char data[], int bytes) {
	int rV = 0;
	//write(device to write, data to write(first byte would be Device register to access), bytes to write)
	if (write(file, data, bytes) != bytes) { 
		/* ERROR HANDLING: i2c transaction failed */
		/*
		printf("Failed to write to the i2c bus: %s.\n", strerror(errno));
		printf("\n\n");
		*/
		rV = 1;
	}
	return rV;
}


int init_i2c_BBB2() {
	int file;

	if ((file = open("/dev/i2c-1", O_RDWR)) < 0) {
		//ERROR HANDLING: you can check errno to see what went wrong
		//printf("Failed to open the i2c bus \n");
		//exit(1);
	}
	return file;
}
