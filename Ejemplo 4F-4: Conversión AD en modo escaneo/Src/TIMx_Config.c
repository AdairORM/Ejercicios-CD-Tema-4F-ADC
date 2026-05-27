/*
 * Config_Perif.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "TIMx_Config.h"

/************* Desarrollo de los prototipos de funciones ************/
void TIM1_Config(void){

}

void TIM2_Config(void){

}

void TIM3_Config(void){

}

void TIM4_Config(void){

}

void TIM5_Config(void){

}

void TIM9_Config(void){

}

void TIM10_Config(void){

}

void TIM11_Config(void){
	RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;

	TIM11->PSC = 16000 - 1;
	TIM11->ARR = 250 - 1;
	TIM11->CNT = 0;

	TIM11->DIER |= TIM_DIER_UIE;
	TIM11->SR &= ~TIM_SR_UIF;
	TIM11->CR1  |= TIM_CR1_CEN;

	NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 1);
}
