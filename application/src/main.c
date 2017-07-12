/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

int main(void)
{

  char *msg = "Hello World!\n\r";
  uint8_t tmp1 = 0x00;

  HAL_Init();
  Init();

  while (1)
  {
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WHO_AM_I_ADDR, 1);
    trace_printf("return SPI : %02X\n", tmp1);
    DelayMilliSeconds(1000);
  }
}
