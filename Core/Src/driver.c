#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "adc.h"

bool isWhite[SENSOR_NUMBER];
int readings[SENSOR_NUMBER];

void clearReadings();
void measure();

void turnLeft1motor();
void turnRight1motor();

void turnLeft2motor();
void turnRight2motor();

/* ---- TASK IMPLEMENTATION ---- */

extern void ExStartDriveTask(void const * argument) {
  /* USER CODE BEGIN StartDriveTask */
  turnRight1motor();
  turnRight2motor();
  /* Infinite loop */
  for(;;)
  {
	for(int i = 19; i > 0; i--) {
		// 19 = 100 % pwm duty
		// 0 = 0% pwm duty
		// duty = CRR / ARR
		// CRRx where 'x' means channel

		TIM4->CCR1 = i;
		TIM4->CCR2 = 19 - i;
		osDelay(300);
	}
	
	// osDelay(SENSOR_DELAY);
    // measure();
    // osDelay(SENSOR_DELAY);
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

void turnLeft1motor() {
	HAL_GPIO_WritePin(DRIVR1_GPIO_Port, DRIVR1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DRIVL1_GPIO_Port, DRIVL1_Pin, GPIO_PIN_SET);
}

void turnRight1motor() {
	HAL_GPIO_WritePin(DRIVR1_GPIO_Port, DRIVR1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVL1_GPIO_Port, DRIVL1_Pin, GPIO_PIN_RESET);
}

void turnLeft2motor() {
	HAL_GPIO_WritePin(DRIVR2_GPIO_Port, DRIVR2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DRIVL2_GPIO_Port, DRIVL2_Pin, GPIO_PIN_SET);
}

void turnRight2motor() {
	HAL_GPIO_WritePin(DRIVR2_GPIO_Port, DRIVR2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRIVL2_GPIO_Port, DRIVL2_Pin, GPIO_PIN_RESET);
}