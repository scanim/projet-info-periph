#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "Driver_Servo.h"

#define CHANNEL '1'

int main(void){	
	
	int i;
	MyGPIO_Struct_TypeDef PIN_SERVO ;
	
	MyTimer_Struct_TypeDef TIMER3 ;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;

	
	PIN_SERVO.GPIO = GPIOA ;
	PIN_SERVO.GPIO_Conf = ALTOUT_PPULL ;
	PIN_SERVO.GPIO_Pin = 6 ;
	
	TIMER3.ARR = PWM_SERVO_ARR ;
	TIMER3.PSC = PWM_SERVO_PSC ;
	TIMER3.Timer = TIM3 ;
	
	MyTimer_Base_Init (&TIMER3) ;
	
	Servo_Init(TIMER3, PIN_SERVO, CHANNEL) ;
	
	Servo_Set_Angle(TIMER3, 0, CHANNEL);

	do
	{
		i = 0;
		while (i<10000000){i++;}
		Servo_Set_Angle(TIMER3, 45, CHANNEL);
		i = 0;
		while (i<10000000){i++;}
		Servo_Set_Angle(TIMER3, 90, CHANNEL);
		i = 0;
		while (i<10000000){i++;}
		Servo_Set_Angle(TIMER3, 45, CHANNEL);
		i = 0;
		while (i<10000000){i++;}
		Servo_Set_Angle(TIMER3, 0, CHANNEL);
	}while(1) ;
}
