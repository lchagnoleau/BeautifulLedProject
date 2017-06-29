/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

int main(void)
{

  char *msg = "Hello World!\n\r";

  HAL_Init();
  Init();

  while (1)
  {
    trace_printf(msg);
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
    DelayMilliSeconds(500);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  }
}
