/*
 * gps_M8N.c
 *
 *  Created on: Aug 28, 2023
 *      Author: yohanes
 */
#include "gps_M8N.h"

char GGA[100];
char RMC[100];

uint8_t ggaflag = -1;
uint8_t rmcflag = 1;

GPSSTRUCT gpsData;

void gps_GGA_routine(){
	if (Wait_for("GGA") == 1){
		Copy_upto("*", GGA);
		decodeGGA(GGA, &gpsData.ggastruct);
		ggaflag *= -1;
	}
//	if (Wait_for("RMC") == 1){
//		Copy_upto("*", RMC);
//		decodeRMC(RMC, &gpsData.rmcstruct);
//		rmcflag *= -1;
//	}
}


















