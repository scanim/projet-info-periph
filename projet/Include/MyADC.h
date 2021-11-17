#ifndef MY_ADC
#define MY_ADC

#include "stm32f10x.h"

void MyADC_Init(ADC_TypeDef * ADC);
void MyADC_ActiveIT( ADC_TypeDef * ADC, void (*IT_function) (void) ) ;
void MyADC_ToggleConvert(ADC_TypeDef * ADC);
int MyADC_Read(ADC_TypeDef * ADC);
#endif