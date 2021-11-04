#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"

//Inits interrupt (reception) and starts background process (emission)
void MyUART_Init(USART_TypeDef USART);

//Sends a string
void MyUART_Send(char * M);

//Receives a string
void MyUART_Receive(char * M);

#endif