//***********************************************************************************
// Include files
//***********************************************************************************
#include "cmu.h"

//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// prototypes
//***********************************************************************************
void cmu_open(void){
//		CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFXO);
		// Enabling the High Frequency Peripheral Clock Tree
		CMU_ClockEnable(cmuClock_HFPER, true);

		// By default, LFRCO is enabled, disable the LFRCO oscillator
		CMU_OscillatorEnable(cmuOsc_LFRCO, false, false);	// using LFXO or ULFRCO

		// Route LF clock to the LF clock tree
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);  // route ULFRCO to proper Low Freq clock tree
		CMU_ClockEnable(cmuClock_CORELE, true);
//		CMU_ClockEnable(cmuClock_LFA, true);

		// No requirement to enable the ULFRCO oscillator.  It is always enabled in EM0-4H

		CMU_OscillatorEnable(cmuOsc_LFXO , false, false);		// Disable LFXO


}

