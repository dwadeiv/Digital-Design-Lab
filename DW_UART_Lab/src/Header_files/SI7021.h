/*
 * SI7021.h
 *
 *  Created on: Feb 25, 2020
 *      Author: dwadeiv
 */

//***********************************************************************************
// Include files
//***********************************************************************************
#ifndef SRC_HEADER_FILES_SI7021_H_
#define SRC_HEADER_FILES_SI7021_H_

#define		Si7021_dev_addr			0x40 	// Si7021 I2C device address
#define		Si7021_TEMP_NO_HOLD		0xF3 	// Si7021 temp read/no hold cmd
#define		Si7021_I2C_FREQ			I2C_FREQ_FAST_MAX 	//400kHz
#define		Si7021_I2C_CLK_RATIO	i2cClockHLRAsymetric
#define		Si7021_SCL_LOC			I2C_ROUTELOC0_SCLLOC_LOC15
#define		Si7021_SCL_EN			I2C_ROUTEPEN_SCLPEN
#define		Si7021_SDA_LOC			I2C_ROUTELOC0_SDALOC_LOC15
#define		Si7021_SDA_EN			I2C_ROUTEPEN_SDAPEN
#define		Si7021_I2C				I2C0 	// The PG I2C peripheral to use
#define		Si7021_REF_FREQ 		0
#define		Si7021_BYTES			2
#define		Si7021_TEMP_CONVR		0.00268127
#define		Si7021_TEMP_SUB			46.85

#include "i2c.h"


//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************



//***********************************************************************************
// function prototypes
//***********************************************************************************
void si7021_i2c_open();
void si7021_i2c_read();
float si7021_i2c_temp_convert();

#endif /* SRC_HEADER_FILES_SI7021_H_ */

