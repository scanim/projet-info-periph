#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init (MyGPIO_Struct_TypeDef * GPIOStructPtr){
	
	if (GPIOStructPtr->GPIO_Pin < 8){
		GPIOStructPtr->GPIO->CRL &= ~(0x0F << GPIOStructPtr->GPIO_Pin*4) ;
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << GPIOStructPtr->GPIO_Pin*4) ;
	} else {
		GPIOStructPtr->GPIO->CRH &= ~(0x0F << (GPIOStructPtr->GPIO_Pin-8)*4) ;
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin-8)*4) ;
	}
	
}



// renvoie 0 ou autre chose different de 0
int MyGPIO_Read (GPIO_TypeDef * GPIO , char GPIO_Pin){
	
	return GPIO->IDR &= (0x01 << GPIO_Pin) ;
	
}



void MyGPIO_Set (GPIO_TypeDef * GPIO , char GPIO_Pin){
	
	GPIO->ODR |= (0x01<<GPIO_Pin) ;
	
}



void MyGPIO_Reset (GPIO_TypeDef * GPIO , char GPIO_Pin){
	
	GPIO->ODR &= ~(0x01<<GPIO_Pin) ;
	
}



void MyGPIO_Toggle (GPIO_TypeDef * GPIO , char GPIO_Pin){
	
	GPIO->ODR ^= (0x01 << GPIO_Pin) ;
	
}

/*

	MyEncoder_Struct_TypeDef Encoder;
	MyGPIO_Struct_TypeDef GPIO_I = {GPIOA, 2, IN_PULLUP}; // configuration pas 100% certain
	MyTimer_Struct_TypeDef compteur_AB = {TIM2, 720, 1};
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;
	
	
	Encoder.Encoder_I=&GPIO_I;
	Encoder.struct_compteur_AB=&compteur_AB;
	MyEncoder_Init(&Encoder);
*/
