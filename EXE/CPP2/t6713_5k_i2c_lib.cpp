#include "t6713_5k_i2c_lib.h"

int T6713_5K_get_CO2(i2cDeviceBBB dev) {
	char data[5] = { 0 };

	int CO2meas = 0;

	int rV = 0;

	dev.init_device();

	//Prepare T6713 5K for reading
	data[0] = FUNCTION_CODE;
	data[1] = START_ADDR_MSB;
	data[2] = START_ADDR_LSB;
	data[3] = REGS_TO_READ_MSB;
	data[4] = REGS_TO_READ_LSB;
	rV = dev.write_i2c(data, 5);
	if (rV == 1) {
		return 1;
	}
	//Wait for T6713 5K to prepare its data
	nanosleep((const struct timespec[]) { {0, I2C_COMM_DELAY} }, NULL);

	//Read from T6713 5K.
	rV = dev.read_i2c(data, 4);
	if (rV == 1) {
		return 1;
	}
	//data[0] gives Function code(0x04).data[1] gives byte count(0x02)
	//data[2] gives MSB of the 16 - bit data and data[3] gives LSB of the 16 - bit data


	//Merge MSB and LSB to 16-bit
	CO2meas = (((data[2] & 0x3F) << 8) | data[3]);

	return CO2meas;
}

/*int T6713_5K_check_status(i2cDeviceBBB dev, char *errMes) {
	char data[5] = { 0 };
	char errH = 0;
	*errMes = 0;

	dev.init_device();

	//Prepare T6713 5K for reading
	data[0] = FUNCTION_CODE;
	data[1] = START_ADDR_MSB;
	data[2] = STATUS_START_ADDR_LSB;
	data[3] = REGS_TO_READ_MSB;
	data[4] = REGS_TO_READ_LSB;
	dev.write_i2c(data, 5);

	dev.read_i2c(data, 4);

	if (data[0] & 0x80) {
		printf("\n T6713 5K: Single point calibration \n");
		errH = 1;
	}

	if (data[0] & 0x08) {
		printf("\n T6713 5K: Warm-up mode \n");
		errH = 1;
	}

	if (data[1] & 0x01) {
		printf("\n T6713 5K: Error condition \n");
		errH = 1;
	}

	if (data[1] & 0x02) {
		printf("\n T6713 5K: Flash error \n");
		errH = 1;
	}

	if (data[1] & 0x04) {
		printf("\n T6713 5K: Calibratio error \n");
		errH = 1;
	}

	return errH;
}
*/
