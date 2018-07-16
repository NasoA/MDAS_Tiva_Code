#define PART_TM4C123GH6PM 1;

#include <stdint.h>
#include <stdbool.h>

#include "Globals_and_Defines.h"
#include "initialization.h"

#include "SensorInput.h"

#include "Switches_PORTF.h"
#include "Linear_Actuator.h"

//Linear actuator scaling
uint32_t calc_linear_act_pos(uint32_t position)
{
	return position;
}


/********************************************************************
 *
 * Drive by wire: Calculating position/moving actuators
 * ADC_Values[]: 0- Steering | 1 - Throttle | 2 - Brake act
 * 
 ********************************************************************/
void DriveByWireIO(void)                                         
{

	//moveto_throttle(throttle_pos);
	//moveto_lin_act(linear_act_pos);
}

