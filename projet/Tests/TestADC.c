#include "MyADC.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef  GPIO_ADC = {GPIOA, 0, IN_ANALOG} ; 

int valeur_adc = 0 ;
void handler_test(){
	valeur_adc = MyADC_Read(ADC1) ; 
}

int i = 0 ;
int main(){
	
	//Setting up clock for ADC1 and GPIOC
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN ;
	
	//Init GPIOC
	MyGPIO_Init(&GPIO_ADC);
	
	//Init ADC1 
	MyADC_Init(ADC1) ;
	
	//ADC1 : Enable Interrupt 
	MyADC_ActiveIT(ADC1, handler_test);  
	//Toogling conversion . . .  
	while(1){
			MyADC_ToggleConvert(ADC1) ; 
			for(i = 0 ; i < 72000 ;  i++) ; 
			MyADC_ToggleConvert(ADC1) ;  
			for(i = 0 ; i < 72000 ;  i++) ; 

	}
	return 0 ;
}