#include "MyUART.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef GPIO_USART = {GPIOA,10,IN_PULLDOWN};

int main(){
	// Enable USART1 clock
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Enable USART2 clock
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	
	// Enable USART clock
	RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;

	MyGPIO_Init(&GPIO_USART);
	MyUART_Init(USART1, 7500);
	while(1);
	return 0;
}
