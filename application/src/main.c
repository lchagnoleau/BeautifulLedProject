/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

int main(void)
{

  char *msg = "Hello World!\n\r";
  uint8_t tmp1 = 0x00;

  trace_printf("HAL_Init\n");
  HAL_Init();
  trace_printf("Init\n");
  Init();

  IMU_6AXES_InitTypeDef LSM6DS3_parameters;
  LSM6DS3_parameters.G_FullScale = 125.0f;
  LSM6DS3_parameters.G_OutputDataRate = LSM6DS3_G_ODR_1660HZ;
  LSM6DS3_parameters.G_X_Axis = 0;
  LSM6DS3_parameters.G_Y_Axis = 0;
  LSM6DS3_parameters.G_Z_Axis = 0;
  LSM6DS3_parameters.X_FullScale = LSM6DS3_XL_FS_2G;
  LSM6DS3_parameters.X_OutputDataRate = LSM6DS3_XL_ODR_PD;
  LSM6DS3_parameters.X_X_Axis = 0;
  LSM6DS3_parameters.X_Y_Axis = 0;
  LSM6DS3_parameters.X_Z_Axis = 0;

  trace_printf("LSM6DS3_Init\n");
  LSM6DS3_Init(&LSM6DS3_parameters);

  int32_t pdata[3] = {0};
  uint8_t tmp = 0;

  trace_printf("While\n");
  while (1)
  {
      LSM6DS3_G_GetAxes(pdata);
//      if(tmp != pdata[0])
//        {
//          tmp = pdata[0];
//          trace_printf("pdata[0] : %lu mdps\n", pdata[0]);
//        }
      LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WHO_AM_I_ADDR, 1);
      trace_printf("return SPI : %02X\n", tmp1);
      DelayMilliSeconds(1000);
  }
}
