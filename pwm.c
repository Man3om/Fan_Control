/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Abdelmonem Magdi
 *
 *******************************************************************************/
#include "pwm.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/interrupt.h>

/*******************************************************************************
 * Description:Initialization PWM
 * Input: Duty Cycle
 * Return: Void
 *******************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle)
{
	uint8 targetTicks = (uint8)(((uint16)(duty_cycle * 256))/100) ;

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01) ;

	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	TCNT0 = 0 ;

	OCR0 = targetTicks;

	SET_BIT(TIMSK,OCIE0); /* Enable Compare Match interrupt */
}
