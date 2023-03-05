/*
 * I2C_private.h
 *
 *  Created on: Oct 7, 2022
 *      Author: Ali Mohamed
 */

#ifndef MCAL_I2C_I2C_PRIVATE_H_
#define MCAL_I2C_I2C_PRIVATE_H_


#define I2C_MASTER_MODE          0
#define I2C_SLAVE_MODE           0

#define TWAR_REG     (*(volatile u8*)0x22)
#define TWBR_REG     (*(volatile u8*)0x20)
#define TWCR_REG     (*(volatile u8*)0x56)
#define TWDR_REG     (*(volatile u8*)0x23)
#define TWSR_REG     (*(volatile u8*)0x21)

/*TWCR_REG BITS*/
#define TWINT_BIT    7
#define TWSTA_BIT    5
#define TWSTO_BIT    4
#define TWEN_BIT     2

#define DISABLE      0
#define ENABLE       1

#define I2C_STILL_PROCESSING                        0
#define I2C_START_CONDTION_HAS_BEEN_TRANSMITTED     0x08
#define I2C_DATA_BYTE_TRASMITTED_ACK_REC            0x28
#endif /* MCAL_I2C_I2C_PRIVATE_H_ */
