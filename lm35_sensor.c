/******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Abdelmonem Magdi
 *
 *******************************************************************************/

#include <util/delay.h> /* For the delay functions */
#include "lm35_sensor.h"
#include "adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

#ifdef POLLING
	uint16 Digital =  0 ;

	/* Read ADC channel where the temperature sensor is connected */
	Digital = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)Digital*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
#endif

#ifdef INTERRUPT

	/* Read ADC channel where the temperature sensor is connected */
	ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Make delay for some time until g_adcResult value is updated with the ADC interrupt */
	_delay_ms(5);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)g_adcdata*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

#endif

	return temp_value;
}

