#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "MyEncoder.h"

// pour configurer external interrupt, il faut que la PIN soit en mode input ?
// https://stm32f4-discovery.net/2014/08/stm32f4-external-interrupts-tutorial/

void MyEncoder_Init(MyEncoder_Struct_TypeDef * struct_Encoder) {
	
	// On setup les ARR et PSC des deux compteurs A et B en format timer. Un seul timer nécessaire.
	MyTimer_Base_Init(struct_Encoder->struct_compteur_AB);
	
	//////// RM 391 Encoder Interface ////////
	struct_Encoder->struct_compteur_AB->Timer->SMCR = TIM_SMCR_SMS_1; // peut aussi choisir 0 et 1.
	// on compte les transitions de TI1 et TI2 donc on choisit le mode 2.
	// input filter ? polarity selection ?
	// TI1 et TI2 c'est les deux input filter qui sont comptés par le Encoder mode. Correspondent aux TIMx_CH1 et TIMx_CH2 (RM 425).
	
	// Il faut enable le TIMER (bit CEN dans CR1)
	MyTimer_Base_Init(struct_Encoder->struct_compteur_AB);
	
	// Partie External Interrupt pour reset le counter
	// Fait avec un seul pin et un seul gpio. On se décide et on le garde, pas possible de faire un switch (trop de cas).
	
	
	// "Configure the mask bits of the 20 Interrupt lines" (RM 207)
	//EXTI->IMR = EXTI_IMR_MR1; //"Interrupt Mask on line 1" pas sur que c'est ce qu'il faut faire (je sais pas ce ue ça fait mais c'est logique).
	
	// on configure dans quels cas ya l'interruption, ici quand ya un front montant ou descendant
	EXTI->RTSR = EXTI_RTSR_TR1; // ça veut dire "si pin 1 a un "R"ising alors on trigger l'external interrupt 1
	EXTI->FTSR = EXTI_FTSR_TR1; // ça veut dire "si pin 1 a un "F"alling alors on trigger l'external interrupt 1
	
	// il faut encore déclarer la fonction "EXTI1_IRQHandler" au NVIC sinon ça va pas marcher
	// En RM ça veut dire "Configure the enable and mask bits that control the NVIC IRQ channel mapped to the External Interrupt Controller
	// so that an interrupt comming from the 20 lines can be properly acknowledged"
	NVIC_EnableIRQ(EXTI1_IRQn) ;
	
	
	
}

short MyEncoder_getPosition(MyEncoder_Struct_TypeDef * struct_encoder) {
	return struct_encoder->struct_compteur_AB->Timer->CNT;
}

int n = 0;
// là c'est que pour les pin numérotés 1 à 4 sinon le nom et sous format différent et le handler aussi

void EXTI1_IRQHandler(void) {
	TIM2->CNT = 0; //reset counter
	EXTI->PR &= ~(EXTI_PR_PR1); // release interrupt
	n+=1;
}

