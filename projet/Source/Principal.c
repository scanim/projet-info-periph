#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"
#include "MyUART.h"
#include "Bordage.h"
#include "MyPin.h"
#include "Orientation.h"

MyTimer_Struct_TypeDef timer_pwm_servo;
MyGPIO_Struct_TypeDef pin_servo = PIN_SERVO_INIT ;
MyEncoder_Struct_TypeDef encoder;


void Handler_Bordage(){
	int mesure = (int)MyEncoder_getPosition(&encoder);
	if ((0 <= mesure && mesure < 45) || (315 <= mesure && mesure < 360)){
		Servo_Set_Angle(&timer_pwm_servo, 0);
	} else if (45 <= mesure && mesure < 180) {
		Servo_Set_Angle(&timer_pwm_servo, 0.6666666667*(mesure-45));
	} else if (180 <= mesure && mesure < 315) {
		Servo_Set_Angle(&timer_pwm_servo, 0.6666666667*(315-mesure));
	}
}

int main(void) {	
	
	// Structures girouette
	MyGPIO_Struct_TypeDef pin_girouette = PIN_GIROUETTE_INIT;
	MyTimer_Struct_TypeDef compteur_AB;
	
	// Structures Servo
	MyTimer_Struct_TypeDef timer1 ;
	// Structures Moteur Plateau et USART
	MyTimer_Struct_TypeDef timer4 ;
	MyGPIO_Struct_TypeDef pin_moteur = PIN_MOTEUR_INIT ;
	MyGPIO_Struct_TypeDef pin_sens_moteur = PIN_SENS_MOTEUR_INIT ;
	MyGPIO_Struct_TypeDef pin_usart_RX = PIN_USART_RX_INIT ;
	MyGPIO_Struct_TypeDef pin_usart_TX = PIN_USART_TX_INIT; //not used for now
	
	// On alimente les ponts
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_USART3EN ;
	
	// Timer interruption bordage (20ms)
	timer1.ARR = INTERRUPT_SERVO_ARR ;
	timer1.PSC = INTERRUPT_SERVO_PSC ;
	timer1.Timer = TIM1 ;
	// Timer PWM servo
	timer_pwm_servo.ARR = PWM_SERVO_ARR ;
	timer_pwm_servo.PSC = PWM_SERVO_PSC ;
	timer_pwm_servo.Timer = TIM3 ;
	
	// Timer PWM plateau
	timer4.ARR = PWM_PLATEAU_ARR ;
	timer4.PSC = 1 ;
	timer4.Timer = TIM4 ;
	
	// Timer encoder girouette
	compteur_AB.Timer = TIM2;
	compteur_AB.ARR = ENCODER_ARR;
	compteur_AB.PSC = ENCODER_PSC;

	encoder.Encoder_I=&pin_girouette;
	encoder.struct_compteur_AB=&compteur_AB;
	
	// Initialisations logicielles du bordage
	MyTimer_Base_Init(&timer_pwm_servo);
	MyTimer_Base_Init(&timer1);
	MyTimer_Base_Init(&timer4) ;

	MyGPIO_Init(&pin_moteur);
	MyGPIO_Init(&pin_sens_moteur);
	MyGPIO_Init(&pin_usart_RX);
	
	Bordage_Init(&timer_pwm_servo, &pin_servo, &encoder);
	
	MyUART_Init(USART1, RX, UART_BAUD_RATE);

	MyTimer_PWM (timer4.Timer, '1') ;
	MyUART_RX_ActiveIT(USART1, SpeedUpdate);
	MyTimer_ActiveIT (TIM1, PRIO_INTERRUPT_BORDAGE, Handler_Bordage);
	
	
	
	do {
	} while(1) ;
}
