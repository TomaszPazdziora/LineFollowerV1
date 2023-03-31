#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include <stdbool.h>

#define SENSOR_NUMBER 2
#define TRESHOLD 1024
#define CLEARED_READING 2048

bool isWhite[SENSOR_NUMBER];
int readings[SENSOR_NUMBER];

void clearReadings();
void measure();


/* ---- TASK IMPLEMENTATION ---- */

extern void ExStartDriveTask(void const * argument) {
  /* USER CODE BEGIN StartDriveTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(300);
    measure();
    osDelay(300);
  }
  /* USER CODE END StartDriveTask */
}



/* ---- SENSOR FUNCTIONS ---- */

void measure() {
	HAL_ADC_Start(&hadc1);

	for(int i = 0; i < SENSOR_NUMBER; i++) {
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		readings[i] = HAL_ADC_GetValue(&hadc1);

		if(readings[i] < TRESHOLD) isWhite[i] = true;
		else isWhite[i] = false;
	}
}

void clearReadings() {
	for(int i = 0; i < SENSOR_NUMBER; i++) {
		readings[i] = CLEARED_READING;
		isWhite[i] = false;
	}
}



/* ---- MOTOR FUNCTIONS ---- */