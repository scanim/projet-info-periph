#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"

#define PINGIROUETTE 4
#define CHANNELPWMSERVO '1'

int main(void) {	
	
	// Structures girouette
	MyEncoder_Struct_TypeDef Encoder;
	MyGPIO_Struct_TypeDef PIN_GIROUETTE;
	MyTimer_Struct_TypeDef compteur_AB;
	
	// Structures Servo
	MyGPIO_Struct_TypeDef PIN_SERVO ;
	MyTimer_Struct_TypeDef TIMER3 ;
	
	volatile int mesure;
	
	// On alimente les ponts
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;
	
	// Init Servo
	PIN_SERVO.GPIO = GPIOA ;
	PIN_SERVO.GPIO_Conf = ALTOUT_PPULL ;
	PIN_SERVO.GPIO_Pin = 6 ;
	
	TIMER3.ARR = PWM_SERVO_ARR ;
	TIMER3.PSC = PWM_SERVO_PSC ;
	TIMER3.Timer = TIM3 ;
	//TIM3 alternate function is linked to PA6
	
	// Init girouette
	PIN_GIROUETTE.GPIO = GPIOA;
	PIN_GIROUETTE.GPIO_Conf = IN_PULLUP;
	PIN_GIROUETTE.GPIO_Pin = PINGIROUETTE;

	compteur_AB.Timer = TIM2;
	compteur_AB.ARR = 4*360; //on compte les quarts de degré donc on remet à 0 tous les 1440 tics
	compteur_AB.PSC = 1;
	
	
	MyTimer_Base_Init (&TIMER3) ;
	Servo_Init (TIMER3, PIN_SERVO, CHANNELPWMSERVO);
	Servo_Set_Angle(TIMER3, 0, CHANNELPWMSERVO);
	
	Encoder.Encoder_I=&PIN_GIROUETTE;
	Encoder.struct_compteur_AB=&compteur_AB;
	MyEncoder_Init(&Encoder);
	

	// On bloque tant que la girouette ne passe pas par 0
	MyEncoder_findZero();

	

	
	do {
		mesure = (int)MyEncoder_getPosition(&Encoder);
		if ((0 <= mesure && mesure < 45) || (315 <= mesure && mesure < 360)){
			Servo_Set_Angle(TIMER3, 0, CHANNELPWMSERVO);
		} else if (45 <= mesure && mesure < 180) {
			Servo_Set_Angle(TIMER3, 0.6666666667*(mesure-45), CHANNELPWMSERVO);
		} else if (180 <= mesure && mesure < 315) {
			Servo_Set_Angle(TIMER3, 0.6666666667*(315-mesure), CHANNELPWMSERVO);
		}
	} while(1) ;
}
