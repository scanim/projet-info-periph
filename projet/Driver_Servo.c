#include "Driver_Servo.h"
#include "stm32f10x.h"

void Servo_Init (MyTimer_Struct_TypeDef timPWM, MyGPIO_Struct_TypeDef pinServo, char channel){
	MyGPIO_Init (&pinServo) ;
	MyTimer_PWM (timPWM.Timer, channel) ;
	Rapport_Cyclique (timPWM.Timer, 5.0, channel) ; //!!!change to Servo_Set_Rotation()
}
