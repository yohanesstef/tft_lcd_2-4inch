/*
 * server.c
 *
 *  Created on: Aug 23, 2023
 *      Author: yohanes
 */

#include "server.h"

#define MAX_RX_PACKET_LEN 2
#define TX_SERVER_LEN 5

UART_HandleTypeDef *server_huart;

uint8_t rxbuff[MAX_RX_PACKET_LEN + 3];
uint8_t txbuff[TX_SERVER_LEN] = {'i', 't', 's', 'o', 'k'};

uint8_t callback_flag;
uint8_t init_flag;
uint8_t receive_flag;
uint8_t restart_flag;
uint8_t transmit_flag;
uint8_t server_status;

void server_init(UART_HandleTypeDef *huart){
	server_huart = huart;
	HAL_UART_Receive_DMA(server_huart, rxbuff, MAX_RX_PACKET_LEN + 3);
	init_flag = 1;
}

void server_receive_restart(void){
	HAL_UART_DMAStop(server_huart);
	HAL_UART_Receive_DMA(server_huart, rxbuff, MAX_RX_PACKET_LEN + 3);
	restart_flag++;
}

void server_receive_callback(UART_HandleTypeDef *huart){
	if (huart->Instance != server_huart->Instance)return;
	if (rxbuff[0] == 'i' && rxbuff[1] == 't' && rxbuff[2] == 's'){
		server_status = 1;
	}
	else {
		server_status = 0;
		server_receive_restart();
//		HAL_UART_DMAStop(server_huart);
//		HAL_UART_Receive_DMA(server_huart, txbuff, MAX_RX_PACKET_LEN + 3);
	}
	callback_flag++;
}

void server_transmit_routine(void){
	static uint32_t delay = 0;
	if(HAL_GetTick() < delay + 10)return;
	delay = HAL_GetTick();
	txbuff[4]++;
	HAL_UART_Transmit_DMA(server_huart, txbuff, TX_SERVER_LEN);
	transmit_flag++;
}
