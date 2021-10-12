#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
typedef struct{
	MyGPIO_Struct_TypeDef * Encoder_I; // linked to external interrupt output and triggers counter reset RM 206
	MyTimer_Struct_TypeDef * struct_compteur_AB;
} MyEncoder_Struct_TypeDef;
/*
typedef struct {
	TIM_TypeDef * Timer; // TIM1 à TIM4
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef;

typedef struct{
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ; //numero de 0 à 15
	char GPIO_Conf ; // voir ci-dessous
} MyGPIO_Struct_TypeDef;

typedef struct
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_TypeDef;

*/

// pour configurer external interrupt, il faut que la PIN soit en mode input ?
// https://stm32f4-discovery.net/2014/08/stm32f4-external-interrupts-tutorial/

void MyEncoder_Init(MyEncoder_Struct_TypeDef * struct_Encoder) {
	
	// On setup les ARR et PSC des deux compteurs A et B en format timer. Un seul timer nécessaire.
	MyTimer_Base_Init(struct_Encoder->struct_compteur_AB);
	
	//////// RM 391 Encoder Interface ////////
	struct_Encoder->struct_compteur_AB->Timer->TIM_SMCR = TIM_SMCR_SMS_2; // peut aussi choisir 0 et 1.
	// on compte les transitions de TI1 et TI2 donc on choisit le mode 2.
	// input filter ? polarity selection ?
	// TI1 et TI2 c'est les deux input filter qui sont comptés par le Encoder mode. Correspondent aux TIMx_CH1 et TIMx_CH2 (RM 425).
	
	// Il faut enable le TIMER (bit CEN dans CR1)
	MyTimer_Base_Start(struct_Encoder->struct_compteur_AB->Timer);
	
	// Partie External Interrupt pour reset le counter
	// Fait avec un seul pin et un seul gpio. On se décide et on le garde, pas possible de faire un switch (trop de cas).
	
	
	// "Configure the mask bits of the 20 Interrupt lines" (RM 207)
	EXTI1->IMR = EXTI_IMR_MR1; //"Interrupt Mask on line 1" pas sur que c'est ce qu'il faut faire (je sais pas ce ue ça fait mais c'est logique).
	
	// on configure dans quels cas ya l'interruption, ici quand ya un front montant ou descendant
	EXTI1->RTSR = EXTI_RTSR_TR1; // ça veut dire "si pin 1 a un "R"ising alors on trigger l'external interrupt 1
	EXTI1->FTSR = EXTI_FTSR_TR1; // ça veut dire "si pin 1 a un "F"alling alors on trigger l'external interrupt 1
	
	/ il faut encore déclarer la fonction "EXTI1_IRQHandler" au NVIC sinon ça va pas marcher
	// En RM ça veut dire "Configure the enable and mask bits that control the NVIC IRQ channel mapped to the External Interrupt Controller
	// so that an interrupt comming from the 20 lines can be properly acknowledged"
	NVIC_EnableIRQ(EXTI1_IRQHandler) ;
	
	
	
	}
}

// là c'est que pour les pin numérotés 1 à 4 sinon le nom et sous format différent et le handler aussi
void EXTI1_IRQHandler(void) {
	TIM2->CNT = 0; //reset counter
	TIM2->SR &= ~(TIM_SR_UIF); // release interrupt
}

int main() {
	
	MyGPIO_Struct_TypeDef GPIO_I = {GPIOA, 7, In_PullUp}; // configuration pas 100% certain
	MyTimer_Struct_TypeDef compteur_AB = {TIM1, 360, 0};
	MyEncoder_Struct_TypeDef Encoder = {.Encoder_I=GPIO_I, .struct_compteur_AB=compteur_AB};
	
	
}