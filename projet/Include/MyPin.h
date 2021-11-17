#ifndef MYPIN_H
#define MYPIN_H

// girouette et encodeur
#define PINGIROUETTE 4
#define ENCODER_ARR 1440




// servo-moteur
#define PWM_SERVO_ARR 60000
#define PWM_SERVO_PSC 24
#define INTERRUPT_SERVO_ARR 120
#define INTERRUPT_SERVO_PSC 6000
#define PWM_PLATEAU_ARR 3600
#define GPIO_PIN_SENS 5
#define GPIO_PIN_SERVO 6 //TIM3 alternate function is linked to PA6


// USART
#define PRIO_INTERRUPT_BORDAGE 4
#define GPIO_USART_PIN 10
#define UART_BAUD_RATE 9600

//PINS
#define PIN_GIROUETTE_NUM 4
#define PIN_GIROUETTE_GPIO GPIOA
#define PIN_SERVO_NUM 6
#define PIN_SERVO_GPIO GPIOA
#define PIN_MOTEUR_NUM 
#define PIN_SENS_MOTEUR_NUM
#define PIN_USART_RX_NUM

#endif
