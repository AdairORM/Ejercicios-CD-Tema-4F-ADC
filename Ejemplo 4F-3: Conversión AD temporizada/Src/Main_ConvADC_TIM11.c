/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4F-3
* Nombre del ejercicio	: Conversión AD temporizada
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Convertidor Analógico - Digital (ADC)
* Fecha de entrega		:

* Descripción:
	Diseñar un programa que muestre en una LCD, el resultado de la
	conversión A-D de la señal de voltaje producida por un potenciómetro
	de 5[kΩ] conectado en configuración de divisor de tensión al pin B0.
	Utilice la interrupción por desbordamiento de un temporizador para
	leer la señal analógica cada cierto tiempo.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	- Potenciómetro en B0

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
uint16_t val_ADC = 0;
uint8_t BND = 1, volt_ent = 0, volt_frac = 0;
float voltaje = 0.0f;
char bufLCD[20];

/***************** Prototipos de funciones a utilizar ***************/
void ADC_Iniciar(uint8_t canal);

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
		if(BND){
			BND = 0;
			voltaje = (3.3f * (float)val_ADC)/4095.0f;
			volt_ent = (uint8_t)voltaje;
			volt_frac = (uint8_t)((voltaje - volt_ent)*100);
	        LCD_PonerCursorRC(0,0);
	        LCD_EnviarCadena("Conversion A-D");

	        sprintf(bufLCD,"Valor: %4d",val_ADC);
	        LCD_PonerCursorRC(1,1);
	        LCD_EnviarCadena(bufLCD);

	        sprintf(bufLCD,"Voltaje: %1d.%2d[V]",volt_ent,volt_frac);
	        LCD_PonerCursorRC(2,1);
	        LCD_EnviarCadena(bufLCD);
		}
	}
}

/************* Desarrollo de los prototipos de funciones ************/
void ADC_Iniciar(uint8_t canal){
	ADC1->SQR3 |= (canal << ADC_SQR3_SQ1_Pos);
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

/************* Desarrollo de las rutinas de interrupción ************/
void TIM1_TRG_COM_TIM11_IRQHandler(){
    ADC_Iniciar(8);
    BND = 1;
	TIM11->SR &= ~TIM_SR_UIF; // Limpia bandera de interrupción
}

void ADC_IRQHandler(){
	val_ADC = ADC1->DR;	// Lee el resultado
}

//====================================================================


