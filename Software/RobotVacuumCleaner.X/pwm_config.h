#include <xc.h>
#include <stdint.h>

#define PWM_MAX 1000     // 100% duty cycle
#define PWM_FERIOD PR2 = 249;        // Set the PWM feriod

void setTRM2ForPWM() {
    // Clear The Timer2 Register. To start counting from 0
    TMR2 = 0;
    // Choose the local clock source (timer mode)
    TMR2ON = 1;
    // Choose the desired prescale ratio (1:4)
    T2CKPS0 = 1;
    T2CKPS1 = 0;
}

/* Duty value is as percent, it's value is between 0 and 100 percent */
void PWM1_DutyCycle(uint16_t Duty_Cycle) {
    Duty_Cycle *= (PWM_MAX / 100);
    // Write to CCP1CON<5:4>
    CCP1Y = Duty_Cycle & (1 << 0);
    CCP1X = Duty_Cycle & (1 << 1);
    // Write to CCPR1L register
    CCPR1L = Duty_Cycle >> 2;
}

void PWM2_DutyCycle(uint16_t Duty_Cycle) {
    Duty_Cycle *= (PWM_MAX / 100);
    // Write to CCP1CON<5:4>
    CCP2Y = Duty_Cycle & (1 << 0);
    CCP2X = Duty_Cycle & (1 << 1);
    // Write to CCPR1L register
    CCPR2L = Duty_Cycle >> 2;
}

/* This function allow PWM module run immediately */
void PWM1_Init() {
    // Configure the CCP1 module for PWM operation
    CCP1M2 = 1;
    CCP1M3 = 1;
    // Set CCP1 pin as output
    TRISC2 = 0;
    PWM1_DutyCycle(0);
}

void PWM2_Init() {
    // Configure the CCP2 module for PWM operation
    CCP2M2 = 1;
    CCP2M3 = 1;
    // Set CCP2 pin as output
    TRISC1 = 0;
    PWM2_DutyCycle(0);
}

/* This function stop PWM module */
void PWM1_Stop() {
    CCP2M2 = 0;
    CCP2M3 = 0;
}

void PWM2_Stop() {
    CCP2M2 = 0;
    CCP2M3 = 0;
}
