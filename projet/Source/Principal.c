#include "stm32f10x.h"

#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"
#include "Bordage.h"

#define PINGIROUETTE 4
#define CHANNEL_PWM_SERVO '1'

int main(void) {	
	
	// Structures girouette
	MyEncoder_Struct_TypeDef Encoder;
	MyGPIO_Struct_TypeDef pin_girouette;
	MyTimer_Struct_TypeDef compteur_AB;
	
	// Structures Servo
	MyGPIO_Struct_TypeDef pin_servo ;
	MyTimer_Struct_TypeDef timer3 ;
	MyTimer_Struct_TypeDef timer1 ;
	
	// On alimente les ponts
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;
	
	// Init Servo
	pin_servo.GPIO = GPIOA ;
	pin_servo.GPIO_Conf = ALTOUT_PPULL ;
	pin_servo.GPIO_Pin = 6 ;
	
	timer3.ARR = PWM_SERVO_ARR ;
	timer3.PSC = PWM_SERVO_PSC ;
	timer3.Timer = TIM3 ;
	//TIM3 alternate function is linked to PA6
	
	timer1.ARR = INTERRUPT_SERVO_ARR ;
	timer1.PSC = INTERRUPT_SERVO_PSC ;
	timer1.Timer = TIM1 ;
	
	
	// Init girouette
	pin_girouette.GPIO = GPIOA;
	pin_girouette.GPIO_Conf = IN_PULLUP;
	pin_girouette.GPIO_Pin = PINGIROUETTE;

	compteur_AB.Timer = TIM2;
	compteur_AB.ARR = 4*360; //on compte les quarts de degré donc on remet à 0 tous les 1440 tics
	compteur_AB.PSC = 1;
	
	Encoder.Encoder_I=&pin_girouette;
	Encoder.struct_compteur_AB=&compteur_AB;
	
	
	// Initialisations logicielles du bordage
	MyTimer_Base_Init(&timer3);
	MyTimer_Base_Init(&timer1);
	MyTimer_ActiveIT(TIM1, PRIO_INTERRUPT_BORDAGE, &Handler_Bordage);

	Bordage_Init(&timer3, &pin_servo, CHANNEL_PWM_SERVO, &Encoder);

	do {
		
	} while(1) ;
}
