#include "Orientation.h"

#include "MyUART.h"
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "MyPin.h"

void Orientation_Init(MyGPIO_Struct_TypeDef * pin_PWM,  MyGPIO_Struct_TypeDef * pin_sens, MyGPIO_Struct_TypeDef * pin_usart_rx, MyTimer_Struct_TypeDef * timer4){
	MyGPIO_Init (pin_PWM) ;
	MyGPIO_Init (pin_sens) ;
	MyGPIO_Init(pin_usart_rx);
	
	MyUART_Init(USART1, RX, UART_BAUD_RATE);

	MyTimer_PWM (timer4->Timer, '1') ;
}

void SpeedUpdate () {
	static signed char input_vitesse = 0;
	if(input_vitesse != USART1->DR){  
		input_vitesse = USART1->DR ;
		if (input_vitesse<0) {
			MyGPIO_Reset (PIN_SENS_MOTEUR_GPIO, PIN_SENS_MOTEUR_NUM) ;
			PWM_Duty_Cycle (TIM4, (double)(input_vitesse*(-1))/100.0, '1') ;
		} else {
			MyGPIO_Set (PIN_SENS_MOTEUR_GPIO, PIN_SENS_MOTEUR_NUM) ;
			PWM_Duty_Cycle (TIM4, (double)(input_vitesse)/100.0, '1') ;
		}
	}
}
