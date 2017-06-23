#include "delay.h"

void delay_us(double count) {
    SETUP_TIMER_US;
    PERIOD_REGISTER = count * TIMER_COEF_US;
    TIMER_ON;
    for (TIMER_REGISTER = 0; TIMER_REGISTER < PERIOD_REGISTER;); // wait for timer match period
    TIMER_OFF;
}

void delay_ms(double count) {
    unsigned int i;
    for (i = 0; i < count; i++) {
        delay_us(1000);
    }
}