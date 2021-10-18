#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"



int main(void){	
	
	MyEncoder_Struct_TypeDef Encoder;
	MyGPIO_Struct_TypeDef GPIO_I = {GPIOA, 2, IN_PULLUP}; // configuration pas 100% certain
	MyTimer_Struct_TypeDef compteur_AB = {TIM2, 720, 1};
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;
	
	
	Encoder.Encoder_I=&GPIO_I;
	Encoder.struct_compteur_AB=&compteur_AB;
	MyEncoder_Init(&Encoder);
	
	
	do
	{

	}while(1) ;
}
