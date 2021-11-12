#include "MyUART.h"
#include "Driver_GPIO.h"

char test_string[7] = "coucou" ; 

MyGPIO_Struct_TypeDef GPIO_USART_TX = {GPIOA,9,ALTOUT_PPULL};

int main(){
	
	// Enable USART1 and GPIOA clock
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Init GPIO on pin 10 as alternate input pull down 
	MyGPIO_Init(&GPIO_USART_TX);
	
	// Init USART1 as RX with baud of 9600
	MyUART_Init(USART1, TX, 9600);
	
	while(1){
		MyUART_TX_Send(USART1,test_string,7) ; 
	}
	return 0;
}