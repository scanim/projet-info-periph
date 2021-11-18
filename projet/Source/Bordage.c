#include "Bordage.h"

void Bordage_Init(MyTimer_Struct_TypeDef * timer_pwm_servo, MyGPIO_Struct_TypeDef * pin_servo, MyEncoder_Struct_TypeDef * encoder){
	Servo_Init (timer_pwm_servo, pin_servo);
	Servo_Set_Angle(timer_pwm_servo, 0);
	
	MyEncoder_Init(encoder);
	
	// On bloque tant que la girouette ne passe pas par 0
	MyEncoder_findZero();
}
