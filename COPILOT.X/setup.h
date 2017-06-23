#ifndef SETUP_H
#define	SETUP_H

// Include all header files here, just include "copilot hardware setup.h" in other files
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
#define PIN_21  // pins 21 à 26
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
// PIN 21 (/!\ switch ICSP/PIN)
#define COMMANDE_BIDULE             PIN_21
#define PIN_21_CONFIG       AN
// PIN 22 (/!\ switch ICSP/PIN)
#define BUTEE                       PIN_22
#define PIN_22_CONFIG       IN
// PIN 23
#define SHARP_LEFT               PIN_23
#define PIN_23_CONFIG       AN
// PIN 24
#define SHARP_MIDDLE            PIN_24
#define PIN_24_CONFIG       AN
// PIN 25
#define SHARP_RIGHT                  PIN_25
#define PIN_25_CONFIG       AN
// PIN 26
#define SHARP_BACK                PIN_26
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
#define PIN_43  _LATB7    // ordre vers pilot
#undef PIN_42
#define PIN_42  _RB6
#define SETUP_PIN_9()   _TRISB11 = 1
#define SETUP_PIN_8()   _TRISB10 = 1
#define SETUP_PIN_3()   _TRISC7 = 1
#define SETUP_PIN_2()   _TRISC6 = 1
#define SETUP_PIN_1()   _TRISB9 = 1
#define SETUP_PIN_44()  _TRISB8 = 1
#define SETUP_PIN_43()  _TRISB7 = 0     // ordre vers pilot
#define SETUP_PIN_42()  _TRISB6 = 1


/* Définition et orentation des autres ports entrées/sorties */
// LED
#define LED             _LATB5
#define SETUP_LED()     _TRISB5 = 0     // output
#define LED_ON          LED = 1
#define LED_OFF         LED = 0
#define LED_TOGGLE      LED = !LED

// Switch
#define SW1         !_RC3   // Actif à l'état haut
#define SW2         !_RC8   // Actif à l'état haut
#define SW3         !_RC9   // Actif à l'état haut
#define MODE        _RC4
#define START       !_RC5   // Actif à l'état haut
#define SETUP_SW1()       _TRISC3 = 1   // input
#define SETUP_SW2()       _TRISC8 = 1
#define SETUP_SW3()       _TRISC9 = 1
#define SETUP_MODE()      _TRISC4 = 1
#define SETUP_START()     _TRISC5 = 1

// Relay
#define RELAY           _LATB13         // Relais de puissance (moteur et servo)
#define SETUP_RELAY()   _TRISB13 = 0    // output
#define RELAY_OFF       RELAY = 0
#define RELAY_ON        RELAY = 1

// Buzzer
#define BUZZER          _LATB12         // Buzzer + LED rouge
#define SETUP_BUZZER()  _TRISB12 = 0    // output
#define BUZZER_OFF      BUZZER = 0
#define BUZZER_ON       BUZZER = 1

// Mesure tension alimentation
#define SETUP_U_PWR()   _PCFG8 = 0                  // AN8
#define COEF_U_PWR      (0.2516)                      // 25.74[Vmax]/1023 * 10 (pour une lecture à 1 décimale, avec un entier)
#define U_PWR_X10       ( readADC(8)*(COEF_U_PWR) ) // tension d'alimentation x10

// Servo
#define SERVO_1 _LATB14     // output
#define SERVO_2 _LATB15
#define SERVO_3 _LATA0
#define SERVO_4 _LATA1
#define SETUP_SERVO_1()     _TRISB14 = 0
#define SETUP_SERVO_2()     _TRISB15 = 0
#define SETUP_SERVO_3()     _TRISA0 = 0
#define SETUP_SERVO_4()     _TRISA1 = 0

// Ecran LCD : voir lcd.h


/* Gestion de configuration des pins 21 à 26 */
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

void setup(void);

#endif	/* COPILOT_HARDWARE_SETUP_H */
