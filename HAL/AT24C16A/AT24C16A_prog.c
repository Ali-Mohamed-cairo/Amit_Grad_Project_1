/*
 * AT24C16A_prog.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Ali Mohamed
 */

#include <AT24C16A/AT24C16A_interface.h>

void H_AT24C16A_vid_EEPROMInit(void)
{
	M_I2C_vid_I2CInit();
}
void H_AT24C16A_vid_EEPROMWrite(u8 Copy_U8_PageNumber, u8 Copy_U8_ByteNumber, u8 Copy_U8_Data)
{
	M_I2C_vid_I2CStartCondition();
	M_I2C_vid_I2CSendSlaveAddressWrite(0x50 | Copy_U8_PageNumber);
	M_I2C_vid_I2CSendByte(Copy_U8_ByteNumber);  /*TO SEND BYTE NUMBER*/
	M_I2C_vid_I2CSendByte(Copy_U8_Data);  /*TO SEND Data       */
	M_I2C_vid_I2CStopCondition();
}
u8 H_AT24C16A_vid_EEPROMRead(u8 Copy_U8_PageNumber, u8 Copy_U8_ByteNumber)
{
	u8 Local_U8_Data;
	M_I2C_vid_I2CStartCondition();
	M_I2C_vid_I2CSendSlaveAddressWrite(0x50 | Copy_U8_PageNumber);
	M_I2C_vid_I2CSendByte(Copy_U8_ByteNumber);
	M_I2C_vid_I2CRepeatCondition();
	M_I2C_vid_I2CSendSlaveAddressRead(0x50 | Copy_U8_PageNumber);
	Local_U8_Data = M_I2C_vid_I2CReadByte();
	M_I2C_vid_I2CStopCondition();
	return Local_U8_Data;
}
