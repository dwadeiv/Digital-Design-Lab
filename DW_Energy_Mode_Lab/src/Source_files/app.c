/**
 * @file app.c
 * @author David Wade
 * @date January 30th, 2020
 * @brief Contains the application code utilizing the LETIMER driver functions
 *
 */


//***********************************************************************************
// Include files
//***********************************************************************************
#include "app.h"
#include "letimer.h"


//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function
//***********************************************************************************

/***************************************************************************//**
 * @brief
 * 	Used to initialize the peripherals
 *
 *
 * @details
 * 	Calls cmu_open to set up the ULFRCO clock to the Low Frequency clock tree
 * 	Calls gpio_open() to establish the output for the PWM
 * 	Calls app_letimer_pwm_open to create an instance if the pwm struct
 * 	Calls scheduler_open() to initialize the scheduler
 * 	Calls sleep_open to initialize the energy modes
 *
 *
 * @note
 * 	Application code should not change anything from the LETIMER driver and the clock or GPIO configuration
 *
 *
 ******************************************************************************/
void app_peripheral_setup(void){
	cmu_open();
	gpio_open();
	app_letimer_pwm_open(PWM_PER, PWM_ACT_PER);
	scheduler_open();
	sleep_open();
}


/***************************************************************************//**
 * @brief
 * 	Creates instance of the letimer_pwm_struct
 *
 *
 * @details
 * 	Initializes all of the elements required for the struct
 *
 *
 * @note
 * 	Function should not change blueprint of the struct
 *
 *
 * @param[in] period
 * 	desired period for PWM
 *
 *
 * @param[in] active period
 * 	desired active period for the PWM
 *
 ******************************************************************************/
void app_letimer_pwm_open(float period, float act_period){
	// Initializing LETIMER0 for PWM operation by creating the
	// letimer_pwm_struct and initializing all of its elements
	APP_LETIMER_PWM_TypeDef letimer_pwm_struct;
	letimer_pwm_struct.debugRun = false;
	letimer_pwm_struct.enable = false;
	letimer_pwm_struct.out_pin_route0 = LETIMER0_ROUTE_OUT0;
	letimer_pwm_struct.out_pin_route1 = LETIMER0_ROUTE_OUT1;
	letimer_pwm_struct.out_pin_0_en = LETIMER0_OUT0_EN;
	letimer_pwm_struct.out_pin_1_en = LETIMER0_OUT1_EN;
	letimer_pwm_struct.period = period;
	letimer_pwm_struct.active_period = act_period;
	letimer_pwm_struct.uf_irq_enable = true;
	letimer_pwm_struct.uf_evt = LETIMER0_UF_EVT;
	letimer_pwm_struct.comp0_irq_enable = false;
	letimer_pwm_struct.comp0_evt = LETIMER0_COMP0_EVT;
	letimer_pwm_struct.comp1_irq_enable = false;
	letimer_pwm_struct.comp1_evt = LETIMER0_COMP1_EVT;


	letimer_pwm_open(LETIMER0, &letimer_pwm_struct);
}

/***************************************************************************//**
 * @brief
 * 	This function cycles through the various energy modes.
 *
 * @details
 * 	Reads the current lowest energy  mode setting, unblocks this current energy mode setting if its less than 4, then
 * 	when the current mode reaches 4, the the energy mode is set back to EM0.
 *
 * @note
 * 	Function utilizes sleep_routines library
 *
 ******************************************************************************/

void scheduled_letimer0_uf_evt (void){
	EFM_ASSERT(get_scheduled_event() & LETIMER0_UF_EVT);
	remove_scheduled_event(LETIMER0_UF_EVT);
	uint32_t low_mode = current_block_energy_mode();
	sleep_unblock_mode(low_mode);
	if(low_mode < EM4){
		sleep_block_mode(low_mode + 1);
	}
	else{
		sleep_block_mode(EM0);
	}
}

/***************************************************************************//**
 * @brief
 * 	Removes scheduled COMP0 event
 *
 * @details
 * 	Function asserts that interrupts are disabled for COMP0
 *
 * @note
 * 	Event is still removed even though interrupts are disabled
 *
 *
 ******************************************************************************/

void scheduled_letimer0_comp0_evt (void){
	remove_scheduled_event(LETIMER0_COMP0_EVT);
	EFM_ASSERT(false);
}

/***************************************************************************//**
 * @brief
 * 	Removes scheduled COMP0 event
 *
 * @details
 * 	Function asserts that interrupts are disabled for COMP0
 *
 * @note
 * 	Event is still removed even though interrupts are disabled
 *
 *
 ******************************************************************************/

void scheduled_letimer0_comp1_evt (void){
	remove_scheduled_event(LETIMER0_COMP1_EVT);
	EFM_ASSERT(false);
}


