#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


extern void ExStartDriveTask(void const * argument)
{
  /* USER CODE BEGIN StartDriveTask */
  int a = 5;
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_WritePin(LED_CTR_GPIO_Port, LED_CTR_Pin, GPIO_PIN_RESET);
    osDelay(1);
  }
  /* USER CODE END StartDriveTask */
}