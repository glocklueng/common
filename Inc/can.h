/*
 * can.h
 *
 *  Created on: Mar 29, 2015
 *      Author: KabooHahahein
 */

#ifndef CAN_H_
#define CAN_H_

#include "stm32f0xx_hal.h"
#include "stdbool.h"
#include "can_comm.h"

void canInit();
HAL_StatusTypeDef canStartReceiving();
HAL_StatusTypeDef sendCanMessage(CAN_HandleTypeDef *hcan, int id, int length, uint8_t *data);
//bool sendCanMessage(const uint16_t id, const uint8_t *data, const uint8_t length);
//bool sendCanMessageTimeoutMs(const uint16_t id, const uint8_t *data,
                             //const uint8_t length, const uint32_t timeout);

#endif /* CAN_H_ */
