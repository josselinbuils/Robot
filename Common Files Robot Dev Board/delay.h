/*
 * File:    delay.h
 * Description :    Delay functions using timer
 * Project :    Robot Development Board 2013 (version 3.4)
 * Author:      Christopher BUREL
 * Version :    1 f�vrier 2013
 */

#ifndef __DELAY_H
#define __DELAY_H

#include "../Common Files Robot Dev Board/p33FJ128MC804.h"

/* Fr�quence des cycles d'instructions en MIPS
 * (voir configuration bits et fonction setup)*/
#define FCY 40  // 40 instructions = 1�s, horloge 80MHz

#define TIMER_REGISTER  TMR1        
#define PERIOD_REGISTER PR1
#define TIMER_ON        _TON = 1
#define TIMER_OFF       _TON = 0
#define SETUP_TIMER_US  _TCKPS = 1  // prescale 1:8
#define SETUP_TIMER_MS  _TCKPS = 3  // prescale 1:256
#define SETUP_TIMER_S   _TCKPS = 3  // prescale 1:256
#define TIMER_COEF_US   ( (FCY) / 8 )
#define TIMER_COEF_MS   ( ( (FCY)*1000 ) / 256 )
#define TIMER_COEF_S    ( ( (FCY)*1000 ) / 256 )

/* Delay in microsecond */
void delay_us(double);

/* Delay in millisecond */
void delay_ms(double);

/* Delay in second */
void delay_s(double);

#endif
