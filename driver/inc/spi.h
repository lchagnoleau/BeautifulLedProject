/*
 * spi.h
 *
 *  Created on: 18 nov. 2016
 *      Author: lchagnoleau
 */

#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_

#include "main.h"
#include "imu_6axes.h"

SPI_HandleTypeDef hspi1;

void MX_SPI1_Init(void);
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi);
void SPI_CSState(uint8_t state);
uint8_t TM_SPI_Send(uint8_t data);

/* Six axes sensor IO functions */
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Init( void );
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Write( uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr,
    uint16_t NumByteToWrite );
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Read( uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr,
    uint16_t NumByteToRead );
void LSM6DS3_IO_ITConfig( void );

#endif /* INCLUDE_SPI_H_ */
