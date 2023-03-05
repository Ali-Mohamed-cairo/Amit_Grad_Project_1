/*
 * AT24C16A_interface.h
 *
 *  Created on: Oct 8, 2022
 *      Author: Ali Mohamed
 */

#ifndef HAL_AT24C16A_AT24C16A_INTERFACE_H_
#define HAL_AT24C16A_AT24C16A_INTERFACE_H_

#include "I2C_interface.h"

void H_AT24C16A_vid_EEPROMInit(void);
void H_AT24C16A_vid_EEPROMWrite(u8, u8, u8);
u8 H_AT24C16A_vid_EEPROMRead(u8, u8);

#endif /* HAL_AT24C16A_AT24C16A_INTERFACE_H_ */
