/*
 * ADC_ass1.c
 *
 *  Created on: Jan 2, 2024
 *      Author: Abir Omara
 */


/* Lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define F_CPU   8000000UL

/* MCAL */
#include "DIO_interface.h"
#include "ADC_interface.h"


/* HAL */
#include "lcd_interface.h"


void Motor_cw (void);
void Motor_ccw (void);
void STOP_MOTOR (void);

int main ()
{
	DIO_voidInit();
	ADC_voidInit();
	LCD_voidInt();

	u16 Local_u16DigitalValue,Local_u16AnalogValue,Local_u16OldValue;
	u8 Hamosha[7]=
	{
			0b00001110,
			0b00001110,
			0b00000100,
			0b00001110,
			0b00010101,
			0b00001110,
			0b00001010,
			0b00000000
	};




	Local_u16OldValue = 0 ;
	u8 local_u8pos = 0;

	while (1)
	{

		ADC_u8GetDigitalValueSynchNonBlocking(ADC_u8_CHANNEL_0,&Local_u16DigitalValue);

		Local_u16AnalogValue=(u16) ((Local_u16DigitalValue*5000UL)/1024);


		if (Local_u16OldValue != Local_u16AnalogValue)
		{
			LCD_voidClearDisplay();
			/*
			local_u8pos = Local_u16AnalogValue % 312;
			//LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,local_u8pos);
			LCD_u8GoToXY(0,1);
			LCD_voidWriteNumber(local_u8pos);
			LCD_u8GoToXY(LCD_u8_LINE2,0);
			LCD_voidWriteNumber(Local_u16AnalogValue);
			Local_u16OldValue = Local_u16AnalogValue;
			 */
		}

		if (Local_u16AnalogValue <= 312)
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,0);
			Motor_ccw();
		}
		else if ((Local_u16AnalogValue > 312) &&(Local_u16AnalogValue <= 625))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,1);
			Motor_ccw();
		}
		else if ((Local_u16AnalogValue > 625) &&(Local_u16AnalogValue <= 937))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,2);
			Motor_ccw();
		}
		else if ((Local_u16AnalogValue > 937) &&(Local_u16AnalogValue <= 1250))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,3);
			Motor_ccw();
		}
		else if ((Local_u16AnalogValue > 1250) &&(Local_u16AnalogValue <= 1562))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,4);
			Motor_ccw();
		}
		else if ((Local_u16AnalogValue > 1562) &&(Local_u16AnalogValue <= 1875))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,5);
			Motor_ccw();
		}
		else if ((Local_u16AnalogValue > 1875) &&(Local_u16AnalogValue <= 2187))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,6);
			STOP_MOTOR();
		}
		else if ((Local_u16AnalogValue > 2187) &&(Local_u16AnalogValue <= 2500))
		{
			//LCD_voidClearDisplay();
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,7);
			STOP_MOTOR();
		}
		else if ((Local_u16AnalogValue > 2500) &&(Local_u16AnalogValue <= 2812))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,8);
			STOP_MOTOR();
		}
		else if ((Local_u16AnalogValue > 2812) &&(Local_u16AnalogValue <= 3125))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,9);
			STOP_MOTOR();
		}
		else if ((Local_u16AnalogValue > 3125) &&(Local_u16AnalogValue <= 3437))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,10);
			Motor_cw();
		}
		else if ((Local_u16AnalogValue > 3437) &&(Local_u16AnalogValue <= 3750))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,11);
			Motor_cw();
		}
		else if ((Local_u16AnalogValue > 3750) &&(Local_u16AnalogValue <= 4062))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,12);
			Motor_cw();
		}
		else if ((Local_u16AnalogValue > 4062) &&(Local_u16AnalogValue <= 4375))
		{
			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,13);
			Motor_cw();
		}
		else if ((Local_u16AnalogValue > 4375) &&(Local_u16AnalogValue <= 4687))
		{

			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,14);
			Motor_cw();
		}

		else if (Local_u16AnalogValue > 4687)
		{

			LCD_voidWriteSpecialChar(1,&Hamosha,LCD_u8_LINE1,15);
			Motor_cw();
		}
		LCD_u8GoToXY(LCD_u8_LINE2,0);
		LCD_voidWriteNumber(Local_u16AnalogValue);
		Local_u16OldValue=Local_u16AnalogValue;

	}

	return 0;
}


void Motor_cw (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN6,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN7,DIO_u8_PIN_LOW);
}
void Motor_ccw (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN6,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN7,DIO_u8_PIN_HIGH);
}

void STOP_MOTOR (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN6,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTC,DIO_u8_PIN7,DIO_u8_PIN_LOW);
}
