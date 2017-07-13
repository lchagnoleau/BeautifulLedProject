/*
 * spi.c
 *
 *  Created on: 18 nov. 2016
 *      Author: lchagnoleau
 */

#include "spi.h"

static uint8_t SPIx_Write(uint8_t Value)
{
  hspi1.Instance->DR = Value;
  while(!(hspi1.Instance->SR & SPI_FLAG_TXE));
  while(!(hspi1.Instance->SR & SPI_FLAG_RXNE));
  while(hspi1.Instance->SR & SPI_FLAG_BSY);
  return hspi1.Instance->DR;
}

uint8_t TM_SPI_Send(uint8_t data)
{
  uint8_t status = SPIx_Write(data);
  return status;
}

/* SPI1 init function */
void MX_SPI1_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  if (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_RESET)
  {
    /* SPI Config */
    hspi1.Instance = SPI1;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
    hspi1.Init.Mode = SPI_MODE_MASTER;

    HAL_SPI_Init(&hspi1);
    //HAL_SPI_MspInit(&hspi1);

    __HAL_SPI_ENABLE(&hspi1);

    //SPI_Cmd(SPI1, ENABLE);
  }
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if (hspi->Instance == SPI1)
  {
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /**SPI1 GPIO Configuration
     PA5     ------> SPI1_SCK
     PA6     ------> SPI1_MISO
     PA7     ------> SPI1_MOSI
     PA4     ------> SPI1_CS
     */
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  if (hspi->Instance == SPI1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
     PA6     ------> SPI1_MISO
     PA7     ------> SPI1_MOSI
     */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_7);
  }
}

void SPI_CSState(uint8_t state)
{
  if(state == 1)
  {
    DelayMilliSeconds(1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    DelayMilliSeconds(1);
  }
}

/* Six axes sensor IO functions */
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Init( void )
{
  return IMU_6AXES_OK;
}
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Write( uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr,
    uint16_t NumByteToWrite )
{
  uint8_t pkt = RegisterAddr;
  uint8_t i = 0;

  //Clear CS
  SPI_CSState(0);

  TM_SPI_Send(pkt);            // read command

  for(i=0; i<NumByteToWrite; i++)
      TM_SPI_Send(pBuffer[i]);

  //Set CS
  SPI_CSState(1);
  return IMU_6AXES_OK;
}
IMU_6AXES_StatusTypeDef LSM6DS3_IO_Read( uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr,
    uint16_t NumByteToRead )
{
  uint8_t pkt = 0x00;
  uint8_t i = 0;
  pkt = 0x80; // read command
  pkt = pkt | RegisterAddr;

  //Clear CS
  SPI_CSState(0);

  TM_SPI_Send(pkt);                // read command

  for(i=0; i<NumByteToRead; i++)
    pBuffer[i] = TM_SPI_Send(0x00);    // just to read

  //Set CS
  SPI_CSState(1);
  return IMU_6AXES_OK;
}
void LSM6DS3_IO_ITConfig( void )
{
  return;
}


