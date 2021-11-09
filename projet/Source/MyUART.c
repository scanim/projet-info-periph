#include "MyUART.h"
#include "stm32f10x.h"

void MyUART_Init(USART_TypeDef * USART, float Baud_Rate){
	
				
	
	
	// Enable both Transmitter and Receiver
	USART->CR1 |= USART_CR1_RE | USART_CR1_TE;

	// Enable interrupt on RXNE event
	USART->CR1 |= USART_CR1_RXNEIE;
	
	// Enable USART
	USART->CR1 |= USART_CR1_UE;
	USART->BRR = FREQ_CPU / Baud_Rate ; 
	
	//RDR : Interrupt init
	//USART->CR1 |= USART_CR1_RXNEIE ;
	
	switch((int)USART) {
		case (int)(USART1) :
//			
//			// Enable USART clock
//			RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;

			NVIC_SetPriority(USART1_IRQn, 1);
			NVIC_EnableIRQ(USART1_IRQn);
			break;
		
		case (int)(USART2) : 

			

			NVIC_SetPriority(USART2_IRQn, 1);
			
			NVIC_EnableIRQ(USART2_IRQn);
			break;
		
		case (int)(USART3) : 
			
			NVIC_SetPriority(USART3_IRQn, 1);
			
			NVIC_EnableIRQ(USART3_IRQn);
			break;	
	}
	
}
int n = 0;
char comp = 0;
signed char comp_signed = 0;

void USART1_IRQHandler(void){
	USART1->SR &= ~USART_SR_RXNE ;
	if(comp != USART1->DR){
		n++ ;
		comp = USART1->DR ; 
		comp_signed = (signed char)comp;
	}
	
}

void USART2_IRQHandler(void){
	USART2->SR &= ~USART_SR_RXNE ;
	n++ ; 
}

void USART3_IRQHandler(void){
	USART3->SR &= ~USART_SR_RXNE ;
	n++ ; 
}

void MyUART_Send(USART_TypeDef * USART, char * M, int len){
	int i ; 
	for(i = 0 ; i <len ; i++){
		USART->DR = M[i] ; 
	}
}



