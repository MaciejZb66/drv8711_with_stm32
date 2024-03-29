/*
 * drv8711.h
 *
 *  Created on: Mar 29, 2024
 *      Author: 4mzr2
 */

#pragma once
//includes
#include "spi.h"
#include "stdint.h"

//spi defines
#define DRV8711_SPI 		&hspi1
#define DRV8711_CS_Pin  	GPIO_PIN_2
#define DRV8711_CS_Port 	GPIOA

// register defines
#define   CTRL_R	0x00
#define   TORQUE_R  0x01
#define   OFF_R     0x02
#define   BLANK_R   0x03
#define   DECAY_R   0x04
#define   STALL_R   0x05
#define   DRIVE_R	0x06
#define   STATUS_R	0x07

//data structs
typedef struct{
	uint16_t ID :4;
	uint16_t DTIME :2;
	uint16_t ISGAIN :2;
	uint16_t EXSTALL :1;
	uint16_t MODE :4;
	uint16_t RSTEP :1;
	uint16_t RDIR :1;
	uint16_t ENBL :1;
}CTRL_data;

typedef struct{
	uint16_t ID :4;
	uint16_t Reserved :1;
	uint16_t SMPLTH :3;
	uint16_t TORQUE :8;
}TORQUE_data;

typedef struct{
	uint16_t ID :4;
	uint16_t Reserved :3;
	uint16_t PWMMODE :1;
	uint16_t TOFF :8;
}OFF_data;

typedef struct{
	uint16_t ID :4;
	uint16_t Reserved :3;
	uint16_t ABT :1;
	uint16_t TBLANK :8;
}BLANK_data;

typedef struct{
	uint16_t ID :4;
	uint16_t Reserved :1;
	uint16_t DECMOD :3;
	uint16_t TDECAY :8;
}DECAY_data;

typedef struct{
	uint16_t ID :4;
	uint16_t VDIV :2;
	uint16_t SDCNT :2;
	uint16_t SDTHR :8;
}STALL_data;

typedef struct{
	uint16_t ID :4;
	uint16_t IDRIVEP :2;
	uint16_t IDRIVEN :2;
	uint16_t TDRIVEP :2;
	uint16_t TDRIVEN :2;
	uint16_t OCPDEG :2;
	uint16_t OCPTH :2;
}DRIVE_data;

typedef struct{
	uint16_t ID :4;
	uint16_t Reserved :4;
	uint16_t STDLAT :1;
	uint16_t STD :1;
	uint16_t UVLO :1;
	uint16_t BPDF :1;
	uint16_t APDF :1;
	uint16_t BOCP :1;
	uint16_t AOCP :1;
	uint16_t OTS :1;
}STATUS_data;

typedef union{
	uint16_t frame;
	CTRL_data CTRL_d;
	TORQUE_data TORQUE_d;
	OFF_data OFF_d;
	BLANK_data BLANK_d;
	DECAY_data DECAY_d;
	STALL_data STALL_d;
	DRIVE_data DRIVE_d;
	STATUS_data STATUS_d;
}get_data;

//prototypes of functions
void DRV8711_SPI_Write(uint16_t data, uint8_t reg);
uint16_t DRV8711_SPI_Read(uint8_t reg);