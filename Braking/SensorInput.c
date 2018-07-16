#define PART_TM4C123GH6PM 1;

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

#include "Globals_and_Defines.h"


//ADC_values[0] Brake Pressure Sensor
//ADC_values[1] Reserved
//ADC_values[2] Reserved

void get_sensor_inputs(uint32_t ADC_values[])
{
	ADCIntClear(ADC0_BASE, 1);
	
	//Start conversion sequence
	ADCProcessorTrigger(ADC0_BASE, 1);
	while(!ADCIntStatus(ADC0_BASE, 1, false))
	{
	}
	
	ADCSequenceDataGet(ADC0_BASE, 1, ADC_values);
}


void ADC0_Setup(void)
{
	//Enable PORTB
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
	{}
	//Enable PORTD
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
	{}
	//Enable PORTE
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
	{}

	//Configure PORT pins for analog input
	//PB5 brake sensor   CH11
	//PD3 E-STOP
	//PE3 Reserved

	GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
		
	//Enable ADC0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
	{}
	
	//Setup ADC0 sequencer 1 to read the three controller inputs
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH11);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH4);
	ADCSequenceStepConfigure(ADC0_BASE,1,2,ADC_CTL_CH2|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);
}

