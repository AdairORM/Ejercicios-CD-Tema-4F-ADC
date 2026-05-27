/*
 * Config_Perif.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "ADC_Config.h"

/************* Desarrollo de los prototipos de funciones ************/
void ADC1_Config(void){
	// Habilita reloj para ADC1
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	//Configuración de frecuencia de reloj del ADC (4[MHz])
	ADC->CCR &= ~ADC_CCR_ADCPRE;
	ADC->CCR |= ADC_CCR_ADCPRE_0;

	//Configurar resolución del ADC
	ADC1->CR1 &= ~ADC_CR1_RES;
	ADC1->CR1 |= ADC_CR1_RES_1;		//Resolución de 8 bits

	//Configurar alineación del resultado de la conversión (a la derecha)
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 &= ~ADC_CR2_CONT;	//Modo conversión única (CONT = 0)

	// Configura el canal en la secuencia regular (PB0 -> canal 8)
	ADC1->SQR1 &= ~ADC_SQR1_L; 	//Una conversión
	// Configura tiempo de muestreo del canal 8 (ejemplo: 84 ciclos)
	ADC1->SMPR2 |= (4U << ADC_SMPR2_SMP8_Pos); // SMP8[2:0] = 100 → 84 ciclos

	ADC1->CR2 |= ADC_CR2_ADON;	// Encender el ADC
}
