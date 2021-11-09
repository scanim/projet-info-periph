#include "MyUART.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef GPIO_USART_RX = {GPIOA,10,ALTOUT_PPULL};
MyGPIO_Struct_TypeDef GPIO_USART_TX = {GPIOB,10,IN_PULLDOWN};

char test_string[] = "coucou" ; 
int main(){
	// Enable USART1 clock
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Enable USART2 clock
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	
	// Enable USART clock
	RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;

	MyGPIO_Init(&GPIO_USART_RX);
	MyGPIO_Init(&GPIO_USART_TX);
	
	MyUART_Init(USART1, 9600);
	MyUART_Init(USART3, 9600);
	
	while(1){
		MyUART_Send(USART3,test_string,7);
	}
	return 0;
}
