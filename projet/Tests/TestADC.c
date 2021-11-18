#include "MyADC.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef  GPIO_ADC = {GPIOA, 0, IN_ANALOG} ; 

int valeur_adc = 0 ;
/*int calcul_potentiel(int valeur){
	return ((float)valeur*3.3)/(0xFFF) ; 
}	*/


void handler_test(){
	valeur_adc = MyADC_Read(ADC1) ; 
	
}

int main(){
	
	//Setting up clock for ADC1 and GPIOC
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN ;
	
	//Init GPIOC
	MyGPIO_Init(&GPIO_ADC);
	
	//Init ADC1 
	MyADC_Init(ADC1,'A',0) ;
	
	//ADC1 : Enable Interrupt 
	MyADC_ActiveIT(ADC1, handler_test);  
	//Togling conversion . . .  

	MyADC_Start(ADC1) ; 

	while(1){
		//valeur_adc = MyADC_Read(ADC1);
	}
	return 0 ;
}
