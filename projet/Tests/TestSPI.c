#include "MySPI.h"
#include "Driver_GPIO.h"

//EXAMPLE for IT_function parameter

signed char comp = 0;

void EXAMPLE_IT_function(){
	//Only execute code if the received content has changed	
	if(comp != SPI1->RXCRCR){  
		
		/*
		* Your code . . . 
		*/
		
		comp = SPI1->RXCRCR ; 
	}
}

MyGPIO_Struct_TypeDef GPIO_SPI_MOSI = {GPIOA,7,OUT_PPULL};
MyGPIO_Struct_TypeDef GPIO_SPI_MISO = {GPIOA,6,IN_PULLDOWN};
MyGPIO_Struct_TypeDef GPIO_SPI_SCK = {GPIOA,5,OUT_PPULL};
MyGPIO_Struct_TypeDef GPIO_SPI_NSS = {GPIOA,4,OUT_PPULL}; //CS CHIP SELECT

int main(){
	
	// Enable USART1 and GPIOA clock
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Init GPIO on pin 10 as alternate input pull down 
	MyGPIO_Init(&GPIO_SPI_MOSI);
	MyGPIO_Init(&GPIO_SPI_MISO);
	MyGPIO_Init(&GPIO_SPI_SCK);
	MyGPIO_Init(&GPIO_SPI_NSS);
	
	// Init USART1 as RX with baud of 9600
	MySPI_Init(SPI1, RX);
	
	// Activate USART1 RXNE interrupt with example handler function from above
	MySPI_RX_ActiveIT(SPI1,EXAMPLE_IT_function);
	
	while(1);
	return 0;
}
