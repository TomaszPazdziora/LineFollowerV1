#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "adc.h"

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
    osDelay(SENSOR_DELAY);
    measure();
    osDelay(SENSOR_DELAY);
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