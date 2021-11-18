#include "Driver_Servo.h"
#include "stm32f10x.h"

void Servo_Init (MyTimer_Struct_TypeDef * timPWM, MyGPIO_Struct_TypeDef * pinServo){
	MyGPIO_Init (pinServo) ;
	MyTimer_PWM (timPWM->Timer, CHANNEL_PWM_SERVO) ;
	Servo_Set_Angle(timPWM, 0) ;
}

void Servo_Set_Angle (MyTimer_Struct_TypeDef * timPWM, int angle) {
	if (angle >= 0 && angle <= 90) {
		PWM_Duty_Cycle (timPWM->Timer, (double)(0.05 + (double)(angle)*0.05/90.0), CHANNEL_PWM_SERVO) ;
	}
}
/*
	PWM has a 50Hz frequency which makes a 20ms period
	0° on the servo is coded with 1ms high (and 19ms low) -> duty cycle of 5%
	90° is coded with 2ms high -> duty cycle of 10%
	n° is coded with a duty cycle of n*5%/90 + 5%
*/
