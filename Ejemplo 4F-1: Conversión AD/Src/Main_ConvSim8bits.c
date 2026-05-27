/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4F-1
* Nombre del ejercicio	: Conversión AD
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Convertidor Analógico - Digital (ADC)
* Fecha de entrega		:

* Descripción:
	Diseñar un programa que muestre mediante 8 LEDs, el resultado de
	la conversión A-D de la señal de voltaje producida por un
	potenciómetro de 5[kΩ] conectado en configuración de divisor de
	tensión al pin B0.
	Considere una resolución de 8 bits para el ADC.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	- Potenciómetro en B0
	- Resultado -> [ R7  R6 R5 R4  R3  R2  R1  R0]
				   [A11 A10 A9 A8 B15 B14 B13 B12]

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
uint8_t val_ADC = 0;

/***************** Prototipos de funciones a utilizar ***************/
uint16_t LeerADC(uint8_t canal);

/************************ Programa principal ************************/
int main(void){
/*------------------ Variables locales de proceso ------------------*/

/*-------------- Configuración de periféricos (SETUP) --------------*/
	GPIOA_Config();
	GPIOB_Config();
	ADC1_Config();
	delay_us(5);

/*--------------------- Ciclo infinito (LOOP) ----------------------*/
	while(1){
        val_ADC = LeerADC(8);	//Canal 8
        MostrarByte(val_ADC);
        delay_ms(100);
	}
}

/************* Desarrollo de los prototipos de funciones ************/
uint16_t LeerADC(uint8_t canal){
	ADC1->SQR3 |= (canal << ADC_SQR3_SQ1_Pos); //1er canal a convertir
    ADC1->CR2 |= ADC_CR2_SWSTART;	// Inicia una conversión
    while (!(ADC1->SR & ADC_SR_EOC)); // Espera a que termine la conversión
    return ADC1->DR;
}

/************* Desarrollo de las rutinas de interrupción ************/

//====================================================================


