/*
 * drv8711.c
 *
 *  Created on: Mar 29, 2024
 *      Author: 4mzr2
 */
#include "drv8711.h"

void DRV8711_SPI_Write(uint16_t data, uint8_t reg){
	HAL_GPIO_WritePin(DRV8711_CS_Port, DRV8711_CS_Pin, GPIO_PIN_RESET);
	data |= ((uint16_t)reg << 12);
	data &= 0x7fff;
	HAL_SPI_Transmit(DRV8711_SPI, (uint8_t*)&data, 1, 10);
	HAL_GPIO_WritePin(DRV8711_CS_Port, DRV8711_CS_Pin, GPIO_PIN_SET);
}
uint16_t DRV8711_SPI_Read(uint8_t reg){

	uint16_t data = 0;
	uint16_t receive;
	HAL_GPIO_WritePin(DRV8711_CS_Port, DRV8711_CS_Pin, GPIO_PIN_RESET);
	data |= 0x8000;
	data |= ((uint16_t)reg << 12);
	HAL_SPI_Transmit(DRV8711_SPI, (uint8_t*)&data, 1, 10);
	HAL_SPI_Receive(DRV8711_SPI, (uint8_t*)&receive, 1, 10);
	HAL_GPIO_WritePin(DRV8711_CS_Port, DRV8711_CS_Pin, GPIO_PIN_SET);

	return receive;
}

/*union help
 * //	get_data temp = {0};//init
 * //	temp.frame = data;//give
 * //	data = temp.CTRL_d.DTIME;
 */

void DRV8711_init(void){
	get_data buff = {0};
	buff.CTRL_d.ENBL = 1;
	DRV8711_SPI_Write(buff.frame, CTRL_R);
}

void DRV8711_onestep(uint8_t dir){
	get_data buff = {0};
	buff.CTRL_d.ENBL = 1;
	buff.CTRL_d.RSTEP = 1;
	buff.CTRL_d.RDIR = dir;
	DRV8711_SPI_Write(buff.frame, CTRL_R);
}
