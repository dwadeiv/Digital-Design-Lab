/*
 * ble.h
 *
 *  Created on: May 22, 2019
 *      Author: xxx
 */

#ifndef SRC_HEADER_FILES_BLE_H_
#define SRC_HEADER_FILES_BLE_H_
//***********************************************************************************
// Include files
//***********************************************************************************

//** Standard Libraries
#include <stdbool.h>
#include <stdint.h>

#include "leuart.h"

//***********************************************************************************
// defined files
//***********************************************************************************

// for testing BLE Connection:
#define BLE_TEST_ENABLED

#define HM18_LEUART0		LEUART0
#define HM18_BAUDRATE		9600
#define	HM18_DATABITS		leuartDatabits8
#define HM18_ENABLE			leuartEnable
#define HM18_PARITY			leuartNoParity
#define HM18_REFFREQ		0	// use reference clock
#define HM18_STOPBITS		leuartStopbits1

#define LEUART0_TX_ROUTE	LEUART_ROUTELOC0_TXLOC_LOC18
#define LEUART0_RX_ROUTE	LEUART_ROUTELOC0_RXLOC_LOC18

#define LEUART0_TX_PIN_EN	LEUART_ROUTEPEN_TXPEN
#define LEUART0_RX_PIN_EN	LEUART_ROUTEPEN_RXPEN

#define LEUART0_TX_EN		LEUART_CMD_TXEN
#define LEUART0_RX_EN		LEUART_CMD_RXEN


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
void ble_open(uint32_t tx_event, uint32_t rx_event);
void ble_write(char *string);

bool ble_test(char *mod_name);

#endif /* SRC_HEADER_FILES_BLE_H_ */
