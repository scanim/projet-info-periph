#ifndef BORDAGE_H
#define BORDAGE_H

#include "Driver_Servo.h"
#include "MyEncoder.h"
#include "MyPin.h"

/* 
TIMER MUST HAVE BEEN BE BASE_INIT()
-init pwm
-set gpio for the given pin
-set servo angle to 0
-BLOCKS UNTIL GIROUETTE GOES THROUGH INDEX (0°)
*/
void Bordage_Init(MyTimer_Struct_TypeDef * timer_pwm_servo, MyGPIO_Struct_TypeDef * pin_servo, MyEncoder_Struct_TypeDef * encoder);

#endif
