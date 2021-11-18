#ifndef MYENCODER_H
#define MYENCODER_H

#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"

typedef struct{
	MyGPIO_Struct_TypeDef * Encoder_I; // linked to external interrupt output and triggers counter reset RM 206
	MyTimer_Struct_TypeDef * struct_compteur_AB;
} MyEncoder_Struct_TypeDef;

//Initiating timer and GPIO
void MyEncoder_Init(MyEncoder_Struct_TypeDef * struct_encoder);

// Blocks the programm while initialisation of the encoder isn't complete
void MyEncoder_findZero(void);

//Returns the encoder's timer counter
short MyEncoder_getPosition(MyEncoder_Struct_TypeDef * struct_encoder);

#endif
