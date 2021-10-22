#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

#define PRIOCALLBACKTIM3 2
#define PINSERVO 6

/*
void Callback (void) {
}
*/

int main(void) {	
	
MyEncoder_Struct_TypeDef Encoder;

	MyGPIO_Struct_TypeDef GPIO_I = {GPIOA, 4, IN_PULLUP}; // configuration pas 100% certain
	MyTimer_Struct_TypeDef compteur_AB = {TIM2, 720, 1};
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;
	
	
	Encoder.Encoder_I=&GPIO_I;
	Encoder.struct_compteur_AB=&compteur_AB;
	MyEncoder_Init(&Encoder);
	
	MyEncoder_findZero();




	MyTimer_Struct_TypeDef TIMER3 ;
	
	MyGPIO_Struct_TypeDef BROCHE_CONFIG_PWM ;
	
	TIMER3.ARR = 60000 ;
	TIMER3.PSC = 24 ;
	TIMER3.Timer = TIM3 ;
	//TIM3 alternate function is linked to PA6
	BROCHE_CONFIG_PWM.GPIO = GPIOA ;
	BROCHE_CONFIG_PWM.GPIO_Conf = ALTOUT_PPULL ;
	BROCHE_CONFIG_PWM.GPIO_Pin = PINSERVO ;
	
	
	MyGPIO_Init (&BROCHE_CONFIG_PWM) ;
	
	MyTimer_Base_Init (&TIMER3) ;
	
	//MyTimer_ActiveIT (TIMER3.Timer, PRIOCALLBACKTIM3, Callback) ;
	
	MyTimer_PWM (TIMER3.Timer, '1') ;
	
	Rapport_Cyclique (TIMER3.Timer, 10.0, '1') ;
	
	
	
	do {
		
	} while(1) ;
}
