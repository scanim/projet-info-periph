#include "Bordage.h"
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Driver_Servo.h"
#include "MyEncoder.h"


// Variables globales qui seront utilisees dans le handler (on ne peut pas lui passer d'argument)
MyTimer_Struct_TypeDef * TIMER_PWM_SERVO;
MyGPIO_Struct_TypeDef * PIN_SERVO;
char CHANNEL_PWM_SERVO;
MyEncoder_Struct_TypeDef * ENCODER;

void Bordage_Init(MyTimer_Struct_TypeDef * timer, MyGPIO_Struct_TypeDef * pin_servo, char channel_pwm, MyEncoder_Struct_TypeDef * encoder){
	
	Servo_Init (*timer, *pin_servo, channel_pwm);
	Servo_Set_Angle(*timer, 0, channel_pwm);
	
	MyEncoder_Init(encoder);
	
	// On bloque tant que la girouette ne passe pas par 0
	MyEncoder_findZero();
	
	// Initialisation des variables du handler
	TIMER_PWM_SERVO = timer;
	PIN_SERVO = pin_servo;
	CHANNEL_PWM_SERVO = channel_pwm;
	ENCODER = encoder;
}



extern void Handler_Bordage(){
	int mesure = (int)MyEncoder_getPosition(ENCODER);
		if ((0 <= mesure && mesure < 45) || (315 <= mesure && mesure < 360)){
			Servo_Set_Angle(*TIMER_PWM_SERVO, 0, CHANNEL_PWM_SERVO);
		} else if (45 <= mesure && mesure < 180) {
			Servo_Set_Angle(*TIMER_PWM_SERVO, 0.6666666667*(mesure-45), CHANNEL_PWM_SERVO);
		} else if (180 <= mesure && mesure < 315) {
			Servo_Set_Angle(*TIMER_PWM_SERVO, 0.6666666667*(315-mesure), CHANNEL_PWM_SERVO);
		}
}
