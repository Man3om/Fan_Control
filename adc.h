/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the ADC driver
 *
 * Author: Abdelmonem Magdi
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/* Includes */
#include "std_types.h"
#define POLLING /* Using Interrupt or Polling */

/* Data Types*/
typedef enum
{
	F_cpu_2 = 1,F_cpu_4,F_cpu_8,F_cpu_16,F_cpu_32,F_cpu_64,F_cpu_128
}ADC_Prescaler;

typedef enum
{
	AREF,AVCC,Reserved,Internal
}ADC_ReferenceVolatge;

typedef struct
{
	ADC_Prescaler prescaler;
	ADC_ReferenceVolatge ref_volt ;
}ADC_configType;

/* Defines */
#define ADC_REF_VOLT_VALUE 2.56
#define ADC_MAXIMUM_VALUE 1023

/* Shared Variables */
#ifdef INTERRUPT
extern volatile uint16 g_adcdata ;
#endif

/* Prototypes */
void ADC_init(const ADC_configType * config_ptr);

#ifdef INTERRUPT
void ADC_readChannel(uint8 pin_num);
#endif

#ifdef POLLING
uint16 ADC_readChannel(uint8 pin_num);
#endif

#endif /* ADC_H_ */
