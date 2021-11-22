#ifndef TENSION_BATTERIE
#define TENSION_BATTERIE

#include "Driver_GPIO.h"
#include "MyADC.h"

void TensionBatterie_init(ADC_TypeDef * ADC, MyGPIO_Struct_TypeDef  GPIO_ADC);
float TensionBatterie_get() ; 


#endif