/*
 * timer.c
 *
 *  Created on: 11 nov. 2016
 *      Author: lchagnoleau
 */

#include "main.h"


void DelayMicroSeconds(unsigned int delay)
{
  __HAL_TIM_SetCounter(&htim6, 0);
  while(__HAL_TIM_GetCounter(&htim6)<delay);
}

void DelayMilliSeconds(unsigned int delay)
{
  for(int i=1000;i>0;i--)
  {
    DelayMicroSeconds(delay);
  }
}
