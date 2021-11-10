#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"


void SpeedUpdate (void) {
	/*MyGPIO_Toggle (GPIOA, 2) ;
	PWM_Duty_Cycle (TIM4, 10.0, '1') ;*/
}

int main(void) {	
	
	int i ;
	int n=0 ;
	
	MyTimer_Struct_TypeDef TIMER4 ;
	MyGPIO_Struct_TypeDef BROCHE_PWM ;
	MyGPIO_Struct_TypeDef PIN_SENS ;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;
	
	TIMER4.ARR = 3600 ;
	TIMER4.PSC = 1 ;
	TIMER4.Timer = TIM4 ;
	
	BROCHE_PWM.GPIO = GPIOB ;
	BROCHE_PWM.GPIO_Conf = ALTOUT_PPULL ;
	BROCHE_PWM.GPIO_Pin = 6 ;
	
	PIN_SENS.GPIO = GPIOB ;
	PIN_SENS.GPIO_Conf = OUT_PPULL ;
	PIN_SENS.GPIO_Pin = 5 ;
	
	MyTimer_Base_Init (&TIMER4) ;
	MyGPIO_Init (&BROCHE_PWM) ;
	MyGPIO_Init (&PIN_SENS) ;
	
	MyTimer_PWM (TIMER4.Timer, '1') ;
	
	PWM_Duty_Cycle (TIM4, 0.3, '1') ;
	
	
	
	
	/*MyTimer_ActiveIT (TIMER1.Timer, 1, SpeedUpdate) ;
	
	MyTimer_Base_Init (&TIMER1) ;*/ // POUR LE CALLBACK (CHANGER LE TIMER)
	
	
	
	// PWM_Duty_Cycle (TIMER4.Timer, 20, '2') ; À CHAQUE INTERRUPTION
	// MISE À JOUR DU RAPPORT CYCLIQUE + ACTIVATION BIT DE SENS
	
	
	
	
	
	do {
		
		for (i=0; i<10000000;i++){n++;}
		MyGPIO_Toggle (PIN_SENS.GPIO, 5) ;
		
	} while(1) ;
}
