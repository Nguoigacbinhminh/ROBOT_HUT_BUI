#include <xc.h>
#include <stdio.h>
#include "main_config.h"
#include "lcd.h"
#include "l298n_control.h"
#include "pwm_config.h"
#include "ultrasonic_sensor.h"

void main() {
    uint16_t text[4];
    LCD_Init();
//    LCD_SendCommand(0x80);
    //LCD_PutString("sdfasd ");
    
//    setTRM2ForPWM();
//    PWM1_Init();
//    PWM2_Init();
//    PWM1_DutyCycle(50);
//    PWM2_DutyCycle(50);
    
//    TRISB = 0xF0;
//    while(1) {
//        forward();
//        __delay_ms(5000);
//        reverse();
//        __delay_ms(5000);
//        stop();
//        __delay_ms(5000);
//    }
    
    setTRM1ForHCSR04();
    HCSR04_Init();
    uint16_t time = 0;
    while(1) {
        create_Pulse_Trigger();
        time = HCSR04_Get_Distance();
        LCD_SendCommand(0x80);
        sprintf(text, "%03u", time);
        LCD_PutString(text);
    }
}
