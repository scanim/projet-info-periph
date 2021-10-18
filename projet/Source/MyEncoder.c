#include "Driver_GPIO.h"
<<<<<<< HEAD
#include "MyTimer.h"
#include "stm32f10x.h"
#include "MyEncoder.h"
=======
#include "MyEncoder.h"
#include "MyTimer.h"
#include "stm32f10x.h"

/* TODO:
 
 _Position 0
_Savoir le sens ça marche là ? Sens positif ou négatif ?
_Input filter ? Polarity ?
_Compte automatiquement ou faut refraîchir dans la boucle ?
_EXTI marche ?
_GPIO Index configuré comment ? In_PullUp pour l'instant (input obligé, PullUp car ça doit être des 0 et 1)
*/


/*
typedef struct {
	TIM_TypeDef * Timer; // TIM1 à TIM4
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef;
>>>>>>> main

int initialized = 0; 

void MyEncoder_Init(MyEncoder_Struct_TypeDef * struct_Encoder) {
	
	// On setup les ARR et PSC des deux compteurs A et B en format timer. Un seul timer nécessaire.
	// On enable aussi le TIMER (bit CEN dans CR1)
	MyTimer_Base_Init(struct_Encoder->struct_compteur_AB);
	
	MyTimer_Base_Start(struct_Encoder->struct_compteur_AB->Timer);
	//////// RM 391 Encoder Interface ////////
<<<<<<< HEAD
	struct_Encoder->struct_compteur_AB->Timer->SMCR = TIM_SMCR_SMS_1; // peut aussi choisir 0 et 1.
=======
	struct_Encoder->struct_compteur_AB->Timer->SMCR = TIM_SMCR_SMS_0; // peut aussi choisir 0 et 1.
>>>>>>> main
	// on compte les transitions de TI1 et TI2 donc on choisit le mode 2.
	// input filter ? polarity selection ?
	// TI1 et TI2 c'est les deux input filter qui sont comptés par le Encoder mode. Correspondent aux TIMx_CH1 et TIMx_CH2 (RM 425).
	
<<<<<<< HEAD
	// Il faut enable le TIMER (bit CEN dans CR1)
	MyTimer_Base_Init(struct_Encoder->struct_compteur_AB);
=======

	
>>>>>>> main
	
	// Partie External Interrupt pour reset le counter
	// Fait avec un seul pin et un seul gpio. On se décide et on le garde, pas possible de faire un switch (trop de cas).
	
	
	
	// "Configure the mask bits of the 20 Interrupt lines" (RM 207)
<<<<<<< HEAD
	EXTI->IMR = EXTI_IMR_MR4; //"Interrupt Mask on line 1" pas sur que c'est ce qu'il faut faire (je sais pas ce ue ça fait mais c'est logique).
	//EXTI->EMR = EXTI_EMR_MR2; //"Interrupt Mask on line 1" pas sur que c'est ce qu'il faut faire (je sais pas ce ue ça fait mais c'est logique).
=======
	EXTI->IMR = EXTI_IMR_MR1; //"Interrupt Mask on line 1" pas sur que c'est ce qu'il faut faire (je sais pas ce ue ça fait mais c'est logique).
>>>>>>> main
	
	//2 -> 4
	// on configure dans quels cas ya l'interruption, ici quand ya un front montant ou descendant
<<<<<<< HEAD
	EXTI->RTSR = EXTI_RTSR_TR4; // ça veut dire "si pin 1 a un "R"ising alors on trigger l'external interrupt 1
	EXTI->FTSR = EXTI_FTSR_TR4; // ça veut dire "si pin 1 a un "F"alling alors on trigger l'external interrupt 1
	
	// il faut encore déclarer la fonction "EXTI1_IRQHandler" au NVIC sinon ça va pas marcher
	// En RM ça veut dire "Configure the enable and mask bits that control the NVIC IRQ channel mapped to the External Interrupt Controller
	// so that an interrupt comming from the 20 lines can be properly acknowledged"
	NVIC_EnableIRQ(EXTI4_IRQn);
	
}

void MyEncoder_findZero(void) {
	while (initialized!=1) {}
}


short MyEncoder_getPosition(MyEncoder_Struct_TypeDef * struct_encoder) {
	return struct_encoder->struct_compteur_AB->Timer->CNT;
}


void EXTI4_IRQHandler(void) {
	TIM2->CNT = 0; //reset counter
	EXTI->PR |= ~(EXTI_PR_PR4); // release interrupt
	initialized = 1 ;
}

=======
	EXTI->RTSR = EXTI_RTSR_TR1; // ça veut dire "si pin 1 a un "R"ising alors on trigger l'external interrupt 1
	EXTI->FTSR = EXTI_FTSR_TR1; // ça veut dire "si pin 1 a un "F"alling alors on trigger l'external interrupt 1
	
	// Déclare l'interrupt au NVIC
	NVIC_EnableIRQ(EXTI1_IRQn) ;

}

unsigned short MyEncoder_getPosition(MyEncoder_Struct_TypeDef * struct_Encoder) {
	return struct_Encoder->struct_compteur_AB->Timer->CNT;
}

// là c'est que pour les pin numérotés 1 à 4 sinon le nom et sous format différent et le handler aussi
void EXTI1_IRQHandler(void) {
	TIM3->CNT = 0; //reset counter
	//TIM3->SR &= ~(TIM_SR_UIF); // release interrupt
	EXTI->PR &= ~(EXTI_PR_PR1);
}

void procedure_test() {
	
	MyGPIO_Struct_TypeDef GPIO_I = {GPIOA, 1, IN_PULLUP}; // configuration pas 100% certain
	MyTimer_Struct_TypeDef compteur_AB = {TIM3, 360, 1};
	MyEncoder_Struct_TypeDef encoder; 
	
	encoder.Encoder_I = &GPIO_I;
	encoder.struct_compteur_AB = &compteur_AB;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM4EN ;
	
	
	
	
	while (1) {
		/*
		if (MyEncoder_getPosition(encoder) == 0) {
		}
		*/
	}
	
	
}
>>>>>>> main
