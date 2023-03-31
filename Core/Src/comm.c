#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include <string.h>


  extern UART_HandleTypeDef huart6;
  char* data = "test";
  void ExStartCommTask(void const * argument){
  uint8_t buffer[8];
  for(;;){
    
    HAL_UART_Transmit(&huart6, (uint8_t*) data, strlen(data), 250);
    HAL_UART_Receive(&huart6,buffer, sizeof(buffer),100);
    osDelay(1);
  }


}

void sendMess(uint8_t mode, uint8_t mess[8]){

  HAL_UART_Transmit(&huart6, (uint8_t*) data, strlen(data), 250);
}