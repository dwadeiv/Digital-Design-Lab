/*
 * SI7021.c
 *
 *  Created on: Feb 25, 2020
 *      Author: dwadeiv
 */

//***********************************************************************************
// Include files
//***********************************************************************************
#include "SI7021.h"
#include "gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************
static uint32_t data;

//***********************************************************************************
// function prototypes
//***********************************************************************************


//***********************************************************************************
// functions
//***********************************************************************************

/***************************************************************************//**
 * @brief
 * 	This function creates instances for the various I2C structs
 *
 * @details
 * This function more specifically passes in the neceesary parameters to communicate
 * with the SI7021 via the I2C bus protocol, then calls the i2c_open() function to begin
 * communication
 *
 * @note
 * A similar function would be written for any other arbitrary sensor
 *
 ******************************************************************************/
void si7021_i2c_open(){
	I2C_IO_STRUCT i2c_values;

	i2c_values.scl_pin = SI7021_SCL_PIN;
	i2c_values.scl_port = SI7021_SCL_PORT;
	i2c_values.sda_pin = SI7021_SDA_PIN;
	i2c_values.sda_port = SI7021_SDA_PORT;

	I2C_OPEN_STRUCT i2c_setup;

	i2c_setup.clhr = Si7021_I2C_CLK_RATIO;
	i2c_setup.enable = true;
	i2c_setup.freq = Si7021_I2C_FREQ;
	i2c_setup.master = true;
	i2c_setup.refFreq = Si7021_REF_FREQ;
	i2c_setup.scl_enable = Si7021_SCL_EN;
	i2c_setup.scl_route = Si7021_SCL_LOC;
	i2c_setup.sda_enable = Si7021_SDA_EN;
	i2c_setup.sda_route = Si7021_SDA_LOC;

	i2c_open(Si7021_I2C, &i2c_setup, &i2c_values);

}

/***************************************************************************//**
 * @brief
 * 	This function is what drives the temperature reading
 *
 * @details
 * 	The function passes in the necessary information for I2C communication between the devices,
 * 	then stores the temperature data into a local static variable
 *
 *
 * @note
 *	A similar function would be written for any other arbitrary sensor
 *
 *
 ******************************************************************************/
void si7021_i2c_read(){
	i2c_start(Si7021_I2C, Si7021_dev_addr, Si7021_TEMP_NO_HOLD, &data, Si7021_BYTES);
}

/***************************************************************************//**
 * @brief
 * 	This function converts the temperature date into fahrenheit
 *
 * @details
 * Using a formula out of the SI7021 data sheet, I first convert the data into Celcius
 * then convert the celcius temperature into Fahrenheit. The temperature in fahrenheit is returned
 *
 * @note
 *	This function is used to control the LEDs in the scheduler
 *
 ******************************************************************************/
float si7021_i2c_temp_convert(){
	float converted_data;
	// Converting to celcius
	converted_data = ((float)data * Si7021_TEMP_CONVR) - Si7021_TEMP_SUB;
	// Converting Celcius to Fahrenheit
	converted_data = ((converted_data * 9) / 5) + 32;

	return converted_data;

}



