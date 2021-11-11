#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

#ifndef FREQ_CPU
#define FREQ_CPU 72000000. //STM32F103RB
#endif

typedef enum{
	RX,TX
}USART_Mode_TypeDef ; 

//Inits interrupt (reception) or sets USART mode to transmission
// TX mode is to be used via pooling method 
// RX mode is based on RXNEI flag interruption : to retrieve received byte, handlers have to be redefined via MyUART_RX_ActiveIT
void MyUART_Init(USART_TypeDef * USART,USART_Mode_TypeDef Mode, float Baud_Rate);

// - USART_TypeDef * USART : designated USART (USART1/2/3)
// - void (*IT_function) (void) : handler to be called when RXNE (data register not empty) flag is raised
// MyUART_Init has to be called with RX mode on the designated USART beforehand
void MyUART_RX_ActiveIT(USART_TypeDef * USART, void (*IT_function) (void));

// - USART_TypeDef * USART : designated USART (USART1/2/3)
// char * M : character array to send
// int len : length of the byte array to send, including end of string character if it is a string
// MyUART_Init has to be called with TX mode on the designated USART beforehand
void MyUART_TX_Send(USART_TypeDef * USART, char * M, int len);


#endif
