#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "adc.h"

#define ARR_TIM4 79
#define FORWARD 1
#define BACKWARD 2

bool isWhite[SENSOR_NUMBER];
int readings[SENSOR_NUMBER];

void clearReadings();
void measure();

int percentToDuty(int percent);
void moveLeftMotor(int dir, int speedInPercent);
void moveRightMotor(int dir, int speedInPercent);

/* ---- TASK IMPLEMENTATION ---- */

extern void ExStartDriveTask(void const * argument) {
  /* USER CODE BEGIN StartDriveTask */
  /* Infinite loop */
  for(;;)
  {
	// testing loops 

	for(int i = 0; i <= 100; i++) {
		moveLeftMotor(FORWARD, i);
		moveRightMotor(BACKWARD, 100 - i);
		osDelay(100);
	}

	for(int i = 0; i <= 100; i++) {
		moveLeftMotor(FORWARD, 100 - i);
		moveRightMotor(BACKWARD, i);
		osDelay(100);
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

int percentToDuty(int percent) {
	// 79 = 100 % pwm duty
	// 0 = 0 % pwm duty
	// duty = CRR / ARR
	// CRRx where 'x' means channel
	return (percent * (ARR_TIM4+1)/100 - 1);
}

void moveLeftMotor(int dir, int speedInPercent) {
	if (dir == FORWARD) {
		HAL_GPIO_WritePin(DRIVR1_GPIO_Port, DRIVR1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DRIVL1_GPIO_Port, DRIVL1_Pin, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(DRIVR1_GPIO_Port, DRIVR1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DRIVL1_GPIO_Port, DRIVL1_Pin, GPIO_PIN_RESET);
	}
	TIM4->CCR1 = percentToDuty(speedInPercent);
}

void moveRightMotor(int dir, int speedInPercent) {
	if (dir == FORWARD) {
		HAL_GPIO_WritePin(DRIVR2_GPIO_Port, DRIVR2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DRIVL2_GPIO_Port, DRIVL2_Pin, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(DRIVR2_GPIO_Port, DRIVR2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DRIVL2_GPIO_Port, DRIVL2_Pin, GPIO_PIN_RESET);
	}
	TIM4->CCR2 = percentToDuty(speedInPercent);
}