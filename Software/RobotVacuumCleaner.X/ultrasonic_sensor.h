#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>

#define TRIGGER RC4
#define ECHO RC5

uint16_t time = 0;
uint16_t distance = 0;

void setTRM1ForHCSR04() {
    // Clear The Timer1 Register. To start counting from 0
    TMR1 = 0;
    // Choose the local clock source (timer mode)
    TMR1CS = 0;
    // Choose the desired prescale ratio (1:4)
    T1CKPS0 = 0;
    T1CKPS1 = 1;
}

void HCSR04_Init() {
    //  Configure The IO Pins
    TRISC4 = 0;
    RC4 = 0;
    TRISC5 = 1;
    
}

void create_Pulse_Trigger() {
    TMR1 = 0;
    // Send Trigger Pulse To The Sensor
    TRIGGER = 1;
    __delay_us(10);
    TRIGGER = 0;
    // Wait For The Echo Pulse From The Sensor
    while(!ECHO);
    // Turn ON Timer Module
    TMR1ON = 1;
    // Wait Until The Pulse Ends
    while(ECHO);
    // Turn OFF The Timer
    TMR1ON = 0;
    
    time = TMR1H << 8;
    time = time | TMR1L;
}

int8_t HCSR04_Get_Distance() {
    // Calculate The Distance Using The Equation
    if(time > 117 && time < 23529) {
        distance = time / 58.82;
        return distance;
    } else {
        return 0;
    }
}
