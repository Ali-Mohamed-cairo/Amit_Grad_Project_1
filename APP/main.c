/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include <AT24C16A/AT24C16A_interface.h>
#include "BitMath.h"
#include "STD.h"
#include "DIO_Interface.h"
#include "LED_Interface.h"
#include "PB_Interface.h"
#include "SSD_Interface.h"
#include "WDT_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "GIE_Interface.h"
#include "ADC_Interface.h"
#include "Timer_Interface.h"
#include "Servo_Interface.h"
#include "ExtInt_Interface.h"
#include "UART_Interface.h"
#include "DCMotor_Interface.h"
#include "SPI_Interface.h"
#include "LM35_Interface.h"
#include <util/delay.h>

#define NUM_OF_WAVES  2



void A_Main_LCDPWMDrawer(u8, u8);
void A_Main_void_MineMicro();
void A_Main_void_ExternalMicro();
void A_Main_void_PoteniAsSource();
void A_Main_void_KeypadAsSource();
/*void A_Main_ExtInt0Execution(void);
void A_Main_ExtInt1Execution(void);
void A_Main_ExtInt2Execution(void);
void A_Main_Timer0Execution(void);*/


/* MASTER */
int main()
{
	M_Timer_Void_PWMInit(TIMER0_CHANNEL);
	M_UART_Void_UARTInit();
	M_ADC_Void_ADCInit();
	H_Lcd_Void_LCDInit();
	H_KeyPad_Void_KeyPadInit();
	M_DIO_Void_SetPinDirection(PA1_PIN, OUTPUT);
	M_DIO_Void_SetPinDirection(PA2_PIN, OUTPUT);
	M_DIO_Void_SetPinDirection(PC7_PIN, OUTPUT);
	M_DIO_Void_SetPinDirection(PD2_PIN, INPUT);
	u32 Local_U32_NumOfUsers = 0;
	u8 Local_U8_UserMode;
	u8 Local_U8_DutyCycle = 40;
	while(1)
	{
		Local_U8_UserMode = 0;
		H_Lcd_Void_LCDClear();
		if(Local_U32_NumOfUsers == 0)
		{
			H_Lcd_Void_LCDWriteString("Welcome");
			_delay_ms(2000);
			H_Lcd_Void_LCDClear();
		}
		H_Lcd_Void_LCDWriteString("Choose the mode");
		_delay_ms(2000);
		H_Lcd_Void_LCDClear();
		H_Lcd_Void_LCDWriteString("1-My-MC  2-Ex-MC");
		H_Lcd_Void_LCDGoTo(1, 0);
		H_Lcd_Void_LCDWriteString("3-Poten 4-Keypad");
		while(!(Local_U8_UserMode = H_KeyPad_U8_KeyPadRead() - 48));
		switch(Local_U8_UserMode)
		{
		case(1):
				A_Main_void_MineMicro();
				++Local_U32_NumOfUsers;
				break;
		case(2):
				A_Main_void_ExternalMicro();
				++Local_U32_NumOfUsers;
				break;
		case(3):
				A_Main_void_PoteniAsSource();
				++Local_U32_NumOfUsers;
				break;
		case(4):
				A_Main_void_KeypadAsSource();
				++Local_U32_NumOfUsers;
				break;
		default:
			H_Lcd_Void_LCDClear();
			H_Lcd_Void_LCDGoTo(0, 6);
			H_Lcd_Void_LCDWriteString("Invalid");
			_delay_ms(1000);
			break;
		}
		//A_Main_LCDPWMDrawer(Local_U8_DutyCycle);
		//while(1);
	}
	return 0;
}


//FIRST MODE
void A_Main_void_MineMicro()
{
	M_DIO_Void_SetPinValue(PA2_PIN, HIGH);
	u8 Local_U8_DutyCycle = 40;
	M_Timer_Void_PWMSetDutyCycle(TIMER0_CHANNEL, Local_U8_DutyCycle);
	M_Timer_Void_PWMStart(TIMER0_CHANNEL);
	A_Main_LCDPWMDrawer(Local_U8_DutyCycle, NUM_OF_WAVES);
	M_DIO_Void_SetPinValue(PA2_PIN, LOW);
}
//SECOND MODE
void A_Main_void_ExternalMicro()
{
	u8 Local_U8_ExtMCDutyCycle = 0;
	u8 Local_U8_NeededNumOfWaves = 0;
	M_UART_Void_UARTSend(1);
	Local_U8_ExtMCDutyCycle = M_UART_Void_UARTRec();
	_delay_ms(300);
	M_UART_Void_UARTSend(2);
	Local_U8_NeededNumOfWaves = M_UART_Void_UARTRec();
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDWriteString("No. of waves:");
	H_Lcd_Void_LCDWriteNumber(Local_U8_NeededNumOfWaves);
	_delay_ms(2000);
	A_Main_LCDPWMDrawer(Local_U8_ExtMCDutyCycle, Local_U8_NeededNumOfWaves);
	M_UART_Void_UARTSend(3);
}
//THIRD MODE
void A_Main_void_PoteniAsSource()
{
	u16 Local_U16_ADCReading = 0;
	f32 Local_U8_DutyCycle = 0;
	M_DIO_Void_SetPinValue(PA1_PIN, HIGH);
	M_ADC_Void_ADCInit();
	Local_U16_ADCReading = M_ADC_Void_ADCRead(ADC_CHANNEL_0);
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDWriteString("Reading : ");
	H_Lcd_Void_LCDWriteNumber(Local_U16_ADCReading);
	_delay_ms(2000);
	Local_U8_DutyCycle = (Local_U16_ADCReading / 1024.0) * 100;
	M_Timer_Void_PWMSetDutyCycle(TIMER0_CHANNEL, Local_U8_DutyCycle);
	M_Timer_Void_PWMStart(TIMER0_CHANNEL);
	A_Main_LCDPWMDrawer(Local_U8_DutyCycle, NUM_OF_WAVES);
	M_DIO_Void_SetPinValue(PA1_PIN, LOW);
}
void A_Main_void_KeypadAsSource()
{
	u8 Local_U8_Reading = 0;
	u8 Local_U8_NeededNumOfWaves = 0;
	u8 Local_U8_NeededDutyCycle  = 0;
	M_DIO_Void_SetPinValue(PC7_PIN, HIGH);
	H_Lcd_Void_LCDClear();
	H_Lcd_Void_LCDWriteString("Needed waves:");
	while(!(Local_U8_NeededNumOfWaves = H_KeyPad_U8_KeyPadRead() - 48));
	H_Lcd_Void_LCDWriteNumber(Local_U8_NeededNumOfWaves);
	H_Lcd_Void_LCDGoTo(1,0);
	H_Lcd_Void_LCDWriteString("Duty cycle:");
	while(!(Local_U8_NeededDutyCycle = H_KeyPad_U8_KeyPadRead() - 48));
	H_Lcd_Void_LCDWriteNumber(Local_U8_NeededDutyCycle);
	while((Local_U8_Reading = H_KeyPad_U8_KeyPadRead()) == 48);
	if(Local_U8_Reading != 'C')
	{
		H_Lcd_Void_LCDWriteNumber(Local_U8_Reading - 48);
		Local_U8_NeededDutyCycle = (Local_U8_NeededDutyCycle * 10) + (Local_U8_Reading - 48);
	}
	while((Local_U8_Reading = H_KeyPad_U8_KeyPadRead()) != 'C');
	M_Timer_Void_PWMSetDutyCycle(TIMER0_CHANNEL, Local_U8_NeededDutyCycle);
	M_Timer_Void_PWMStart(TIMER0_CHANNEL);
	A_Main_LCDPWMDrawer(Local_U8_NeededDutyCycle, Local_U8_NeededNumOfWaves);
	M_DIO_Void_SetPinValue(PC7_PIN, LOW);
}
void A_Main_LCDPWMDrawer(u8 Copy_U8_DutyCycle, u8 Copy_U8_NumOfWaves)
{
	u8 Local_U8_HighPeriod = 0;
	u8 Local_U8_LowPeriod  = 0;
	u8 Local_U8_Cursor = 0;
	u8 Local_U8_NumOfCharacter = 16 / Copy_U8_NumOfWaves;

	Local_U8_HighPeriod = (Copy_U8_DutyCycle * Local_U8_NumOfCharacter) / 100;
	Local_U8_LowPeriod  = Local_U8_NumOfCharacter- Local_U8_HighPeriod;
	if(Local_U8_HighPeriod == 0 || Local_U8_LowPeriod == 0)
	{
		H_Lcd_Void_LCDClear();
		H_Lcd_Void_LCDWriteString("Invalid required");
		H_Lcd_Void_LCDGoTo(1,0);
		H_Lcd_Void_LCDWriteString("number of waves");
		_delay_ms(2000);
		H_Lcd_Void_LCDClear();
		H_Lcd_Void_LCDWriteString("Enter lower");
		H_Lcd_Void_LCDGoTo(1,0);
		H_Lcd_Void_LCDWriteString("number of waves");
		_delay_ms(2000);
	}
	else
	{
		H_Lcd_Void_LCDClear();
		H_Lcd_Void_LCDWriteString("Frequancy:16 MHZ");
		_delay_ms(1500);
		H_Lcd_Void_LCDClear();
		H_Lcd_Void_LCDWriteString("Duty cycle : ");
		H_Lcd_Void_LCDWriteNumber(Copy_U8_DutyCycle);
		H_Lcd_Void_LCDWriteCharacter('%');
		_delay_ms(1500);
		H_Lcd_Void_LCDClear();
		for(u8 Local_U8_CountForWaves = Copy_U8_NumOfWaves; Local_U8_CountForWaves > 0; Local_U8_CountForWaves--)
		{
				u8 Local_U8_CountForHigh = 0;
				u8 Local_U8_CountForLow  = 0;
			for(; Local_U8_CountForHigh < Local_U8_HighPeriod; Local_U8_CountForHigh++)
			{
				H_Lcd_Void_LCDGoTo(0, Local_U8_Cursor);
				H_Lcd_Void_LCDWriteCharacter('_');
				Local_U8_Cursor++;
			}
			for(; Local_U8_CountForLow < Local_U8_LowPeriod; Local_U8_CountForLow++)
			{
				H_Lcd_Void_LCDGoTo(1, Local_U8_Cursor);
				if(Local_U8_CountForLow == 0)
					H_Lcd_Void_LCDWriteCharacter('L');
				else
					H_Lcd_Void_LCDWriteCharacter('_');
					Local_U8_Cursor++;
			}
			H_Lcd_Void_LCDWriteCharacter('|');
			Local_U8_Cursor++;
		}
		while(!(M_DIO_Void_GetPinValue(PD2_PIN) == 1));
		M_Timer_Void_PWMStop(TIMER0_CHANNEL);
	}
}



/*void A_Main_ExtInt0Execution(void)
{
	if(H_PB_U8_PBRead(PUSH_BUTTON_2_PIN) == 1)
		Global_U8_Stop = 1;
}
void A_Main_ExtInt1Execution(void)
{
	H_LED_Void_LedOn(LED0);
}
void A_Main_ExtInt2Execution(void)
{
	H_LED_Void_LedOn(LED0);
}

void A_Main_Timer0Execution(void)
{
	H_LED_Void_LedTog(LED0);
}*/





