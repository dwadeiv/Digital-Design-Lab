//***********************************************************************************
// Include files
//***********************************************************************************
#include "em_gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************

// LED0 pin is
#define	LED0_port					gpioPortF
#define LED0_pin					04u
#define LED0_default				false 	// off
// LED1 pin is
#define LED1_port					gpioPortF
#define LED1_pin					05u
#define LED1_default				false	// off
// SCL pin is
#define SI7021_SCL_PORT				gpioPortC
#define SI7021_SCL_PIN				11u
#define SI7021_SCL_default			true
// SDA pin is
#define SI7021_SDA_PORT				gpioPortC
#define SI7021_SDA_PIN				10u
#define SI7021_SDA_default			true
// Sensor enable pin is
#define SI7021_SENSOR_EN_PORT		gpioPortB
#define SI7021_SENSOR_EN_PIN		10u
#define SI7021_SENSOR_EN_default	true

//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
void gpio_open(void);

