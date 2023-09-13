/*
 * lora.c
 *
 *  Created on: Aug 24, 2023
 *      Author: yohanes
 */

#include "lora.h"


#define LORA_SERIAL_LEN 15

UART_HandleTypeDef *lora_huart;

lora_t lora;
lora_data_t lora_data_tx;
lora_data_t lora_data_rx;

uint8_t txdummy[5] = {'i','t','s','o','k'};
uint8_t rxdummy[5];

uint8_t lora_txbuff[LORA_SERIAL_LEN];
uint8_t lora_tx_gps[23] = {'i','t','s'};
uint8_t lora_rxbuff[LORA_SERIAL_LEN];
uint8_t lora_param[6];
uint8_t lora_dummy_rxbuff;
uint8_t aux;
float coordinates[2];

//uint8_t lora_gps_txbuf[]

char coordinates_buf[4];

extern GPSSTRUCT gpsData;

void lora_init(UART_HandleTypeDef *huart){
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);
	lora_huart = huart;
	lora_read_model_data();
	lora_set_ADDH(0);
	lora_set_ADDL(0);
	lora_set_speed(0b00011000);
	lora_set_channel(0b00000110);
	lora_set_option(0b01000100);
	lora_save_param(PERMANENT);
}

void lora_set_mode(LORA_Mode mode){
	HAL_Delay(LORA_PIN_RECOVER);
	switch(mode){
	case LORA_NORMAL_MODE:
		HAL_GPIO_WritePin(M0_Port, M0_Pin, 0);
		HAL_GPIO_WritePin(M1_Port, M1_Pin, 0);
		break;
	case LORA_WAKEUP_MODE:
		HAL_GPIO_WritePin(M0_Port, M0_Pin, 1);
		HAL_GPIO_WritePin(M1_Port, M1_Pin, 0);
		break;
	case LORA_POWERSAVING_MODE:
		HAL_GPIO_WritePin(M0_Port, M0_Pin, 0);
		HAL_GPIO_WritePin(M1_Port, M1_Pin, 1);
		break;
	case LORA_PROGRAM_MODE:
		HAL_GPIO_WritePin(M0_Port, M0_Pin, 1);
		HAL_GPIO_WritePin(M1_Port, M1_Pin, 1);
		break;
	}
	HAL_Delay(LORA_PIN_RECOVER);
	lora_clear_buffer();
	lora_complete_task(200);
}

void lora_read_model_data(){
	lora_txbuff[0] = 0xc1;
	lora_txbuff[1] = 0xc1;
	lora_txbuff[2] = 0xc1;

	memset(lora_param, 0, 6);

	lora_set_mode(LORA_PROGRAM_MODE);

	HAL_UART_Transmit_DMA(lora_huart, lora_txbuff, 3);
	HAL_UART_Receive_DMA(lora_huart, lora_param, 6);
	lora_set_mode(LORA_NORMAL_MODE);
}

void lora_receive_callback(UART_HandleTypeDef *huart){
	if (huart->Instance != lora_huart->Instance)return;
}

void lora_set_ADDH(uint8_t val){
	lora.addh = val;
}

void lora_set_ADDL(uint8_t val){
	lora.addl = val;
}

void lora_set_speed(uint8_t val){
	lora.speed = val;
}

void lora_set_channel(uint8_t val){
	lora.channel = val;
}

void lora_set_option(uint8_t val){
	lora.option = val;
}

void lora_save_param(uint8_t val){
	lora_txbuff[0] = val;
	lora_txbuff[1] = lora.addh;
	lora_txbuff[2] = lora.addl;
	lora_txbuff[3] = lora.speed;
	lora_txbuff[4] = lora.channel;
	lora_txbuff[5] = lora.option;

	lora_serial_transmit(lora_txbuff, 6);

	lora_read_model_data();
}

void lora_serial_transmit(uint8_t *data, uint8_t len){
	lora_set_mode(LORA_PROGRAM_MODE);
	HAL_UART_Transmit_DMA(lora_huart, data, len);
	lora_set_mode(LORA_NORMAL_MODE);
}

void lora_clear_buffer(){
	unsigned long time = HAL_GetTick();
	while(HAL_GetTick() < time + 500){
		HAL_UART_Receive_DMA(lora_huart, &lora_dummy_rxbuff, 1);
	}
}

void lora_complete_task(unsigned long timeout){
	unsigned long time = HAL_GetTick();
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);
	if (((unsigned long) (time + timeout)) == 0){
		time = 0;
	}
	while (HAL_GPIO_ReadPin(AUX_Port, AUX_Pin) == 0){
		HAL_Delay(LORA_PIN_RECOVER);
		if (HAL_GetTick() > time + timeout)break;
	}
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);
}

void lora_receive_routine(){
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);
	static uint32_t rxdelay = 0;
	if(HAL_GetTick() < rxdelay + 1000)return;
	rxdelay = HAL_GetTick();
	HAL_UART_Receive_DMA(lora_huart, rxdummy, 5);
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);
//	lora_complete_task(1000);
}

void lora_wireless_transmit_routine(){
//	memcpy(lora_data_tx.dummy, dummy, 5);
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);

	static uint32_t delay = 0;
	if(HAL_GetTick() < delay + 1000)return;
	delay = HAL_GetTick();
	lora_encode_gps();
	HAL_UART_Transmit_DMA(lora_huart, lora_tx_gps, 23);
	aux = HAL_GPIO_ReadPin(AUX_Port, AUX_Pin);
//	lora_complete_task(1000);
}

void lora_encode_gps(void){
	for (int x=0; x<2; x++){
		int front;
		float back;
		if(x == 0 ){
			front = floor(gpsData.ggastruct.lcation.latitude);
			back = 100.0*(gpsData.ggastruct.lcation.latitude - (float)front);
		}
		else if (x == 1){
			front = floor(gpsData.ggastruct.lcation.longitude);
			back = 100.0*(gpsData.ggastruct.lcation.longitude - (float)front);
		}
		coordinates[x] = (float)(front) + ((float)(back)/60.0);
	}
	uint8_t h = (uint8_t)(gpsData.ggastruct.tim.hour);
	uint8_t m = (uint8_t)(gpsData.ggastruct.tim.min);
	uint8_t s = (uint8_t)(gpsData.ggastruct.tim.sec);
	uint8_t v = (uint8_t)(gpsData.ggastruct.isfixValid);
	uint8_t n = (uint8_t)(gpsData.ggastruct.numofsat);

	memset(lora_tx_gps+3,0,16);
	memcpy(lora_tx_gps+3, &coordinates[0],4); //argumen ke-2 memcpy hanya works untuk 8bit, kalau lebih harus pake tanda & (yang diambil alamat memorinya)
	memcpy(lora_tx_gps+7, &gpsData.ggastruct.lcation.NS,1);
	memcpy(lora_tx_gps+8, &coordinates[1],4);
	memcpy(lora_tx_gps+12, &gpsData.ggastruct.lcation.EW,1);
//	memcpy(lora_tx_gps+13, (int8_t*)gpsData.ggastruct.tim.hour,1);
	memcpy(lora_tx_gps+13, &h,1);
	memcpy(lora_tx_gps+14, &m,1);
	memcpy(lora_tx_gps+15, &s,1);
	memcpy(lora_tx_gps+16, &v,1);
//	memcpy(lora_tx_gps+14, (unt8_t*)&gpsData.ggastruct.tim.min,1);
//	memcpy(lora_tx_gps+15, (uint8_t*)&gpsData.ggastruct.tim.sec,1);
//	memcpy(lora_tx_gps+16, (int8_t*)gpsData.ggastruct.isfixValid,1);
	memcpy(lora_tx_gps+17, &gpsData.ggastruct.alt.altitude,4);
	memcpy(lora_tx_gps+21, &gpsData.ggastruct.alt.unit,1);
//	memcpy(lora_tx_gps+22, (int8_t*)gpsData.ggastruct.numofsat,1);
	memcpy(lora_tx_gps+22, &n,1);
}
