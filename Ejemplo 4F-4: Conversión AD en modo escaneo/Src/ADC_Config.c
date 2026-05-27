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
	ADC->CCR |= ADC_CCR_ADCPRE_0;

	//Configurar resolución del ADC (12 bits por default)

	//Modo SCAN e interrupción por fin de conversión
	ADC1->CR1 |= (ADC_CR1_SCAN | ADC_CR1_EOCIE);

	//Alineación a la derecha y conversión continua desactivada
	ADC1->CR2 &= ~(ADC_CR2_ALIGN | ADC_CR2_CONT);
	ADC1->CR2 |= ADC_CR2_EOCS;	//Interrupción por cada conversión

	// Configura canales en la secuencia regular (PB0 -> canal 8, PA6 -> canal 6)
	ADC1->SQR1 |= ADC_SQR1_L_0; 	//Dos conversiones
	ADC1->SQR3 |= (6 << ADC_SQR3_SQ2_Pos) | (8 << ADC_SQR3_SQ1_Pos);

	// Configura tiempo de muestreo del canal 8 (ejemplo: 84 ciclos)
	ADC1->SMPR2 |= (4U << ADC_SMPR2_SMP8_Pos); // SMP8[2:0] = 100 → 84 ciclos
	ADC1->SMPR2 |= (4U << ADC_SMPR2_SMP6_Pos); // SMP6[2:0] = 100 → 84 ciclos

	NVIC_EnableIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn,1);

	ADC1->CR2 |= ADC_CR2_ADON;	// Encender el ADC
}
