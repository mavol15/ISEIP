#pragma once
#include "BBB_i2c_lib.h"

//* The delay between a write and read command
#define I2C_COMM_DELAY (21000000L)

//* Slave address of T6713 5K
#define T6713_5K (0x15)

//* Function Code
#define FUNCTION_CODE (0x04)

//* Starting Address (MSB)
#define START_ADDR_MSB (0x13)

//* Starting Address (LSB)
#define START_ADDR_LSB (0x8B)

//* Starting Address (LSB)
#define STATUS_START_ADDR_LSB (0x8A)

//* Input registers to read (MSB)
#define REGS_TO_READ_MSB (0x00)

//* Input registers to read (LSB)
#define REGS_TO_READ_LSB (0x01)

/*
* Read from T6713 5K via I2C
* Input: Object of class i2cDevice (Will only work if the object is of a T6713 5K sensor)
* Output: CO2 as ppm of type int
*/
int T6713_5K_get_CO2(i2cDeviceBBB dev);

//int T6713_5K_check_status(i2cDeviceBBB dev, char *errMes);

