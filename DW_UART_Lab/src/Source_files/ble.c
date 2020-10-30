/**
 * @file ble.c
 * @author Keith Graham
 * @date November 28th, 2019
 * @brief Contains all the functions to interface the application with the HM-18
 *   BLE module and the LEUART driver
 *
 */


//***********************************************************************************
// Include files
//***********************************************************************************
#include "ble.h"
#include <string.h>

//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// private variables
//***********************************************************************************

/***************************************************************************//**
 * @brief BLE module
 * @details
 *  This module contains all the functions to interface the application layer
 *  with the HM-18 Bluetooth module.  The application does not have the
 *  responsibility of knowing the physical resources required, how to
 *  configure, or interface to the Bluetooth resource including the LEUART
 *  driver that communicates with the HM-18 BLE module.
 *
 ******************************************************************************/

//***********************************************************************************
// Private functions
//***********************************************************************************


//***********************************************************************************
// Global functions
//***********************************************************************************


/***************************************************************************//**
 * @brief
 * 	This function initializes the LEUART_OPEN_STRUCT for serial communication
 *
 * @details
 * 	This function initializes all the necessary information for the LEUART driver
 * 	to be able to communicate with a BLE device then calls the leuart_open function
 * 	passing the initialized information
 *
 * @note
 * 	All of the macros can remain the same in this function, if one would want to use
 * 	a different BLE, they would just have to edit the values in the header file
 *
 * @param[in] tx_event
 *   Value of the tx_event for the scheduler
 *
 * @param[in] rx_event
 * 	Value of the rx_event for the scheduler
 *
 ******************************************************************************/

void ble_open(uint32_t tx_event, uint32_t rx_event){
	LEUART_OPEN_STRUCT ble_values;
	ble_values.baudrate = HM18_BAUDRATE;
	ble_values.databits = HM18_DATABITS;
	ble_values.enable = HM18_ENABLE;
	ble_values.parity = HM18_PARITY;
	ble_values.ref_freq = HM18_REFFREQ;
	ble_values.rx_loc = LEUART0_RX_ROUTE;
	ble_values.rx_en = LEUART0_RX_EN;
	ble_values.rx_pin_en = LEUART0_RX_PIN_EN;
	ble_values.tx_loc = LEUART0_TX_ROUTE;
	ble_values.tx_en = LEUART0_TX_EN;
	ble_values.tx_pin_en = LEUART0_TX_PIN_EN;
	ble_values.stopbits = HM18_STOPBITS;
	ble_values.tx_done_evt = tx_event;
	ble_values.rx_done_evt = rx_event;

	leuart_open(HM18_LEUART0, &ble_values);
}

/***************************************************************************//**
 * @brief
 * 	This function writes the string argument to the BLE module
 *
 * @details
 * 	The function calls leuart_start function passing the LEUART being used, the
 * 	input string, and the length of the string
 *
 * @note
 * 	THis function will work with any LEUART and any string
 *
 * @param[in] string
 *   String that will be sent to the BLE
 *
 ******************************************************************************/

void ble_write(char* string){
	leuart_start(HM18_LEUART0, string, strlen(string));
}

/***************************************************************************//**
 * @brief
 *   BLE Test performs two functions.  First, it is a Test Driven Development
 *   routine to verify that the LEUART is correctly configured to communicate
 *   with the BLE HM-18 module.  Second, the input argument passed to this
 *   function will be written into the BLE module and become the new name
 *   advertised by the module while it is looking to pair.
 *
 * @details
 * 	 This global function will use polling functions provided by the LEUART
 * 	 driver for both transmit and receive to validate communications with
 * 	 the HM-18 BLE module.  For the assignment, the communication with the
 * 	 BLE module must use low energy design principles of being an interrupt
 * 	 driven state machine.
 *
 * @note
 *   For this test to run to completion, the phone most not be paired with
 *   the BLE module.  In addition for the name to be stored into the module
 *   a breakpoint must be placed at the end of the test routine and stopped
 *   at this breakpoint while in the debugger for a minimum of 5 seconds.
 *
 * @param[in] *mod_name
 *   The name that will be written to the HM-18 BLE module to identify it
 *   while it is advertising over Bluetooth Low Energy.
 *
 * @return
 *   Returns bool true if successfully passed through the tests in this
 *   function.
 ******************************************************************************/

bool ble_test(char *mod_name){
	uint32_t	str_len;

	__disable_irq();
	// This test will limit the test to the proper setup of the LEUART
	// peripheral, routing of the signals to the proper pins, pin
	// configuration, and transmit/reception verification.  The test
	// will communicate with the BLE module using polling routines
	// instead of interrupts.
	//
	// How is polling different than using interrupts?
	// ANSWER: In interrupt, the device notifies the CPU that it needs servicing whereas,
	// in polling CPU repeatedly checks whether a device needs servicing.
	//
	// How does interrupts benefit the system for low energy operation?
	// ANSWER: It takes less energy due to the CPU only checking when an interrupt flag
	// is triggered whereas with polling, the CPU is consuming more energy by constantly
	// checking.
	//
	// How does interrupts benefit the system that has multiple tasks?
	// ANSWER: Because you service a single interrupt at a time which will take less
	// processing power.

	// First, you will need to review the DSD HM10 datasheet to determine
	// what the default strings to write data to the BLE module and the
	// expected return statement from the BLE module to test / verify the
	// correct response

	// The break_str is used to tell the BLE module to end a Bluetooth connection
	// such as with your phone.  The ok_str is the result sent from the BLE module
	// to the micro-controller if there was not active BLE connection at the time
	// the break command was sent to the BLE module.
	// Replace the break_str "" with the command to break or end a BLE connection
	// Replace the ok_str "" with the result that will be returned from the BLE
	//   module if there was no BLE connection
	char		break_str[80] = "AT";
	char		ok_str[80] = "OK";

	// output_str will be the string that will program a name to the BLE module.
	// From the DSD HM10 datasheet, what is the command to program a name into
	// the BLE module?
	// The  output_str will be a string concatenation of the DSD HM10 command
	// and the input argument sent to the ble_test() function
	// Replace the otput_str "" with the command to change the program name
	// Replace the result_str "" with the first part of the expected result
	//  the backend of the expected response will be concatenated with the
	//  input argument
	char		output_str[80] = "AT+NAME";
	char		result_str[80] = "OK+Set:";

	// To program the name into your module, you must reset the module after you
	// have sent the command to update the modules name.  What is the DSD HM10
	// name to reset the module?
	// Replace the reset_str "" with the command to reset the module
	// Replace the reset_result_str "" with the expected BLE module response to
	//  to the reset command
	char		reset_str[80] = "AT+RESET";
	char		reset_result_str[80] = "OK+RESET";
	char		return_str[80];

	bool		success;
	bool		rx_disabled, rx_en, tx_en;
	uint32_t	status;

	// These are the routines that will build up the entire command and response
	// of programming the name into the BLE module.  Concatenating the command or
	// response with the input argument name
	strcat(output_str, mod_name);
	strcat(result_str, mod_name);

	// The test routine must not alter the function of the configuration of the
	// LEUART driver, but requires certain functionality to insure the logical test
	// of writing and reading to the DSD HM10 module.  The following c-lines of code
	// save the current state of the LEUART driver that will be used later to
	// re-instate the LEUART configuration

	status = leuart_status(HM18_LEUART0);
	if (status & LEUART_STATUS_RXBLOCK) {
		rx_disabled = true;
		// Enabling, unblocking, the receiving of data from the LEUART RX port
		leuart_cmd_write(HM18_LEUART0, LEUART_CMD_RXBLOCKDIS);
	}
	else rx_disabled = false;
	if (status & LEUART_STATUS_RXENS) {
		rx_en = true;
	} else {
		rx_en = false;
		// Enabling the receiving of data from the RX port
		leuart_cmd_write(HM18_LEUART0, LEUART_CMD_RXEN);
		while (!(leuart_status(HM18_LEUART0) & LEUART_STATUS_RXENS));
	}

	if (status & LEUART_STATUS_TXENS){
		tx_en = true;
	} else {
		// Enabling the transmission of data to the TX port
		leuart_cmd_write(HM18_LEUART0, LEUART_CMD_TXEN);
		while (!(leuart_status(HM18_LEUART0) & LEUART_STATUS_TXENS));
		tx_en = false;
	}
//	leuart_cmd_write(HM10_LEUART0, (LEUART_CMD_CLEARRX | LEUART_CMD_CLEARTX));

	// This sequence of instructions is sending the break ble connection
	// to the DSD HM10 module.
	// Why is this command required if you want to change the name of the
	// DSD HM10 module?
	// ANSWER: Separate the module before changing it
	str_len = strlen(break_str);
	for (int i = 0; i < str_len; i++){
		leuart_app_transmit_byte(HM18_LEUART0, break_str[i]);
	}

	// What will the ble module response back to this command if there is
	// a current ble connection?
	// ANSWER: OK
	str_len = strlen(ok_str);
	for (int i = 0; i < str_len; i++){
		return_str[i] = leuart_app_receive_byte(HM18_LEUART0);
		if (ok_str[i] != return_str[i]) {
				EFM_ASSERT(false);;
		}
	}

	// This sequence of code will be writing or programming the name of
	// the module to the DSD HM10
	str_len = strlen(output_str);
	for (int i = 0; i < str_len; i++){
		leuart_app_transmit_byte(HM18_LEUART0, output_str[i]);
	}

	// Here will be the check on the response back from the DSD HM10 on the
	// programming of its name
	str_len = strlen(result_str);
	for (int i = 0; i < str_len; i++){
		return_str[i] = leuart_app_receive_byte(HM18_LEUART0);
		if (result_str[i] != return_str[i]) {
				EFM_ASSERT(false);;
		}
	}

	// It is now time to send the command to RESET the DSD HM10 module
	str_len = strlen(reset_str);
	for (int i = 0; i < str_len; i++){
		leuart_app_transmit_byte(HM18_LEUART0, reset_str[i]);
	}

	// After sending the command to RESET, the DSD HM10 will send a response
	// back to the micro-controller
	str_len = strlen(reset_result_str);
	for (int i = 0; i < str_len; i++){
		return_str[i] = leuart_app_receive_byte(HM18_LEUART0);
		if (reset_result_str[i] != return_str[i]) {
				EFM_ASSERT(false);;
		}
	}

	// After the test and programming have been completed, the original
	// state of the LEUART must be restored
	if (!rx_en) leuart_cmd_write(HM18_LEUART0, LEUART_CMD_RXDIS);
	if (rx_disabled) leuart_cmd_write(HM18_LEUART0, LEUART_CMD_RXBLOCKEN);
	if (!tx_en) leuart_cmd_write(HM18_LEUART0, LEUART_CMD_TXDIS);
	leuart_if_reset(HM18_LEUART0);

	success = true;

	__enable_irq();
	return success;
}



