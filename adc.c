 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Abdelmonem Magdi
 *
 *******************************************************************************/

#include "adc.h"
#include "common_macros.h"
#include <avr/io.h>

#ifdef INTERRUPT
#include <avr/interrupt.h>
volatile uint16 g_adcdata = 0 ; /* Global Variable to Store ADC Digital Value*/


/***************************************************************************
 * Description: ISR Function For ADC Interrupt
 ***************************************************************************/
ISR(ADC_vect)
{
	g_adcdata = ADC ;
}
#endif

/****************************************************************************
 * Description: Initialization ADC Function
 * Input: Pointer to Structure
 * Return: Void
 ***************************************************************************/
void ADC_init(const ADC_configType * config_ptr)
{
	/*
	 *  ADLAR = 0
	 *  MUX4..0 = 00000
	 */
	ADMUX = 0 ;

	/* Using AREF => REFS1 = 0 REFS0 = 0*/
	ADMUX = (ADMUX & 0x3F) | ((config_ptr->ref_volt)<<6) ;

	/*
	 *  Enable ADC => ADEN = 1
	 *  Disable ADC Interrupt => ADIE = 0
	 */
	ADCSRA = (1<<ADEN) ;

	/* Pre-Scaler = 8  => ADPS0 = 1 /  ADPS1 = 1 / ADPS2 = 0 */
	ADCSRA = (ADCSRA & 0xF8) | (config_ptr->prescaler) ;

#ifdef INTERRUPT
	SET_BIT(ADCSRA,ADIE) ;  /* Enable ADC Interrupt => ADIE = 1 */
#endif
}

#ifdef POLLING
/****************************************************************************
 * Description: Read ADC Channel Function
 * Input: ADC Channel
 * Return: ADC Register
 ***************************************************************************/
uint16 ADC_readChannel(uint8 pin_num)
{
	ADMUX = (ADMUX & 0xE0) | ( pin_num & 0x1F ); /* insert Channel */

	SET_BIT(ADCSRA,ADSC) ; /* Start Conversion */

	while(BIT_IS_CLEAR(ADCSRA,ADIF)) ; /* Waiting till ADC Flag = 1 */

	SET_BIT(ADCSRA , ADIF) ; /* Clear ADC Flag => ADIF = 1 */

	return ADC ; /* Return ADC Register */
}
#endif

#ifdef INTERRUPT
/****************************************************************************
 * Description: Read ADC Channel Function
 * Input: ADC Channel
 * Return: Void
 ***************************************************************************/
void ADC_readChannel(uint8 pin_num)
{
	ADMUX = (ADMUX & 0xE0) | ( pin_num & 0x1F ); /* insert Channel */

	SET_BIT(ADCSRA,ADSC) ; /* Start Conversion */
}
#endif
