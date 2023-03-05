/*
 * I2C_prog.c
 *
 *  Created on: Oct 7, 2022
 *      Author: Ali Mohamed
 */

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"



void M_I2C_vid_I2CInit(void)
{
#if   I2C_MODE == I2C_MASTER_MODE
	 //TO SELECT THE FSCL -> 400HZ
	 TWBR_REG = 12;
#elif I2C_MODE == I2C_SLAVE_MODE
	 TWAR_REG = (I2C_SLAVE_ADDRESS << 0x01) | I2C_GENERAL_CALL;
#endif
	 //ENABLE THE I2C CIRCUIT
	 SET_BIT(TWCR_REG, TWEN_BIT);
}
void M_I2C_vid_I2CStartCondition(void)
{
	SET_BIT(TWCR_REG, TWSTA_BIT);
	SET_BIT(TWCR_REG, TWINT_BIT);   /*TO CLEAR THE FLAG*/
	while(GET_BIT(TWCR_REG, TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != I2C_START_CONDTION_HAS_BEEN_TRANSMITTED);
}
void M_I2C_vid_I2CStopCondition(void)
{
	SET_BIT(TWCR_REG, TWSTO_BIT);
	SET_BIT(TWCR_REG, TWINT_BIT);   /*TO CLEAR THE FLAG*/
}
void M_I2C_vid_I2CRepeatCondition(void)
{
	SET_BIT(TWCR_REG, TWSTA_BIT);
	SET_BIT(TWCR_REG, TWINT_BIT);  /*TO CLEAR THE FLAG*/
	while(GET_BIT(TWCR_REG, TWINT_BIT) == I2C_STILL_PROCESSING);
}
void M_I2C_vid_I2CSendSlaveAddressWrite(u8 Copy_U8_SlaveAddress)
{
	TWDR_REG = (Copy_U8_SlaveAddress << 0x01);
	SET_BIT(TWCR_REG, TWINT_BIT);   /*TO CLEAR THE FLAG*/
	while(GET_BIT(TWCR_REG, TWINT_BIT) == I2C_STILL_PROCESSING);
}
void M_I2C_vid_I2CSendSlaveAddressRead(u8 Copy_U8_SlaveAddress)
{
	TWDR_REG = (Copy_U8_SlaveAddress << 0x01) | 0x01;
	CLR_BIT(TWCR_REG, TWSTA_BIT);
	SET_BIT(TWCR_REG, TWINT_BIT);   /*TO CLEAR THE FLAG*/
	while(GET_BIT(TWCR_REG, TWINT_BIT) == I2C_STILL_PROCESSING);
}
void M_I2C_vid_I2CSendByte(u8 Copy_U8_Data)
{
	u32 Local_U32_Counter = 0;
	TWDR_REG = Copy_U8_Data;
	CLR_BIT(TWCR_REG, TWSTA_BIT);
	SET_BIT(TWCR_REG, TWINT_BIT);   /*TO CLEAR THE FLAG*/
	while(GET_BIT(TWCR_REG, TWINT_BIT) == I2C_STILL_PROCESSING);
	while(Local_U32_Counter < 2000000)
	{
		if((TWSR_REG & 0xF8) == I2C_DATA_BYTE_TRASMITTED_ACK_REC)
			break;
		Local_U32_Counter++;
	}
}
u8 M_I2C_vid_I2CReadByte(void)
{
	CLR_BIT(TWCR_REG, TWSTA_BIT);
	SET_BIT(TWCR_REG, TWINT_BIT);   /*TO CLEAR THE FLAG*/
	while(GET_BIT(TWCR_REG, TWINT_BIT) == I2C_STILL_PROCESSING);
	return TWDR_REG;
}
