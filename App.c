/******************************************************************************
 *
 * Layer: Application Layer
 *
 * File Name: App.c
 *
 * Description: Source file for the Application Layer
 *
 * Author: Abdelmonem Magdi
 *
 *******************************************************************************/

#include "lcd.h"
#include "lm35_sensor.h"
#include "adc.h"
#include "common_macros.h"
#include "dc_motor.h"
#include <util/delay.h>


int main(void)
{
	/* Configure ADC Clock Type(Pre-scaler = 8) & Source Type(Internal) */
	ADC_configType configiration = {F_cpu_8 , Internal} ;

	uint8 Temp = 0 ;

	LCD_init(); /* Initialization LCD Module */
	ADC_init(&configiration); /* Initialization ADC Module */
	DcMotor_init(); /* Initialization DC Motor Module */

	LCD_displayString("Fan is OFF");
	LCD_displayStringRowColumn(1,0 , "Temp =     C");

	while(1)
	{
		Temp = LM35_getTemperature();

		if(Temp >= 120)
		{
			LCD_displayStringRowColumn(0,7 , "ON "); /* Display Motor State */
			LCD_moveCursor(1,7);
			LCD_intgerToString(Temp); /* Display Temperature */

			DcMotor_Rotate(100, CW); /* Fan Rotates With Maximum Speed */
		}
		else if((Temp >= 90) && (Temp <120))
		{
			LCD_displayStringRowColumn(0,7 , "ON "); /* Display Motor State */
			LCD_moveCursor(1,7);
			if(Temp >= 100)
			{
				LCD_intgerToString(Temp); /* Display Temperature */
			}
			else
			{
				LCD_intgerToString(Temp); /* Display Temperature */
				LCD_displayCharacter(' ');
			}

			DcMotor_Rotate(75, CW); /* Fan Rotates With 75% Speed */
		}
		else if((Temp >= 60) && (Temp < 90))
		{
			LCD_displayStringRowColumn(0,7 , "ON "); /* Display Motor State */
			LCD_moveCursor(1,7);
			LCD_intgerToString(Temp); /* Display Temperature */

			DcMotor_Rotate(50, CW); /* Fan Rotates With 50% Speed */
		}
		else if((Temp >= 30) && (Temp < 60))
		{
			LCD_displayStringRowColumn(0,7 , "ON "); /* Display Motor State */
			LCD_moveCursor(1,7);
			LCD_intgerToString(Temp); /* Display Temperature */

			DcMotor_Rotate(25, CW); /* Fan Rotates With 25% Speed */
		}
		else
		{
			LCD_displayStringRowColumn(0,7 , "OFF"); /* Display Motor State */
			LCD_moveCursor(1,7);

			if(Temp >= 10)
			{
				LCD_intgerToString(Temp); /* Display Temperature */
			}
			else
			{
				LCD_intgerToString(Temp); /* Display Temperature */
				LCD_displayCharacter(' ');
			}

			DcMotor_Rotate(0, OFF); /* Fan Turn OFF */
		}
	}
}
