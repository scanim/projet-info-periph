#include "MySPI.h"

void (*pHandler_SPI_RX1) (void) ;
void (*pHandler_SPI_RX2) (void) ;
void (*pHandler_SPI_RX3) (void) ;

void MySPI_Init(SPI_TypeDef * SPI, SPI_Mode_TypeDef Mode){
	
	// Enable SPI
	SPI->CR1 |= SPI_CR1_SPE;
	
	if(Mode == RX){
		// Enable Receiver
		SPI->CR2 |= SPI_CR2_RXDMAEN ;
	}
	
	if(Mode == TX){
		// Enable Transmiter
		SPI->CR2 |= SPI_CR2_TXDMAEN ;
	}
}

void MySPI_RX_ActiveIT(SPI_TypeDef * SPI, void (*IT_function) (void)){
	
	// Enable interrupt on RXNE event
	SPI->CR2 |= SPI_CR2_RXNEIE;
	
	switch((int)SPI) {
			case (int)(USART1) :
				pHandler_SPI_RX1 = IT_function ;
				NVIC_SetPriority(SPI1_IRQn, 1);
				NVIC_EnableIRQ(SPI1_IRQn);
				break;
			
			case (int)(USART2) : 
				pHandler_SPI_RX2 = IT_function ;
				NVIC_SetPriority(SPI2_IRQn, 1);
				NVIC_EnableIRQ(SPI2_IRQn);
				break;
		}
}

void SPI1_IRQHandler(void){
	USART1->SR &= ~USART_SR_RXNE ;
	if (pHandler_SPI_RX1 != 0){
		(*pHandler_SPI_RX1) ();
	}
}

void SPI2_IRQHandler(void){
	USART2->SR &= ~USART_SR_RXNE ;
	if (pHandler_SPI_RX2 != 0){
		(*pHandler_SPI_RX2) ();
	}
}

void MySPI_TX_Send(SPI_TypeDef * SPI, char * M, int len){
	int i ; 
	for(i = 0 ; i <len ; i++){
		SPI->TXCRCR = M[i] ; 
		while (!(SPI->SR & (1<<6))); 
	}
}
