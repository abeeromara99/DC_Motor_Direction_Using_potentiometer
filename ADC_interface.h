/******************************************************************************************/
/******************************************************************************************/
/******************************     Name   :  Abir Omara     ******************************/
/******************************     Date   :  23/12/2023     ******************************/
/******************************     SWC    :  ADC           ******************************/
/******************************   Version  :  1.0            ******************************/
/******************************************************************************************/
/******************************************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_u8_CHANNEL_0     0
#define ADC_u8_CHANNEL_1     1
#define ADC_u8_CHANNEL_2     2
#define ADC_u8_CHANNEL_3     3
#define ADC_u8_CHANNEL_4     4
#define ADC_u8_CHANNEL_5     5
#define ADC_u8_CHANNEL_6     6
#define ADC_u8_CHANNEL_7     7

#define ADC_u8_ADMUX_REFS1            7
#define ADC_u8_ADMUX_REFS0            6
#define ADC_u8_ADMUX_ADLAR            5

#define ADC_u8_ADCSRA_ADEN            7
#define ADC_u8_ADCSRA_ADSC            6
#define ADC_u8_ADCSRA_ADATE           5
#define ADC_u8_ADCSRA_ADIF            4
#define ADC_u8_ADCSRA_ADIE            3
#define ADC_u8_ADCSRA_ADPS2           2
#define ADC_u8_ADCSRA_ADPS1           1
#define ADC_u8_ADCSRA_ADPS0           0



void ADC_voidInit (void);

u8 ADC_u8GetDigitalValueSynchNonBlocking  (u8 Copy_u8ChannelNumb,u16 *Copy_pu16DigitalValue);

u8 ADC_u8GetDigitalValueAsynch            (u8 Copy_u8ChannelNumb,void (*Copy_pfNotification)(u16));

u8 ADC_u8GetADCRegValue                   (u16 *Copy_pu16ADCValue);

#endif
