#ifndef DRIVERSERVO_H
#define DRIVERSERVO_H

#include "Driver_GPIO.h"
#include "MyTimer.h"

/*
**************************************************************************************************
* @brief
* @param :
	- MyTimer_Struct_TypeDef timPWM : Timer on which PWM will be executed
	- MyGPIO_Struct_TypeDef pinServo : pin that will be linked to the servomotor
* @Note : Init specified servo pin and PWM. TIMER IS NOT INITIALIZED
**************************************************************************************************
*/
void Servo_Init (MyTimer_Struct_TypeDef timPWM, MyGPIO_Struct_TypeDef pinServo, char channel);

/*
**************************************************************************************************
* @brief
* @param :
	- MyTimer_Struct_TypeDef timPWM : Timer on which PWM is running
	- int angle : angle between the longitudinal axe and the servo (0 to 180°)
	- char channel : channel of the PWM used
* @Note : Servo_Init must have been launched
**************************************************************************************************
*/
void Servo_Set_Rotation (MyTimer_Struct_TypeDef timPWM, int angle, char channel);


#endif
