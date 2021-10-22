#include "Driver_Servo.h"
#include "stm32f10x.h"

void Servo_Init (MyTimer_Struct_TypeDef timPWM, MyGPIO_Struct_TypeDef pinServo, char channel){
	MyGPIO_Init (&pinServo) ;
	MyTimer_PWM (timPWM.Timer, channel) ;
	Servo_Set_Angle(timPWM, 0, channel) ;
}

void Servo_Set_Angle (MyTimer_Struct_TypeDef timPWM, int angle, char channel) {
	if (angle >= 0 && angle <= 90) {
		Rapport_Cyclique (timPWM.Timer, (double)(0.05 + (double)(angle)*0.05/90.0), channel) ;
	}
}
/*
	PWM has a 50Hz frequency which makes a 20ms period
	0° on the servo is coded with 1ms high (and 19ms low) -> duty cycle of 5%
	90° is coded with 2ms high -> duty cycle of 10%
	n° is coded with a duty cycle of n*5%/90 + 5%
*/
