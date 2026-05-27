/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4F-2
* Nombre del ejercicio	: Blink variable por ADC
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Convertidor Analógico - Digital (ADC)
* Fecha de entrega		:

* Descripción:
	Diseñar un programa que haga que aumente la frecuencia de parpadeo
	de un LED a medida que aumenta el voltaje proporcionado por un
	potenciómetro. Ante un voltaje 0, la frecuencia de parpadeo deberá
	ser aproximadamente de 1Hz y ante un voltaje de 3.3[V], la
	frecuencia deberá ser de aproximadamente de 10Hz.
	Considere una resolución de 12 bits y el uso de la interrupción por
	fin de conversión.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	- Potenciómetro en B0
	- LED en B12

====================================================================*/

/*********************************************************************
*****************************  Programa  *****************************
*********************************************************************/

/********************** Bibliotecas a utilizar **********************/
#include "stm32f4xx.h"
#include "GPIO_Config.h"
#include "ADC_Config.h"
#include "Funciones.h"

/********************* Constantes de compilador *********************/

/******************* Variables globales de proceso ******************/
uint16_t val_ADC = 0, retardo = 0;

/***************** Prototipos de funciones a utilizar ***************/

/************************ Programa principal ************************/
int main(void){
/*------------------ Variables locales de proceso ------------------*/

/*-------------- Configuración de periféricos (SETUP) --------------*/
	GPIOB_Config();
	ADC1_Config();
	delay_us(5);
	ADC1->CR2 |= ADC_CR2_SWSTART;	// Inicia la 1ra conversión

/*--------------------- Ciclo infinito (LOOP) ----------------------*/
	while(1){
		GPIOB->ODR ^= GPIO_ODR_OD12;
		retardo = 500 - (450 * val_ADC/4095);
		delay_ms(retardo);
	}
}

/************* Desarrollo de los prototipos de funciones ************/

/************* Desarrollo de las rutinas de interrupción ************/
void ADC_IRQHandler(){
	val_ADC = ADC1->DR;	// Lee el resultado
	ADC1->CR2 |= ADC_CR2_SWSTART; // Inicia otra conversión
}
//====================================================================


