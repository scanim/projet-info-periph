#include "MyADC.h"

void (*pHandler_ADC) (void) ;

void MyADC_Init(ADC_TypeDef * ADC){
	ADC -> CR2 &= 0 ;
	ADC -> CR2 |= ADC_CR2_ADON ; 
}

void MyADC_ActiveIT( ADC_TypeDef * ADC, void (*IT_function) (void) ){
	ADC -> CR1 |= ADC_CR1_EOCIE ; 
	pHandler_ADC = IT_function ;
	NVIC_SetPriority(ADC1_2_IRQn, 3);
	NVIC_EnableIRQ(ADC1_2_IRQn);
}

void MyADC_ToggleConvert(ADC_TypeDef * ADC){
	ADC -> CR2 ^= ADC_CR2_SWSTART ; 
}





 
 