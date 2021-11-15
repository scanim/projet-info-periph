#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"
#include "MyUART.h"

signed char valeur = 0;

void SpeedUpdate () {
	if(valeur != USART1->DR){  
		valeur = USART1->DR ;
		if (valeur>=0) {
			MyGPIO_Reset (GPIOB, 5) ;
			PWM_Duty_Cycle (TIM4, (double)(valeur)/100.0, '1') ;
		} else {
			MyGPIO_Set (GPIOB, 5) ;
			PWM_Duty_Cycle (TIM4, (double)(valeur*(-1))/100.0, '1') ;
		}
	}
}
int main(void) {	
	
	/*int i ;
	int n=0 ;*/
	
	MyTimer_Struct_TypeDef TIMER4 ;
	MyGPIO_Struct_TypeDef BROCHE_PWM ;
	MyGPIO_Struct_TypeDef PIN_SENS ;
	MyGPIO_Struct_TypeDef GPIO_USART_RX = {GPIOA,10,IN_PULLDOWN};
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN ;
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
	MyGPIO_Init(&GPIO_USART_RX);
	MyUART_Init(USART1, RX, 9600);

	MyTimer_PWM (TIMER4.Timer, '1') ;
	MyUART_RX_ActiveIT(USART1, SpeedUpdate);
	
	
	
	
	/*MyTimer_ActiveIT (TIMER1.Timer, 1, SpeedUpdate) ;
	
	MyTimer_Base_Init (&TIMER1) */
	
	
	
	// PWM_Duty_Cycle (TIMER4.Timer, 20, '2') ; À CHAQUE INTERRUPTION
	// MISE À JOUR DU RAPPORT CYCLIQUE + ACTIVATION BIT DE SENS
	
	
	
	
	
	do {
		
		/*for (i=0; i<10000000;i++){n++;}
		MyGPIO_Toggle (PIN_SENS.GPIO, 5) ;*/
		
	} while(1) ;
}
