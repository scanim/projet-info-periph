#include "MyUART.h"
#include "Driver_GPIO.h"

//EXAMPLE for IT_function parameter

signed char comp = 0;

void EXAMPLE_IT_function(){
	//Only execute code if the received content has changed	
	if(comp != USART1->DR){  
		
		/*
		* Your code . . . 
		*/
		
		comp = USART1->DR ; 
	}
}

MyGPIO_Struct_TypeDef GPIO_USART_RX = {GPIOA,10,IN_PULLDOWN};

int main(){
	
	// Enable USART1 and GPIOA clock
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Init GPIO on pin 10 as alternate input pull down 
	MyGPIO_Init(&GPIO_USART_RX);
	
	// Init USART1 as RX with baud of 9600
	MyUART_Init(USART1, RX, 9600);
	
	// Activate USART1 RXNE interrupt with example handler function from above
	MyUART_RX_ActiveIT(USART1,EXAMPLE_IT_function);
	
	while(1);
	return 0;
}
