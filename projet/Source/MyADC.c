#include "MyADC.h"

void (*pHandler_ADC1) (void) ;
void (*pHandler_ADC2) (void) ;

void MyADC_Init(ADC_TypeDef * ADC, char port, int pin){
	int channel ; 
	ADC -> CR2 &= 0 ;
	ADC -> CR2 |= ADC_CR2_ADON ;

	if(port == 'A')
	{
		if(pin < 8)
			channel = pin;
	}
	else if (port == 'B')
	{
		if(pin<2)
			channel = 8 + pin;
	}
	else if (port == 'C')
	{
		if(pin<6)
			channel = 10 + pin;
	}
	ADC -> SQR3 = channel ; 
	
}

void MyADC_ActiveIT( ADC_TypeDef * ADC, void (*IT_function) (void) ){
	ADC -> CR1 |= ADC_CR1_EOCIE ;
	switch((int)ADC){
		case (int)ADC1 : 
			pHandler_ADC1 = IT_function ;
			break ; 
		case (int)ADC2 : 
			pHandler_ADC2 = IT_function ;
			break ;
	}
	NVIC_SetPriority(ADC1_2_IRQn, 3);
	NVIC_EnableIRQ(ADC1_2_IRQn);
	
}

void MyADC_Start(ADC_TypeDef * ADC){
	int i ; 
	for(i = 0 ; i < 72000 ;  i++) ; 
	ADC -> CR2 |= ADC_CR2_ADON ; 
	ADC -> CR2 |= ADC_CR2_CONT ;
}

void MyADC_Stop(ADC_TypeDef * ADC){
	ADC -> CR2 &= 0 ;
}


int MyADC_Read(ADC_TypeDef * ADC){
	return ADC -> DR ;
}

void ADC1_2_IRQHandler(void){
	
	if( ADC1->SR != (ADC1->SR & ADC_SR_EOC) ){ //Checking which ADC called the handler
		ADC1->SR &= ~ADC_SR_EOC ;
		if (pHandler_ADC1 != 0){
			(*pHandler_ADC1) ();
		}
	}else{
		ADC2->SR &= ~ADC_SR_EOC ;
		if (pHandler_ADC2 != 0){
			(*pHandler_ADC2) ();
		}
	}
}




 
 