/*
 * server.h
 *
 *  Created on: Aug 23, 2023
 *      Author: yohanes
 */

#ifndef INC_SERVER_H_
#define INC_SERVER_H_

#include "main.h"
#include "usart.h"

void server_init(UART_HandleTypeDef *huart);
void server_receive_restart(void);
void server_receive_callback(UART_HandleTypeDef *huart);
void server_transmit_routine(void);

#endif /* INC_SERVER_H_ */
