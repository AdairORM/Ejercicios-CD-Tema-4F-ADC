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

}

void GPIOB_Config(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER &= ~GPIO_MODER_MODER12;

	GPIOB->MODER |= GPIO_MODER_MODER12_0;

	GPIOB->BSRR = GPIO_BSRR_BR12;

    // Configura PB0 como modo analógico
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	GPIOB->MODER |= GPIO_MODER_MODER0;  // 11: modo analógico
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR0; // Sin resistencias pull-up/down
}
