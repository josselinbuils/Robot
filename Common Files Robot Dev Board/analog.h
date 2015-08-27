/*
 * Fichier :        analog.h
 * Description :    Fonctions liées aux périphériques analogiques
 * Projet :         Robot Development Board 2013 (version 3.4)
 * Auteur :         Christopher BUREL
 * Version :        1 février 2013
 */

#ifndef _analog_h
#define _analog_h

#include "p33FJ128MC804.h"

/* Paramètres */

#define ADC_CHANNEL _CH0SA
#define ADC_BUFFER  ADC1BUF0


/* Macros */

#define ADC_ON()                _ADON = 1
#define START_SAMPLING()        _SAMP = 1
#define STOP_SAMPLING()         _SAMP = 0
#define CLEAR_ADC_INT_FLAG()    _AD1IF = 0
#define WAIT_SAMPLING()         Nop();Nop();Nop();Nop();Nop()   // for(i=0; i<20; i++);
#define WAIT_CONVERSION()       while(!_AD1IF)


/* Prototypes des fonctions */

unsigned int readADC(unsigned int);

#endif
