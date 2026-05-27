/*
 * Config_Perif.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "GPIO_Config.h"

/************* Desarrollo de los prototipos de funciones ************/
void GPIOA_Config(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER9
					| GPIO_MODER_MODER8);

	GPIOA->MODER |= (GPIO_MODER_MODER11_0 | GPIO_MODER_MODER9_0
					| GPIO_MODER_MODER8_0);

	GPIOA->BSRR = (GPIO_BSRR_BR11 | GPIO_BSRR_BR9 | GPIO_BSRR_BR8);
}

void GPIOB_Config(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER &= ~(GPIO_MODER_MODER15 | GPIO_MODER_MODER14
					| GPIO_MODER_MODER13 | GPIO_MODER_MODER12);

	GPIOB->MODER |= (GPIO_MODER_MODER15_0 | GPIO_MODER_MODER14_0
				   | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER12_0);

	GPIOB->BSRR = (GPIO_BSRR_BR15 | GPIO_BSRR_BR14 | GPIO_BSRR_BR13 | GPIO_BSRR_BR12);

    // Configura PB0 como modo analógico
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	GPIOB->MODER |= GPIO_MODER_MODER0;  // 11: modo analógico
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR0; // Sin resistencias pull-up/down
}
