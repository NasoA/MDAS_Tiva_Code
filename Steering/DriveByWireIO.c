#define PART_TM4C123GH6PM 1;

#include <stdint.h>
#include <stdbool.h>

#include "Globals_and_Defines.h"
#include "initialization.h"

#include "Joystick.h"

#include "Switches_PORTF.h"
#include "Linear_Actuator.h"
#include "Steering_Actuator.h"
#include "Throttle.h"



/************************************************************************
 *
 * calc_steering_pos called in DriveByWireIO()
 * Used to calculate steering potion by scaling the input ADC value.
 * add Position by 2^11 (2048). 
 * Clear all bits but the last 12 via anding by 0x000000FFF
 * Logic shift left by 20 bits, Divide by 0x00020000 and multiply by 100
 * Add 360k
 *
 ************************************************************************/
int32_t calc_steering_pos(uint32_t position)
{
	int32_t	scaled_position = (((position + 2048)&0x00000FFF)<<20); 
    scaled_position = (scaled_position/131072)*100;               
    scaled_position += 360000;                                 
  return scaled_position;
}


/********************************************************************
 *
 * Drive by wire: Calculating position/moving actuators
 * ADC_Values[]: 0- Steering | 1 - Throttle | 2 - Brake act
 * 
 ********************************************************************/
void DriveByWireIO(uint32_t position)                                         
{
	int32_t steering_pos;

	steering_pos = calc_steering_pos(position);

	moveto_steering_act(steering_pos);

}

