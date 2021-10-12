#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

int pulse = 0; 

void Callback (void) {
	MyGPIO_Toggle (GPIOA, 5) ;
	pulse = (pulse + 5) % 101;
	Rapport_Cyclique (TIM3, pulse, '2') ;
}



int main(void){	
	
	MyGPIO_Struct_TypeDef BROCHE_LED_VERTE ;
	
	MyGPIO_Struct_TypeDef BROCHE_BOUTON_USER ;
	
	MyTimer_Struct_TypeDef TIMER2 ;
	
	MyTimer_Struct_TypeDef TIMER3 ;
	
	MyGPIO_Struct_TypeDef BROCHE_CONFIG_PWM ;
	
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;

	
	BROCHE_LED_VERTE.GPIO = GPIOA ;
	BROCHE_LED_VERTE.GPIO_Conf = OUT_PPULL ;
	BROCHE_LED_VERTE.GPIO_Pin = 5 ;

	BROCHE_BOUTON_USER.GPIO = GPIOC ;
	BROCHE_BOUTON_USER.GPIO_Conf = IN_FLOATING ;
	BROCHE_BOUTON_USER.GPIO_Pin = 13 ;
	
	TIMER2.ARR = 65455 ;
	TIMER2.PSC = 550 ;
	TIMER2.Timer = TIM2 ;
	
	TIMER3.ARR = 720 ;
	TIMER3.PSC = 1 ;
	TIMER3.Timer = TIM3 ;
	
	BROCHE_CONFIG_PWM.GPIO = GPIOA ;
	BROCHE_CONFIG_PWM.GPIO_Conf = ALTOUT_PPULL ;
	BROCHE_CONFIG_PWM.GPIO_Pin = 7 ;
	
	
	MyGPIO_Init (&BROCHE_LED_VERTE) ;
	
	MyGPIO_Init (&BROCHE_BOUTON_USER) ;
	
	MyGPIO_Init (&BROCHE_CONFIG_PWM) ;
	
	MyTimer_ActiveIT (TIMER2.Timer, 1, Callback) ;
	
	MyTimer_Base_Init (&TIMER2) ;
	
	MyTimer_PWM (TIMER3.Timer, '2') ;
	
	Rapport_Cyclique (TIMER3.Timer, 20, '2') ;
	
	MyTimer_Base_Init (&TIMER3) ;
	
	
	do
	{
		
		/*if (MyGPIO_Read(BROCHE_BOUTON_USER.GPIO, BROCHE_BOUTON_USER.GPIO_Pin) == 0) {
			MyGPIO_Set (BROCHE_LED_VERTE.GPIO, BROCHE_LED_VERTE.GPIO_Pin) ;
		} else {
			MyGPIO_Reset (BROCHE_LED_VERTE.GPIO, BROCHE_LED_VERTE.GPIO_Pin) ;
		}*/
		
	}while(1) ;
}
