#include "MyUART.h"
#include "stm32f10x.h"

void MyUART_Init(USART_TypeDef * USART, short Baud_Rate){
	
	// Enable both Transmitter and Receiver
	USART->CR1 |= USART_CR1_RE;

	// Enable interrupt on RXNE event
	USART->CR1 |= USART_CR1_RXNEIE;
	// Enable USART2
	USART->CR1 |= USART_CR1_UE;
	USART->CR1 |= USART_CR1_OVER8;
	USART->BRR = Baud_Rate ; 
	
	//RDR : Interrupt init
	//USART->CR1 |= USART_CR1_RXNEIE ;
	
	switch((int)USART) {
		case (int)(USART1) :
			
			// Enable USART clock
			RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;

			NVIC_SetPriority(USART1_IRQn, 1);
			NVIC_EnableIRQ(USART1_IRQn);
			break;
		
		case (int)(USART2) : 
			// Enable USART clock
			RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
			

			NVIC_SetPriority(USART2_IRQn, 1);
			
			NVIC_EnableIRQ(USART2_IRQn);
			break;
		
		case (int)(USART3) : 
			// Enable USART clock
			RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;

			NVIC_SetPriority(USART3_IRQn, 1);
			
			NVIC_EnableIRQ(USART3_IRQn);
			break;	
	}
	
}
int n = 0;
void USART1_IRQHandler(void){
	USART1->SR &= ~USART_SR_RXNE ;
	n++ ; 
}

void USART2_IRQHandler(void){
	USART2->SR &= ~USART_SR_RXNE ;
	n++ ; 
}

void USART3_IRQHandler(void){
	USART3->SR &= ~USART_SR_RXNE ;
	n++ ; 
}

int main(){
	MyUART_Init(USART1, 9600);
	while(1);
	return 0;
}

