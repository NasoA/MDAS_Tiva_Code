#define PART_TM4C123GH6PM 1;

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"

#include "Globals_and_Defines.h"
	

void CAN_Setup(void)
{
	//Enable PORTE
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
	{}

	// Configure the GPIO pin muxing to select CAN0 functions for these pins.
	// This step selects which alternate function is available for these pins.
	GPIOPinConfigure(GPIO_PE4_CAN0RX);
	GPIOPinConfigure(GPIO_PE5_CAN0TX);

	//Configure the pins for CAN
	GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	
	// Enable the CAN0 module.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0))
	{} 
	CANInit(CAN0_BASE);

	// 250Kbit CAN speed
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 250000);


	CANEnable(CAN0_BASE);
		
}


void sendSteeringData(uint32_t steering) // will have to add ,modes here
{
	tCANMsgObject sMsgObjectTx;
	uint8_t pui8BufferOut[8];
  //pui8BufferOut[0] = MODES
	pui8BufferOut[1] = (steering&0x000000FF);
	pui8BufferOut[2] = (steering&0x0000FF00)>>8;
	pui8BufferOut[3] = (steering&0x00FF0000)>>16;
	pui8BufferOut[4] = (steering&0xFF000000)>>24;
		
	//Configure transmit of message object.
	sMsgObjectTx.ui32MsgID =  steering_board_address;
	sMsgObjectTx.ui32Flags = 0;
	sMsgObjectTx.ui32MsgLen = 8;
	sMsgObjectTx.pui8MsgData = pui8BufferOut;
	
	//Send out data on CAN
	CANMessageSet(CAN0_BASE, 1, &sMsgObjectTx, MSG_OBJ_TYPE_TX);
}

void sendThrottleData(uint32_t throttle)
{
	tCANMsgObject sMsgObjectTx;
	uint8_t pui8BufferOut[8];

	pui8BufferOut[2] = (throttle&0x000000FF);
	pui8BufferOut[3] = (throttle&0x0000FF00)>>8;
	pui8BufferOut[4] = (throttle&0x00FF0000)>>16;
	pui8BufferOut[5] = (throttle&0xFF000000)>>24;
		
	//Configure transmit of message object.
	sMsgObjectTx.ui32MsgID =  throttle_board_address;
	sMsgObjectTx.ui32Flags = 0;
	sMsgObjectTx.ui32MsgLen = 8;
	sMsgObjectTx.pui8MsgData = pui8BufferOut;
	
	//Send out data on CAN
	CANMessageSet(CAN0_BASE, 1, &sMsgObjectTx, MSG_OBJ_TYPE_TX);
}



//TBD
void sendBrakeData(uint32_t brake)
{
	tCANMsgObject sMsgObjectTx;
	uint8_t pui8BufferOut[8];

	pui8BufferOut[2] = (brake&0x000000FF);
	pui8BufferOut[3] = (brake&0x0000FF00)>>8;
	pui8BufferOut[4] = (brake&0x00FF0000)>>16;
	pui8BufferOut[5] = (brake&0xFF000000)>>24;
		
	//Configure transmit of message object.
	sMsgObjectTx.ui32MsgID =  brake_board_address;
	sMsgObjectTx.ui32Flags = 0;
	sMsgObjectTx.ui32MsgLen = 8;
	sMsgObjectTx.pui8MsgData = pui8BufferOut;
	
	//Send out data on CAN
	CANMessageSet(CAN0_BASE, 1, &sMsgObjectTx, MSG_OBJ_TYPE_TX);
}




