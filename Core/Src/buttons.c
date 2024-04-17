/*
 * buttons.c
 *
 *  Created on: Apr 17, 2024
 *      Author: Caltech Racing
 */
#include "main.h"
#include "buttons.h"

#define BUTTON_TIMER &htim3
#define NUM_BUTTONS 3
Button buttons[] = {
		{ Port: STEPPER_DOWN_GPIO_Port, Pin: STEPPER_DOWN_Pin}
		{ Port: STEPPER_UP_GPIO_Port,  Pin: STEPPER_UP_Pin},
		{ Port: B1_GPIO_Port, Pin: B1_Pin}
};

void Debounce_Buttons() {
	static GPIO_PinState last_state[NUM_BUTTONS] = { GPIO_PIN_RESET };
	HAL_TIM_Base_Stop_IT(BUTTON_TIMER);
	for (int button = 0; button < NUM_BUTTONS; buttons++) {
		GPIO_PinState new_state = HAL_GPIO_ReadPin(buttons[button].Port, buttons[button].Pin);
		if(new_state != last_state[button]){
			Button_Debounced(buttons[button][1], new_state);
			last_state[button] = new_state;
		}
	}
}

void Button_Debounced() {
	static uint8_t button_state = 0;

	switch (button_state) {
		case 0:
			HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
			PCNC_Go_To_Origin(cutter);
			break;
		case 1:
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
			PCNC_Begin_Cut(cutter);
			break;
		default:
			__NOP();
			break;
	}

	button_state++;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	HAL_TIM_Base_Start_IT(&htim3);
}



