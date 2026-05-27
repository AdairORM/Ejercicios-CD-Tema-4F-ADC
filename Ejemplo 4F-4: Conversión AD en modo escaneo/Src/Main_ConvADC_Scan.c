/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4F-4
* Nombre del ejercicio	: Conversión AD en modo escaneo
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Convertidor Analógico - Digital (ADC)
* Fecha de entrega		:

* Descripción:
	Diseñar un programa en lenguaje C con controladores CMSIS que
	muestre en una LCD, el resultado de la conversión A-D de dos
	señales de voltaje producidas por dos potenciómetros de 5[kΩ]
	conectados en configuración de divisor de tensión al pin B0
	y A6.
	Utilice la interrupción por desbordamiento de un temporizador
	para leer las señales analógicas cada cierto tiempo.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	- Potenciómetro 1 en B0
	- Potenciómetro 2 en A6

====================================================================*/

/*********************************************************************
*****************************  Programa  *****************************
*********************************************************************/

/********************** Bibliotecas a utilizar **********************/
#include "stm32f4xx.h"
#include "GPIO_Config.h"
#include "ADC_Config.h"
#include "TIMx_Config.h"
#include "Funciones.h"
#include "LCD_4bits.h"
#include "stdio.h"

/********************* Constantes de compilador *********************/

/******************* Variables globales de proceso ******************/
uint16_t val_PB0 = 0, val_PA6 = 0;
uint8_t BN1 = 1, BN2 = 0;
char bufLCD[20];

/***************** Prototipos de funciones a utilizar ***************/

/************************ Programa principal ************************/
int main(void){
/*------------------ Variables locales de proceso ------------------*/

/*-------------- Configuración de periféricos (SETUP) --------------*/
	GPIOA_Config();
	GPIOB_Config();
	TIM11_Config();
	ADC1_Config();
	LCD_Inicializar();
	delay_ms(5);

/*--------------------- Ciclo infinito (LOOP) ----------------------*/
	while(1){
		if(BN1){
			BN1 = 0;
			LCD_PonerCursorRC(0,0);
	        LCD_EnviarCadena("Conversion A-D");

	        sprintf(bufLCD,"ValorPB0: %4d",val_PB0);
	        LCD_PonerCursorRC(1,1);
	        LCD_EnviarCadena(bufLCD);

	        sprintf(bufLCD,"ValorPA6: %4d",val_PA6);
	        LCD_PonerCursorRC(2,1);
	        LCD_EnviarCadena(bufLCD);
		}
	}
}

/************* Desarrollo de los prototipos de funciones ************/

/************* Desarrollo de las rutinas de interrupción ************/
void TIM1_TRG_COM_TIM11_IRQHandler(){
	ADC1->CR2 |= ADC_CR2_SWSTART; //Inicia conversión ADC
    BN1 = 1;
	TIM11->SR &= ~TIM_SR_UIF; // Limpia bandera de interrupción
}

void ADC_IRQHandler(){
	uint16_t val_ADC = ADC1->DR;
	if(!BN2){
		val_PB0 = val_ADC;	// Resultado de PB0
		BN2 = 1;
	}
	else{
		val_PA6 = val_ADC;	// Resultado de PA6
		BN2 = 0;
	}
}

//====================================================================


