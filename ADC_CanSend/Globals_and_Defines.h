
#ifndef _GLOBALSANDDEFINES_H_
#define _GLOBALSANDDEFINES_H_

/***********************
* Includes             *
***********************/
#include <stdint.h>
#include <stdbool.h>
/***********************
* Public Types         *
***********************/

/***********************
* Public Macros        *
***********************/


/***********************
* Public Defines       *
***********************/

//PORTF LED pins
#define PF2  (*((volatile uint32_t *)0x40025010))
#define PF3  (*((volatile uint32_t *)0x40025020))
#define PF4  (*((volatile uint32_t *)0x40025040))
	
#define PD7  (*((volatile uint32_t *)0x400070100))
	
	
//Drive by wire update rate in Hz
#define Update_Rate 10

//Throttle board CAN address
#define throttle_board_address 0x17FF00F0

#define steering_board_address 0x18FFFFFF

#define brake_board_address 0x18FFF0FF

#define px2_address 0x000F00F0
/***********************
* Public Constants     *
***********************/


/***********************
* Public Variables     *
***********************/
extern bool driveENABLE;
//Flag for tick timer.   
//Timer ISR sets to true.
//Scheduler sets to false 
extern bool g_tick_flag;

//Flag for starting drive by wire.   
//GPIO PORTF ISR sets to true.
//Scheduler sets to false 
extern bool g_start_flag;

//Flag for stopping drive by wire.   
//GPIO PORTF ISR sets to true.
//Scheduler sets to false 
extern bool g_stop_flag;

extern bool g_new_CAN_data;



/***********************
* Public Functions     *
***********************/


#endif /* _GLOBALSANDDEFINES_H_ */

