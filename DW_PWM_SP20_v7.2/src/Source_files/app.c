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
 * @param[in]
 * 	desired period for PWM
 *
 *
 * @param[in]
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


	letimer_pwm_open(LETIMER0, &letimer_pwm_struct);
}


