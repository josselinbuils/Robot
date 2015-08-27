/*
 * File:    delay.c
 * Description :    Fonctions de d�lais 
 * Project :    Robot Development Board 2013 (version 3.4)
 * Author:      Christopher BUREL
 * Version :    1 f�vrier 2013
 */

#include "delay.h"

/* Delay in microsecond */
void delay_us(double count)
{
    SETUP_TIMER_US;
    PERIOD_REGISTER = count * TIMER_COEF_US;
    TIMER_ON;
    for( TIMER_REGISTER = 0; TIMER_REGISTER < PERIOD_REGISTER;) ;	// wait for timer match period
    TIMER_OFF;
}

/* Delay in millisecond */
void delay_ms(double count)
{
    /*SETUP_TIMER_MS;
    PERIOD_REGISTER = ( count * TIMER_COEF_MS ) ;
    TIMER_ON;
    for( TIMER_REGISTER = 0; TIMER_REGISTER < PERIOD_REGISTER;) ;	// wait for timer match period
    TIMER_OFF;*/
    unsigned int i;
    for( i=0; i<count; i++)
    {
        delay_us(1000);
    }
}

/* Delay in second */
void delay_s(double count)
{
    /*
    SETUP_TIMER_S;
    PERIOD_REGISTER = count * TIMER_COEF_S;
    TIMER_ON;
    for( TIMER_REGISTER = 0; TIMER_REGISTER < PERIOD_REGISTER;) ;	// wait for timer match period
    TIMER_OFF;
     */
    #warning "delay_s is not implemented"
}