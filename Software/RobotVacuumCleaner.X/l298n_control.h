#include <stdint.h>

#define FORWARD_LEFT RB0
#define REVERSE_LEFT RB1
#define FORWARD_RIGHT RB2
#define REVERSE_RIGHT RB3

void motor_left_forward() {
    FORWARD_LEFT = 1;
    REVERSE_LEFT = 0;
}

void motor_left_reverse() {
    FORWARD_LEFT = 0;
    REVERSE_LEFT = 1;
}

void motor_left_stop() {
    FORWARD_LEFT = 0;
    REVERSE_LEFT = 0;
}

void motor_right_forward() {
    FORWARD_RIGHT = 1;
    REVERSE_RIGHT = 0;
}

void motor_right_reverse() {
    FORWARD_RIGHT = 0;
    REVERSE_RIGHT = 1;
}

void motor_right_stop() {
    FORWARD_RIGHT = 0;
    REVERSE_RIGHT = 0;
}

void forward() {
    motor_right_forward();
    motor_left_forward();
}

void reverse(){
    motor_right_reverse();
    motor_left_reverse();
}

void stop() {
    motor_right_stop();
    motor_left_stop();
}

void turn_left() {
    motor_right_forward();
    motor_left_stop();
}

void turn_right() {
    motor_left_forward();
    motor_right_stop();
}
