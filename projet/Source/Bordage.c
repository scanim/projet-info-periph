#include "Bordage.h"
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Driver_Servo.h"
#include "MyEncoder.h"

extern MyTimer_Struct_TypeDef TIMER_PWM_SERVO;
extern MyGPIO_Struct_TypeDef PIN_SERVO;
extern char CHANNEL_PWM_SERVO;
extern MyEncoder_Struct_TypeDef ENCODER;

void Bordage_Init(){
	Servo_Init (TIMER_PWM_SERVO, PIN_SERVO, CHANNEL_PWM_SERVO);
	Servo_Set_Angle(TIMER_PWM_SERVO, 0, CHANNEL_PWM_SERVO);
	
	MyEncoder_Init(&ENCODER);
	
	// On bloque tant que la girouette ne passe pas par 0
	MyEncoder_findZero();
}
