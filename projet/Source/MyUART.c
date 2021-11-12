#include "MyUART.h"
#include "stm32f10x.h"

void (*pHandlerRX1) (void) ;
void (*pHandlerRX2) (void) ;
void (*pHandlerRX3) (void) ;

void MyUART_Init(USART_TypeDef * USART, USART_Mode_TypeDef Mode, float Baud_Rate){
	
	// Enable USART
	USART->CR1 |= USART_CR1_UE;
	
	USART->BRR = FREQ_CPU / Baud_Rate ; //baud USART3  = = = 4800?????
	
	if(Mode == RX){
		// Enable Receiver
		USART->CR1 |= USART_CR1_RE;

	}
	
	if(Mode == TX){
		// Enable Transmiter
		USART->CR1 |= USART_CR1_TE ;
	}
}

void MyUART_RX_ActiveIT(USART_TypeDef * USART, void (*IT_function) (void)){
	
	// Enable interrupt on RXNE event
	USART->CR1 |= USART_CR1_RXNEIE;
	
	switch((int)USART) {
			case (int)(USART1) :
				pHandlerRX1 = IT_function ;
				NVIC_SetPriority(USART1_IRQn, 1);
				NVIC_EnableIRQ(USART1_IRQn);
				break;
			
			case (int)(USART2) : 
				pHandlerRX2 = IT_function ;
				NVIC_SetPriority(USART2_IRQn, 1);
				NVIC_EnableIRQ(USART2_IRQn);
				break;
			
			case (int)(USART3) : 
				pHandlerRX3 = IT_function ;
				NVIC_SetPriority(USART3_IRQn, 1);
				NVIC_EnableIRQ(USART3_IRQn);
				break;	
		}
}

void USART1_IRQHandler(void){
	USART1->SR &= ~USART_SR_RXNE ;
	if (pHandlerRX1 != 0){
		(*pHandlerRX1) ();
	}
}

void USART2_IRQHandler(void){
	USART2->SR &= ~USART_SR_RXNE ;
	if (pHandlerRX2 != 0){
		(*pHandlerRX2) ();
	}
}

void USART3_IRQHandler(void){
	USART3->SR &= ~USART_SR_RXNE ;
	if (pHandlerRX3 != 0){
		(*pHandlerRX3) ();
	}
}

void MyUART_TX_Send(USART_TypeDef * USART, char * M, int len){
	int i ; 
	for(i = 0 ; i <len ; i++){
		USART->DR = M[i] ; 
		while (!(USART->SR & (1<<6)));
	}
}



