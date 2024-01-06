/******************************************************************************************/
/******************************************************************************************/
/******************************     Name   :  Abir Omara     ******************************/
/******************************     Date   :  23/12/2023     ******************************/
/******************************     SWC    :  ADC            ******************************/
/******************************   Version  :  1.0            ******************************/
/******************************************************************************************/
/******************************************************************************************/

/* Lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static void (*ADC_pfNotification)(u16) = NULL;

/*ADC busy flag*/
static u8 ADC_u8BusyFlag =0;
void ADC_voidInit (void)
{
	/*1- Vref =AVCC
	  2- Right Adjust
	  3- Disable AutoTrigger
	  4- Select CLK/64
	  5- Enable ADC*/
	CLR_BIT(ADC_u8_ADMUX,ADC_u8_ADMUX_REFS1);
	SET_BIT(ADC_u8_ADMUX,ADC_u8_ADMUX_REFS0);

	CLR_BIT(ADC_u8_ADMUX,ADC_u8_ADMUX_ADLAR);

	CLR_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADATE);

	SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADPS2);
	SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADPS1);
	CLR_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADPS0);

	SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADEN);

}

u8 ADC_u8GetDigitalValueSynchNonBlocking  (u8 Copy_u8ChannelNumb,u16 *Copy_pu16DigitalValue)
{

	u8 Local_u8ErrorState=STD_TYPES_OK;
	u32 Local_u32TimeOutCounter=0;
	if ((Copy_u8ChannelNumb <32) &&(Copy_pu16DigitalValue != NULL) )
	{

		/*clear MUX 4...0*/
		ADC_u8_ADMUX &= 0b11100000;
		/*select channel*/
		ADC_u8_ADMUX |= Copy_u8ChannelNumb;
		/*start conversion*/
		SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADSC);
		/*wait flag =1*/
		while ((GET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADIF) ==0) && (Local_u32TimeOutCounter<ADC_u32_TIME_OUT_MAX_VALUE))
		{
			Local_u32TimeOutCounter++;
		}
		//while (!GET_BIT(ADC_u8_ADCSRA_REG,4));
		if ((GET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADIF) !=0) /*(Local_u32TimeOutCounter<ADC_u32_TIME_OUT_MAX_VALUE)*/)
		{
			/*clear flag*/
			SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADIF);
			/*read digital value */
			*Copy_pu16DigitalValue=ADC_u16_ADC;
		}
		else
		{
			Local_u8ErrorState=STD_TYPES_NOK;
		}
	}

	else
	{
		Local_u8ErrorState=STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


u8 ADC_u8GetDigitalValueAsynch  (u8 Copy_u8ChannelNumb,void (*Copy_pfNotification)(u16))
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
	if ((Copy_u8ChannelNumb <32) &&(Copy_pfNotification != NULL)&& (ADC_u8BusyFlag == 0))
	{
		/*set flag to mae ADC is busy*/
			ADC_u8BusyFlag =1;
		/*update Global Pointer to a function*/
		ADC_pfNotification=Copy_pfNotification;
		/*Enable ADC Interrupt*/
		SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADIE);
		/*clear MUX 4...0*/
		ADC_u8_ADMUX &= 0b11100000;
		/*select channel*/
		ADC_u8_ADMUX |= Copy_u8ChannelNumb;
		/*start conversion*/
		SET_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADSC);
	}
	else
	{
		Local_u8ErrorState=STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 ADC_u8GetADCRegValue    (u16 *Copy_pu16ADCValue)
{
	u8 Local_u8ErrorState=STD_TYPES_OK;
		if (Copy_pu16ADCValue != NULL)
		{
		/*read ADC register*/
			*Copy_pu16ADCValue=ADC_u16_ADC;
		}
		else
		{
			Local_u8ErrorState=STD_TYPES_NOK;
		}
		return Local_u8ErrorState;
	}
/*Prototype for ADC ISR*/
void __vector_16 (void)   __attribute__((signal));
void __vector_16 (void)
{
	if (ADC_pfNotification != NULL)
	{
		/*clear flag */
		ADC_u8BusyFlag =0;
		/*clear PTE of ADC*/
		CLR_BIT(ADC_u8_ADCSRA,ADC_u8_ADCSRA_ADIE);
		/*call notification function*/
		ADC_pfNotification(ADC_u16_ADC);
	}
}
