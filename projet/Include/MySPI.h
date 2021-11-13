#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

#ifndef FREQ_CPU
#define FREQ_CPU 72000000
#endif
	
typedef enum{
		RX, TX 
}SPI_Mode_TypeDef ;

void MySPI_Init(SPI_TypeDef * SPI, SPI_Mode_TypeDef Mode);
	
void MySPI_RX_ActiveIT(SPI_TypeDef * USART, void (*IT_function) (void));


#endif