#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"
#include "MyTimer.h"

typedef struct
{
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ; // numero de 0 a 15
	char GPIO_Conf ; // voir ci dessous
} MyGPIO_Struct_TypeDef ;

#define IN_FLOATING 0x4
#define IN_PULLDOWN 0x314
#define IN_PULLUP 0x8
#define IN_ANALOG 0x0
#define OUT_PPULL 0x2
#define OUT_OD 0x6
#define ALTOUT_PPULL 0xA
#define ALTOUT_OD 0xE

void MyGPIO_Init (MyGPIO_Struct_TypeDef * GPIOStructPtr) ;
int MyGPIO_Read (GPIO_TypeDef * GPIO , char GPIO_Pin) ; // renvoie 0 ou autre chose different de 0
void MyGPIO_Set (GPIO_TypeDef * GPIO , char GPIO_Pin) ;
void MyGPIO_Reset (GPIO_TypeDef * GPIO , char GPIO_Pin) ;
void MyGPIO_Toggle (GPIO_TypeDef * GPIO , char GPIO_Pin) ;

#endif
