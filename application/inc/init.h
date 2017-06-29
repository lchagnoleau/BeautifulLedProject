/*
 * init.h
 *
 *  Created on: 5 janv. 2017
 *      Author: lchagnoleau
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_

#include "main.h"

#define GND_Pin GPIO_PIN_8
#define GND_GPIO_Port GPIOA

#define LED_Pin GPIO_PIN_9
#define LED_GPIO_Port GPIOA

GPIO_InitTypeDef  GPIO_InitStruct;
TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart2;

void Init();
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base);

#endif /* INC_INIT_H_ */
