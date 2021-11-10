#include "MyUART.h"
#include "stm32f10x.h"

void MyUART_Init(USART_TypeDef * USART, USART_Mode_TypeDef Mode, float Baud_Rate){
	
	USART->BRR = FREQ_CPU / Baud_Rate ; //baud USART3  = = = 4800?????
	
	if(Mode == RX){
		// Enable Receiver
		USART->CR1 |= USART_CR1_RE;

		// Enable interrupt on RXNE event
		USART->CR1 |= USART_CR1_RXNEIE;
		
		// Enable USART
		USART->CR1 |= USART_CR1_UE;

		switch((int)USART) {
			case (int)(USART1) :
	//			// Enable USART clock
	
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
	
	if(Mode == TX){
		// Enable Transmiter
		USART->CR1 |= USART_CR1_TE ;
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



