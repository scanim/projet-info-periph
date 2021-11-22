#include "MyADC.h"
#include "Driver_GPIO.h"

int adc_value ;
ADC_TypeDef * ADC_Tension ; 
char channel ;

void handler_tension(){
	adc_value = MyADC_Read(ADC1) ; 
}

void update_value(){
		adc_value = MyADC_Read(ADC1) ; 		
}

void TensionBatterie_init(ADC_TypeDef * ADC, MyGPIO_Struct_TypeDef  * GPIO_ADC){ 
	adc_value = 0 ; 
	channel = GPIO_ADC->GPIO_Pin ; 
	/*int calcul_potentiel(int valeur){
		return ((float)valeur*3.3)/(0xFFF) ; 
	}	*/
	
	//Setting up clock for ADC1 and GPIOC
	switch((int)(GPIO_ADC->GPIO)){
		case((int)GPIOA) :
			RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN  ;
			break;
		case((int)GPIOB) :
			RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN  ;
			channel += 8 ; 
			break;
		case((int)GPIOC) :
			RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN  ;
			channel += 10 ; 
			break;
	}
	
	switch((int)ADC){
		case((int)ADC1) :
			RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN ;			
			break ; 
		case((int)ADC2) :
			RCC -> APB2ENR |= RCC_APB2ENR_ADC2EN ;
			break ;
	}

	//Init GPIO
	MyGPIO_Init(GPIO_ADC);
		
	//Init ADC 
	switch((int)(GPIO_ADC->GPIO)){
		case((int)GPIOA) :
			MyADC_Init(ADC,'A',GPIO_ADC->GPIO_Pin) ;
			break;
		case((int)GPIOB) :
			MyADC_Init(ADC,'A',GPIO_ADC->GPIO_Pin) ;
			break;
		case((int)GPIOC) :
			RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN  ;
			break;
	}
	MyADC_Init(ADC1,'A',0) ;
		
	//ADC1 : Enable Interrupt 
	MyADC_ActiveIT(ADC1, handler_tension);  
	//Togling conversion . . .  

}

void TensionBatterie_get(){
	int i ; 
	MyADC_Start(ADC_Tension) ; 
	for( i = 0 ; i < 7200000 ; i++ ) ; 
	MyADC_Stop(ADC_Tension) ; 
}

