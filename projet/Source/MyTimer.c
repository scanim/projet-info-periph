#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

void (*pFnc1) (void) ;
void (*pFnc2) (void) ;
void (*pFnc3) (void) ;
void (*pFnc4) (void) ;


void MyTimer_Base_Init (MyTimer_Struct_TypeDef * TimerStruct){
	
	TimerStruct->Timer->PSC = TimerStruct->PSC - 1 ;
	
	TimerStruct->Timer->ARR = TimerStruct->ARR - 1 ;
	
	MyTimer_Base_Start (TimerStruct) ;
	
}


void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio, void (*IT_function) (void)){
	
	Timer->DIER |= TIM_DIER_UIE ;
	
	switch ((uint32_t)Timer) {
		
		case TIM1_BASE:
			pFnc1 = IT_function ;
			NVIC_EnableIRQ (TIM1_UP_IRQn ) ;
			NVIC_SetPriority (TIM1_UP_IRQn , Prio) ;
			break ;
		
		case TIM2_BASE:
			pFnc2 = IT_function ;
			NVIC_EnableIRQ (TIM2_IRQn) ;
			NVIC_SetPriority (TIM2_IRQn , Prio) ;
			break ;
		
		case TIM3_BASE:
			pFnc3= IT_function ;
			NVIC_EnableIRQ (TIM3_IRQn) ;
			NVIC_SetPriority (TIM3_IRQn , Prio) ;
			break ;
		
		case TIM4_BASE:
			pFnc4 = IT_function ;
			NVIC_EnableIRQ (TIM4_IRQn) ;
			NVIC_SetPriority (TIM4_IRQn , Prio) ;
			break ;
	}
	
}


void TIM1_IRQHandler ( void ){
	
	TIM1->SR &= ~TIM_SR_UIF ;
	
	if (pFnc1 != 0){
		(*pFnc1) (); /* appel indirect de la fonction */
	}
	
}


void TIM2_IRQHandler ( void ){
	
	TIM2->SR &= ~TIM_SR_UIF ;
	
	if (pFnc2 != 0){
		(*pFnc2) (); /* appel indirect de la fonction */
	}
	
}


void TIM3_IRQHandler ( void ){
	
	TIM3->SR &= ~TIM_SR_UIF ;
	
	if (pFnc3 != 0){
		(*pFnc3) (); /* appel indirect de la fonction */
	}
	
}


void TIM4_IRQHandler ( void ){
	
	TIM4->SR &= ~TIM_SR_UIF ;
	
	if (pFnc4 != 0){
		(*pFnc4) (); /* appel indirect de la fonction */
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

