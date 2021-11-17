#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"
#include "MyUART.h"
#include "Bordage.h"
#include "MyPin.h"



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
	
	
	// Structures girouette
	MyEncoder_Struct_TypeDef Encoder;
	MyGPIO_Struct_TypeDef pin_girouette;
	MyTimer_Struct_TypeDef compteur_AB;
	// Structures Servo
	MyGPIO_Struct_TypeDef pin_servo ;
	MyTimer_Struct_TypeDef timer3 ;
	MyTimer_Struct_TypeDef timer1 ;
	// Structures Moteur Plateau et USART
	MyTimer_Struct_TypeDef TIMER4 ;
	MyGPIO_Struct_TypeDef BROCHE_PWM ;
	MyGPIO_Struct_TypeDef PIN_SENS ;
	MyGPIO_Struct_TypeDef GPIO_USART_RX = {GPIOA, GPIO_USART_PIN, IN_PULLDOWN};
	
	// On alimente les ponts
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_USART3EN ;
	
	timer1.ARR = INTERRUPT_SERVO_ARR ;
	timer1.PSC = INTERRUPT_SERVO_PSC ;
	timer1.Timer = TIM1 ;
	
	timer3.ARR = PWM_SERVO_ARR ;
	timer3.PSC = PWM_SERVO_PSC ;
	timer3.Timer = TIM3 ;
	//TIM3 alternate function is linked to PA6
	
	TIMER4.ARR = PWM_PLATEAU_ARR ;
	TIMER4.PSC = 1 ;
	TIMER4.Timer = TIM4 ;
	
	BROCHE_PWM.GPIO = GPIOB ;
	BROCHE_PWM.GPIO_Conf = ALTOUT_PPULL ;
	BROCHE_PWM.GPIO_Pin = 6 ;
	
	PIN_SENS.GPIO = GPIOB ;
	PIN_SENS.GPIO_Conf = OUT_PPULL ;
	PIN_SENS.GPIO_Pin = GPIO_PIN_SENS ;
	
	// Init Servo
	pin_servo.GPIO = GPIOA ;
	pin_servo.GPIO_Conf = ALTOUT_PPULL ;
	pin_servo.GPIO_Pin = GPIO_PIN_SERVO ;
	
	// Init girouette
	pin_girouette.GPIO = GPIOA;
	pin_girouette.GPIO_Conf = IN_PULLUP;
	pin_girouette.GPIO_Pin = PINGIROUETTE;
	
	compteur_AB.Timer = TIM2;
	compteur_AB.ARR = ENCODER_ARR; //on compte les quarts de degré donc on remet à 0 tous les 1440 tics
	compteur_AB.PSC = 1;

	
	Encoder.Encoder_I=&pin_girouette;
	Encoder.struct_compteur_AB=&compteur_AB;
	
	// Initialisations logicielles du bordage
	MyTimer_Base_Init(&timer3);
	MyTimer_Base_Init(&timer1);
	MyTimer_Base_Init (&TIMER4) ;

	Bordage_Init(&timer3, &pin_servo, '1', &Encoder);
	
	MyGPIO_Init (&BROCHE_PWM) ;
	MyGPIO_Init (&PIN_SENS) ;
	MyGPIO_Init(&GPIO_USART_RX);
	
	MyUART_Init(USART1, RX, UART_BAUD_RATE);

	MyTimer_PWM (TIMER4.Timer, '1') ;
	MyUART_RX_ActiveIT(USART1, SpeedUpdate);
	MyTimer_ActiveIT (TIM1, PRIO_INTERRUPT_BORDAGE, Handler_Bordage);
	
	
	
	do {
	} while(1) ;
}
