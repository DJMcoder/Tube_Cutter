/*
 * buttons.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Caltech Racing
 */

extern TIM_HandleTypeDef htim3;

typedef struct {
	GPIO_TypeDef *Port;
	uint16_t Pin;
} Button;
