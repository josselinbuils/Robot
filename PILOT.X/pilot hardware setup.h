/* 
 * File:    pilot hardware setup.h
 * Description :    Définition des ports et initialisation du pilote
 * Project :    Robot Development Board 2013 (version 3.4)
 * Author:      Christopher BUREL
 * Version :    1 février 2013
 */

#ifndef PILOT_HARDWARE_SETUP_H
#define	PILOT_HARDWARE_SETUP_H

/* Include all header files here, just include "pilot hardware setup.h" in other files */
#include "../Common Files Robot Dev Board/p33FJ128MC804.h"
#include "../Common Files Robot Dev Board/analog.h"
#include "../Common Files Robot Dev Board/delay.h"
#include "../Common Files Robot Dev Board/lcd.h"

// Paramètres de configuration (par défaut: 0=not defined, 1=defined)
#define AN  (2)   // analog
#define IN  (3)   // input
#define OUT (4)   // output
// Déclaration des pins (permet de les nommer ensuite)
#define PIN_9   // pins synchro
#define PIN_8
#define PIN_3
#define PIN_2
#define PIN_1
#define PIN_44
#define PIN_43
#define PIN_42
#define PIN_19  // pins 19 à 26
#define PIN_20
#define PIN_21  
#define PIN_22
#define PIN_23
#define PIN_24
#define PIN_25
#define PIN_26


/********* Configurations des pins ***************
 * Nommer la pin (facultatif, la pin est nommer PIN_x par défaut)
 * (/!\ ne pas supprimer les caractères "\")
 * Définir la configuration :
 *      AN : entrée analogique
 *      IN : entrée numérique
 *      OUT : sortie numérique
 */
// PIN 19
#define SHARP_LEFT                PIN_19
#define PIN_19_CONFIG       AN
// PIN 20
#define SHARP_MIDDLE                PIN_20
#define PIN_20_CONFIG       AN
// PIN 21 (/!\ switch ICSP/PIN)
#define SHARP_RIGHT                PIN_21
#define PIN_21_CONFIG       AN
// PIN 22 (/!\ switch ICSP/PIN)
#define DETECTEUR_AR                PIN_22
#define PIN_22_CONFIG       IN
// PIN 23
#define CAPTEUR_DROITE               PIN_23
#define PIN_23_CONFIG       AN
// PIN 24
#define CAPTEUR_DISTANCE            PIN_24
#define PIN_24_CONFIG       AN
// PIN 25
#define CAPTEUR_25                  PIN_25
#define PIN_25_CONFIG       IN
// PIN 26
#define COLOR_SENSOR                PIN_26
#define PIN_26_CONFIG       AN

/* Configurations des pins synchro */
// Nommer les pins
#define SPI_CK          PIN_9
#define SPI_IN          PIN_8
#define SPI_OUT         PIN_3
#define SPI_CS          PIN_2
#define I2C_SDA         PIN_1
#define I2C_SCL         PIN_44
#define START_PILOT     PIN_43
#define SYNCHRO_BIDULE  PIN_42
// Configurer les pins
#undef PIN_9
#define PIN_9   _RB11
#undef PIN_8
#define PIN_8   _RB10
#undef PIN_3
#define PIN_3   _RC7
#undef PIN_2
#define PIN_2   _RC6
#undef PIN_1
#define PIN_1   _RB9
#undef PIN_44
#define PIN_44  _RB8
#undef PIN_43
#define PIN_43  _RB7    // ordre du copilot
#undef PIN_42
#define PIN_42  _RB6
#define SETUP_PIN_9()   _TRISB11 = 1
#define SETUP_PIN_8()   _TRISB10 = 1
#define SETUP_PIN_3()   _TRISC7 = 1
#define SETUP_PIN_2()   _TRISC6 = 1
#define SETUP_PIN_1()   _TRISB9 = 1
#define SETUP_PIN_44()  _TRISB8 = 1
#define SETUP_PIN_43()  _TRISB7 = 1     // ordre du copilot
#define SETUP_PIN_42()  _TRISB6 = 1

/* Définition et orentation des autres ports entrées/sorties */
// LED
#define LED             _LATB5
#define SETUP_LED()     _TRISB5 = 0     // output
#define LED_ON          LED = 1
#define LED_OFF         LED = 0
#define LED_TOGGLE      LED = !LED

// Switch
#define SELECT          _RC3
#define SETUP_SELECT()  _TRISC3 = 1   // input

// Equipe
#define EQUIPE SELECT

/* Configurations moteurs (PWM) */
#define ENABLE_PWM          P1TCONbits.PTEN = 1                         // PWM time base is on
#define PWM_FREQ_KHZ        20                                          // Fréquence PWM en kHz
#define SETUP_PWM_PERIOD()  _PTPER = (40000/(PWM_FREQ_KHZ))             // Période PWM = 2000 TCY (pour 20kHz)
#define SETUP_PWM_MODE()    {_PTMOD = 0; _PMOD1 = 1; _PMOD2 = 1;}       // Edge aligned mode, PWM I/O pin pair independent
#define SETUP_PWM_M1()      {_PEN1H = 1; _PEN1L = 0;}                   // pin DIR_M1 = PWM, pin PWM_M1 = I/O (locked anti-phase PWM)
#define SETUP_PWM_M2()      {_PEN2H = 1; _PEN2L = 0;}                   // pin DIR_M2 = PWM, pin PWM_M2 = I/O (locked anti-phase PWM)
// pin de frein moteur
#define SETUP_BRAKE()       {_TRISB15 = 0; _TRISB13 = 0;}               // frein moteur = pin PWM_Mx (locked anti-phase PWM)
#define BRAKE_M1            _LATB15 = 0                                 // frein moteur 1
#define BRAKE_M2            _LATB13 = 0                                 // frein moteur 2
#define ENABLE_M1           _LATB15 = 1                                 // débloque moteur 1
#define ENABLE_M2           _LATB13 = 1                                 // débloque moteur 2
// Vitesse+direction moteur : Xmax/min = +/-PTPER (-2000 recule et 2000 avance 100%, pour 20kHz, 0 arrêt moteur)
#define SETPOINT_M1(X)      if (X == 0) {BRAKE_M1;} else {PDC1 = _PTPER + (X); ENABLE_M1;}
#define MOTEUR_GAUCHE(X)    SETPOINT_M1(X)                              // MOTEUR GAUCHE = M1
#define SETPOINT_M2(X)      if (X == 0) {BRAKE_M2;} else {PDC2 = _PTPER + (X); ENABLE_M2;}
#define MOTEUR_DROIT(X)     SETPOINT_M2(X)                              // MOTEUR DROIT = M2
#define SETUP_DUTY_CYCLE()  {_IUE = 1; SETPOINT_M1(0); SETPOINT_M2(0);} // Immediate update of duty cycle enabled,
#define SETUP_DEAD_TIME()   P1DTCON1bits.DTA = 40                       // dead time 40 TCY = 1µs (recommended for LMD18200)



// Ecran LCD : voir lcd.h


/* Gestion de configuration des pins 19 à 26 */
// PIN 19
#if PIN_19_CONFIG == AN
    #undef PIN_19
    #define PIN_19  ( readADC(0) )          // AN0
    #define SETUP_PIN_19()  {_PCFG0 = 0;}
#elif PIN_19_CONFIG == IN
    #undef PIN_19
    #define PIN_19  _RA0
    #define SETUP_PIN_19()  {_PCFG0 = 1; _TRISA0 = 1;}
#elif PIN_19_CONFIG == OUT
    #undef PIN_19
    #define PIN_19  _LATA0
    #define SETUP_PIN_19()  {_PCFG0 = 1; _TRISA0 = 0;}
#else
    #error "PIN 19 not configured"
#endif
// PIN 20
#if PIN_20_CONFIG == AN
    #undef PIN_20
    #define PIN_20  ( readADC(1) )          // AN1
    #define SETUP_PIN_20()  {_PCFG1 = 0;}
#elif PIN_20_CONFIG == IN
    #undef PIN_20
    #define PIN_20  _RA1
    #define SETUP_PIN_20()  {_PCFG1 = 1; _TRISA1 = 1;}
#elif PIN_20_CONFIG == OUT
    #undef PIN_20
    #define PIN_20  _LATA1
    #define SETUP_PIN_20()  {_PCFG1 = 1; _TRISA1 = 0;}
#else
    #error "PIN 20 not configured"
#endif
// PIN 21
#if PIN_21_CONFIG == AN
    #undef PIN_21
    #define PIN_21  ( readADC(2) )          // AN2
    #define SETUP_PIN_21()  {_PCFG2 = 0;}   
#elif PIN_21_CONFIG == IN
    #undef PIN_21
    #define PIN_21  _RB0
    #define SETUP_PIN_21()  {_PCFG2 = 1; _TRISB0 = 1;}
#elif PIN_21_CONFIG == OUT
    #undef PIN_21
    #define PIN_21  _LATB0
    #define SETUP_PIN_21()  {_PCFG2 = 1; _TRISB0 = 0;}
#else
    #error "PIN 21 not configured"
#endif
// PIN 22
#if PIN_22_CONFIG == AN
    #undef PIN_22
    #define PIN_22  ( readADC(3) )          // AN3
    #define SETUP_PIN_22()  {_PCFG3 = 0;}   
#elif PIN_22_CONFIG == IN
    #undef PIN_22
    #define PIN_22  _RB1
    #define SETUP_PIN_22()  {_PCFG3 = 1; _TRISB1 = 1;}
#elif PIN_22_CONFIG == OUT
    #undef PIN_22
    #define PIN_22  _LATB1
    #define SETUP_PIN_22()  {_PCFG3 = 1; _TRISB1 = 0;}
#else
    #error "PIN 22 not configured"
#endif
// PIN 23
#if PIN_23_CONFIG == AN
    #undef PIN_23
    #define PIN_23  ( readADC(4) )          // AN4
    #define SETUP_PIN_23()  {_PCFG4 = 0;}   
#elif PIN_23_CONFIG == IN
    #undef PIN_23
    #define PIN_23  _RB2
    #define SETUP_PIN_23()  {_PCFG4 = 1; _TRISB2 = 1;}
#elif PIN_23_CONFIG == OUT
    #undef PIN_23
    #define PIN_23  _LATB2
    #define SETUP_PIN_23()  {_PCFG4 = 1; _TRISB2 = 0;}
#else
    #error "PIN 23 not configured"
#endif
// PIN 24
#if PIN_24_CONFIG == AN
    #undef PIN_24
    #define PIN_24  ( readADC(5) )          // AN5
    #define SETUP_PIN_24()  {_PCFG5 = 0;}   
#elif PIN_24_CONFIG == IN
    #undef PIN_24
    #define PIN_24  _RB3
    #define SETUP_PIN_24()  {_PCFG5 = 1; _TRISB3 = 1;}
#elif PIN_24_CONFIG == OUT
    #undef PIN_24
    #define PIN_24  _LATB3
    #define SETUP_PIN_24()  {_PCFG5 = 1; _TRISB3 = 0;}
#else
    #error "PIN 24 not configured"
#endif
// PIN 25
#if PIN_25_CONFIG == AN
    #undef PIN_25
    #define PIN_25  ( readADC(6) )          // AN6
    #define SETUP_PIN_25()  {_PCFG6 = 0;}   
#elif PIN_25_CONFIG == IN
    #undef PIN_25
    #define PIN_25  _RC0
    #define SETUP_PIN_25()  {_PCFG6 = 1; _TRISC0 = 1;}
#elif PIN_25_CONFIG == OUT
    #undef PIN_25
    #define PIN_25  _LATC0
    #define SETUP_PIN_25()  {_PCFG6 = 1; _TRISC0 = 0;}
#else
    #error "PIN 25 not configured"
#endif
// PIN 26
#if PIN_26_CONFIG == AN
    #undef PIN_26
    #define PIN_26  ( readADC(7) )          // AN7
    #define SETUP_PIN_26()  {_PCFG7 = 0;}   
#elif PIN_26_CONFIG == IN
    #undef PIN_26
    #define PIN_26  _RC1
    #define SETUP_PIN_26()  {_PCFG7 = 1; _TRISC1 = 1;}
#elif PIN_26_CONFIG == OUT
    #undef PIN_26
    #define PIN_26  _LATC1
    #define SETUP_PIN_26()  {_PCFG7 = 1; _TRISC1 = 0;}
#else
    #error "PIN 26 not configured"
#endif
// End gestion configuration des pins



/* Prototypes des fonctions */

void setup(void);

#endif	/* PILOT_HARDWARE_SETUP_H */

