#include "Orientation.h"

#include "MyUART.h"
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

void Orientation_Init(MyGPIO_Struct_TypeDef * broche_PWM,  MyGPIO_Struct_TypeDef * pin_sens, MyGPIO_Struct_TypeDef * GPIO_USART_RX, MyTimer_Struct_TypeDef * timer4){
	MyGPIO_Init (broche_PWM) ;
	MyGPIO_Init (pin_sens) ;
	MyGPIO_Init(GPIO_USART_RX);
	
	MyUART_Init(USART1, RX, 9600);

	MyTimer_PWM (timer4->Timer, '1') ;
}

void SpeedUpdate () {
	static signed char input_vitesse = 0;
	if(input_vitesse != USART1->DR){  
		input_vitesse = USART1->DR ;
		if (input_vitesse<0) {
			MyGPIO_Reset (GPIOB, 5) ;
			PWM_Duty_Cycle (TIM4, (double)(input_vitesse*(-1))/100.0, '1') ;
		} else {
			MyGPIO_Set (GPIOB, 5) ;
			PWM_Duty_Cycle (TIM4, (double)(input_vitesse)/100.0, '1') ;
		}
	}
}
