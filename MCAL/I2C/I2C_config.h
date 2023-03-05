/*
 * I2C_config.h
 *
 *  Created on: Oct 7, 2022
 *      Author: Ali Mohamed
 */

#ifndef MCAL_I2C_I2C_CONFIG_H_
#define MCAL_I2C_I2C_CONFIG_H_

#include "I2C_private.h"

/*
 * SELECT THE I2C_MODE : 1 - I2C_MASTER_MODE
 *                       2 - I2C_SLAVE_MODE
 */
#define I2C_MODE            I2C_MASTER_MODE
/*
 * SELECT THE I2C SLAVE_ADDRESS : CHOOSE WITHIN THE RANGE [1, 119]
 */
#define SLAVE_ADDRESS       1

/*
 * SELECT TO ENABLE OR DISABLE THE I2C_GENERAL_CALL : 1 - DISABLE
 *                                                    2 - ENABLE
 */
#define I2C_GENERAL_CALL    DISABLE

#endif /* MCAL_I2C_I2C_CONFIG_H_ */
