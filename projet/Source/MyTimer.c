#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Bordage.h"

void (*pHandlerTim1) (void) ;
void (*pHandlerTim2) (void) ;
void (*pHandlerTim3) (void) ;
void (*pHandlerTim4) (void) ;


void MyTimer_Base_Init (MyTimer_Struct_TypeDef * TimerStruct){
	
	TimerStruct->Timer->PSC = TimerStruct->PSC - 1 ;
	
	TimerStruct->Timer->ARR = TimerStruct->ARR - 1 ;
	
	MyTimer_Base_Start (TimerStruct) ;
	
}


void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio, void (*IT_function) (void)){
	
	Timer->DIER |= TIM_DIER_UIE ;
	
	switch ((uint32_t)Timer) {
		
		case TIM1_BASE:
			pHandlerTim1 = IT_function ;
			NVIC_EnableIRQ (TIM1_UP_IRQn) ;
			NVIC_SetPriority (TIM1_UP_IRQn , Prio) ;
			break ;
		
		case TIM2_BASE:
			pHandlerTim2 = IT_function ;
			NVIC_EnableIRQ (TIM2_IRQn) ;
			NVIC_SetPriority (TIM2_IRQn , Prio) ;
			break ;
		
		case TIM3_BASE:
			pHandlerTim3= IT_function ;
			NVIC_EnableIRQ (TIM3_IRQn) ;
			NVIC_SetPriority (TIM3_IRQn , Prio) ;
			break ;
		
		case TIM4_BASE:
			pHandlerTim4 = IT_function ;
			NVIC_EnableIRQ (TIM4_IRQn) ;
			NVIC_SetPriority (TIM4_IRQn , Prio) ;
			break ;
	}
	
}


void TIM1_UP_IRQHandler ( void ){
	
	TIM1->SR &= ~TIM_SR_UIF ;
	
	if (pHandlerTim1 != 0){
		(*pHandlerTim1) (); /* appel indirect de la fonction */
	}
	
}


void TIM2_IRQHandler ( void ){
	
	TIM2->SR &= ~TIM_SR_UIF ;
	
	if (pHandlerTim2 != 0){
		(*pHandlerTim2) (); /* appel indirect de la fonction */
	}
	
}


void TIM3_IRQHandler ( void ){
	
	TIM3->SR &= ~TIM_SR_UIF ;
	
	if (pHandlerTim3 != 0){
		(*pHandlerTim3) (); /* appel indirect de la fonction */
	}
	
}


void TIM4_IRQHandler ( void ){
	
	TIM4->SR &= ~TIM_SR_UIF ;
	
	if (pHandlerTim4 != 0){
		(*pHandlerTim4) (); /* appel indirect de la fonction */
	}

}

	
void MyTimer_PWM (TIM_TypeDef * Timer, char Channel){
	
	switch (Channel) {
		
		case '1':
			Timer->CCMR1 &= ~TIM_CCMR1_OC1M_0;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_1| TIM_CCMR1_OC1M_2;
			Timer->CCER |= TIM_CCER_CC1E;
			break ;
		
		case '2':
			Timer->CCMR1 &= ~TIM_CCMR1_OC2M_0;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
			Timer->CCER |= TIM_CCER_CC2E;
			break ;
		
		case '3':
			Timer->CCMR2 &= ~TIM_CCMR2_OC3M_0;
			Timer->CCMR2|= TIM_CCMR2_OC3M_1| TIM_CCMR2_OC3M_2;
			Timer->CCER |= TIM_CCER_CC3E;
			break ;
		
		case '4':
			Timer->CCMR2 &= ~TIM_CCMR2_OC4M_0;
			Timer->CCMR2 |= TIM_CCMR2_OC4M_1| TIM_CCMR2_OC4M_2;
			Timer->CCER |= TIM_CCER_CC4E;
			break ;
	}
	
}


void PWM_Duty_Cycle (TIM_TypeDef * Timer, double Pourcentage, char Channel){
	
	int valeur = ((double)(Timer->ARR) * Pourcentage) ;
	
	switch (Channel) {
		
		case '1':
			Timer->CCR1 = valeur ;
			break ;
		
		case '2':
			Timer->CCR2 = valeur ;
			break ;
		
		case '3':
			Timer->CCR3 = valeur ;
			break ;
		
		case '4':
			Timer->CCR4 = valeur ;
			break ;
	}
	
}

