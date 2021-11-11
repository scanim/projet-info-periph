#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

#ifndef FREQ_CPU
#define FREQ_CPU 72000000.
#endif

typedef enum{
	RX,TX
}USART_Mode_TypeDef ; 

//Inits interrupt (reception) or sets USART mode to transmission
// TX mode is to be used via pooling method 
// RX mode is based on RXNEI flag interruption : to retrieve received byte, handlers have to be redefined
void MyUART_Init(USART_TypeDef * USART,USART_Mode_TypeDef Mode, float Baud_Rate, void (*IT_function) (USART_TypeDef));

//Sends a string M with length len
void MyUART_Send(USART_TypeDef * USART, char * M, int len);

//Receives a string
void MyUART_Receive(USART_TypeDef * USART, char * M);

#endif
