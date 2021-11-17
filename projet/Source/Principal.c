#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "Driver_Servo.h"
#include "MyUART.h"
#include "Bordage.h"
#include "MyPin.h"
#include "Orientation.h"

MyTimer_Struct_TypeDef TIMER_PWM_SERVO;
MyGPIO_Struct_TypeDef PIN_SERVO;
char CHANNEL_PWM_SERVO;
MyEncoder_Struct_TypeDef ENCODER;


void Handler_Bordage(){
	int mesure = (int)MyEncoder_getPosition(&ENCODER);
	if ((0 <= mesure && mesure < 45) || (315 <= mesure && mesure < 360)){
		Servo_Set_Angle(TIMER_PWM_SERVO, 0, CHANNEL_PWM_SERVO);
	} else if (45 <= mesure && mesure < 180) {
		Servo_Set_Angle(TIMER_PWM_SERVO, 0.6666666667*(mesure-45), CHANNEL_PWM_SERVO);
	} else if (180 <= mesure && mesure < 315) {
		Servo_Set_Angle(TIMER_PWM_SERVO, 0.6666666667*(315-mesure), CHANNEL_PWM_SERVO);




	}
}

int main(void) {	
	
	
	// Structures girouette
	MyGPIO_Struct_TypeDef pin_girouette;
	MyTimer_Struct_TypeDef compteur_AB;
	// Structures Servo
	MyTimer_Struct_TypeDef timer1 ;
	// Structures Moteur Plateau et USART
	MyTimer_Struct_TypeDef timer4 ;
	MyGPIO_Struct_TypeDef pin_moteur ;
	MyGPIO_Struct_TypeDef pin_sens_moteur ;
	MyGPIO_Struct_TypeDef pin_usart_RX = {GPIOA, GPIO_USART_PIN, IN_PULLDOWN};
	
	CHANNEL_PWM_SERVO = '1';
	
	// On alimente les ponts
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_USART3EN ;
	
	// Timer interruption bordage (20ms)
	timer1.ARR = INTERRUPT_SERVO_ARR ;
	timer1.PSC = INTERRUPT_SERVO_PSC ;
	timer1.Timer = TIM1 ;
	// Timer PWM servo
	TIMER_PWM_SERVO.ARR = PWM_SERVO_ARR ;
	TIMER_PWM_SERVO.PSC = PWM_SERVO_PSC ;
	TIMER_PWM_SERVO.Timer = TIM3 ;
	
	// Init pin Servo
	PIN_SERVO.GPIO = GPIOA ;
	PIN_SERVO.GPIO_Conf = ALTOUT_PPULL ;
	PIN_SERVO.GPIO_Pin = GPIO_PIN_SERVO ;
	
	// Timer PWM plateau
	timer4.ARR = PWM_PLATEAU_ARR ;
	timer4.PSC = 1 ;
	timer4.Timer = TIM4 ;
	
	pin_moteur.GPIO = GPIOB ;
	pin_moteur.GPIO_Conf = ALTOUT_PPULL ;
	pin_moteur.GPIO_Pin = 6 ; 
	
	pin_sens_moteur.GPIO = GPIOB ;
	pin_sens_moteur.GPIO_Conf = OUT_PPULL ;
	pin_sens_moteur.GPIO_Pin = GPIO_PIN_SENS ;
	
	// Init pin girouette
	pin_girouette.GPIO = GPIOA;
	pin_girouette.GPIO_Conf = IN_PULLUP;
	pin_girouette.GPIO_Pin = PINGIROUETTE;
	
	// Timer encoder girouette
	compteur_AB.Timer = TIM2;
	compteur_AB.ARR = ENCODER_ARR; //on compte les quarts de degré donc on remet à 0 tous les 1440 tics
	compteur_AB.PSC = 1;

	ENCODER.Encoder_I=&pin_girouette;
	ENCODER.struct_compteur_AB=&compteur_AB;
	
	// Initialisations logicielles du bordage
	MyTimer_Base_Init(&TIMER_PWM_SERVO);
	MyTimer_Base_Init(&timer1);
	MyTimer_Base_Init(&timer4) ;

	Bordage_Init();
	
	MyGPIO_Init(&pin_moteur) ;
	MyGPIO_Init(&pin_sens_moteur) ;
	MyGPIO_Init(&pin_usart_RX);
	
	MyUART_Init(USART1, RX, UART_BAUD_RATE);

	MyTimer_PWM (timer4.Timer, '1') ;
	MyUART_RX_ActiveIT(USART1, SpeedUpdate);
	MyTimer_ActiveIT (TIM1, PRIO_INTERRUPT_BORDAGE, Handler_Bordage);
	
	
	
	do {
	} while(1) ;
}
