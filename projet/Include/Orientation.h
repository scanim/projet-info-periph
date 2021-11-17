#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "MyUART.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"

void Orientation_Init(MyGPIO_Struct_TypeDef * broche_PWM,  MyGPIO_Struct_TypeDef * pin_sens, MyGPIO_Struct_TypeDef * GPIO_USART_RX, MyTimer_Struct_TypeDef * timer4);

void SpeedUpdate(void);

#endif
