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
