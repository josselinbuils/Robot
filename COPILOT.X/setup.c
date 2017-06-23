/*
 * File:            copilot hardware setup.c
 * Description :    Définition des ports et initialisation du COPILOT
 * Project :        Coupe de France de Robotique 2015
 * Author:          Christopher BUREL, Josselin BUILS
 * Version :        20 juillet 2014
 */

#include "setup.h"

/* Configuration bits */
_FOSCSEL( FNOSC_PRIPLL )    // Primary oscillator (XT, HS, EC) w/ PLL
_FOSC( POSCMD_XT )          // XT oscillator
_FWDT( FWDTEN_OFF )         // Watchdog Timer disabled


// Séquence d'initialisation (Attention à l'ordre d'exécution!)
void setup(void)
{
    /* Fréquence d'entrée : résonateur XT 10 MHz
     * Fréquence des cycles d'instructions (FCY) : 40 MIPS */

    _PLLPRE = 0;    // N1 = 2
    _PLLDIV = 32;   // M = 32
    _PLLPOST = 0;   // N2 = 2

    /* Setup des pins configurables */

    SETUP_PIN_21();
    SETUP_PIN_22();
    SETUP_PIN_23();
    SETUP_PIN_24();
    SETUP_PIN_25();
    SETUP_PIN_26();

    /* Setup des pins de synchro */

    SETUP_PIN_9();
    SETUP_PIN_8();
    SETUP_PIN_3();
    SETUP_PIN_2();
    SETUP_PIN_1();
    SETUP_PIN_44();
    SETUP_PIN_43();
    SETUP_PIN_42();

    // Setup de la LED
    SETUP_LED();

    /* Setup des switchs */

    SETUP_SW1();
    SETUP_SW2();
    SETUP_SW3();
    SETUP_MODE();

    // Setup du lanceur
    SETUP_START();

    // Setup du relai
    SETUP_RELAY();

    // Setup du buzzer
    SETUP_BUZZER();

    // Setup de la mesure de tension d'alimentation
    SETUP_U_PWR();

    /* Setup des servos */

    SETUP_SERVO_1();
    SETUP_SERVO_2();
    SETUP_SERVO_3();
    SETUP_SERVO_4();

    /* Setup de l'interruption de fin de match et des timers associes
     * Les timers 2 et 3 (16 bits) sont utilisés pour obtenir un timer 32 bits nécessaire pour fixer une période de 90s */

    T3CONbits.TON = 0; // Desactive le timer
    T2CONbits.TON = 0; // Desactive le timer
    T2CONbits.T32 = 1; // Active le mode 32 bits
    T2CONbits.TCS = 0; // Utilise l'horloge interne
    T2CONbits.TGATE = 0; // Desactive le GATE
    T2CONbits.TCKPS = 0b00; // Selectionne l'echelle 1:1
    TMR3 = 0x00; // Efface le registre du timer 3
    TMR2 = 0x00; // Efface le registre du timer 2
    PR3 = 0xD693; // Fixe la periode a 90s (40000000 * T)
    PR2 = 0xA400; // Fixe la periode a 90s (40000000 * T)
    IPC2bits.T3IP = 0x02; // Fixe la priorite
    IFS0bits.T3IF = 0; // Efface le drapeau de l'interruption
    IEC0bits.T3IE = 1; // Active l'interruption

    // Setup de l'écran
    setupLCD();

    // Setup ADC
    ADC_ON();
}