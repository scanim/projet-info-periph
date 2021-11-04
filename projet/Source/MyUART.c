#include "MyUART.h"
#include "stm32f10x.h"

void MyUART_Init(USART_TypeDef * USART, short Baud_Rate){
	USART->BRR = Baud_Rate ; 
	
	//RDR : Interrupt init
	USART->CR1 |= USART_CR1_RXNEIE ;
	
	switch((int)USART) {
		case (int)(USART1) : 
			NVIC_EnableIRQ(USART1_IRQn);
			break;
		case (int)(USART2) : 
			NVIC_EnableIRQ(USART2_IRQn);
			break;
		case (int)(USART3) : 
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

