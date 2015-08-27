/*
 * Fichier :        pilot hardware setup.c
 * Description :    Definition des ports et initialisation du PILOT
 * Projet :         COupe de France de Robotique 2015
 * Auteurs:         Christopher BUREL, Josselin BUILS
 * Version :        20 juillet 2014
 */

#include "pilot hardware setup.h"

/* Configuration bits */
_FOSCSEL(FNOSC_PRIPLL) // Primary oscillator (XT, HS, EC) w/ PLL
_FOSC(POSCMD_XT) // XT oscillator
_FWDT(FWDTEN_OFF) // Watchdog Timer disabled


// Séquence d'initialisation (Attention à l'ordre d'exécution!)
void setup(void) {
    
    /* Fréquence d'entrée : résonateur XT 10 MHz
     * Fréquence des cycles d'instructions (FCY) : 40 MIPS */

    _PLLPRE = 0; // N1 = 2
    _PLLDIV = 32; // M = 32
    _PLLPOST = 0; // N2 = 2

    /* Setup des pins configurables */

    SETUP_PIN_19();
    SETUP_PIN_20();
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

    // Setup du switch SELECT
    SETUP_SELECT();

    /* Setup du PWM */

    SETUP_PWM_MODE();
    SETUP_PWM_PERIOD();
    SETUP_PWM_M1();
    SETUP_PWM_M2();
    SETUP_BRAKE();
    SETUP_DUTY_CYCLE();
    SETUP_DEAD_TIME();
    ENABLE_PWM;

    /* Setup de l'interruption principale et du timer associé */

    T2CONbits.TON = 0; // Desactive le timer 2
    T2CONbits.TGATE = 0; // Desactive le GATE
    T2CONbits.TSIDL = 0;
    T2CONbits.TCS = 0; // Utilise l'horloge interne
    T2CONbits.T32 = 0; // Sélectionne le mode 16 bits
    T2CONbits.TCKPS = 0b11; // Selectionne l'echelle 1:256
    TMR2 = 0x00; // Efface le registre
    PR2 = 781; // Fixe la frequence a 200Hz ( 40000000 / (F * 256) )
    IPC1bits.T2IP = 0x01; // Fixe la priorite
    IFS0bits.T2IF = 0; // Efface le drapeau de l'interruption
    IEC0bits.T2IE = 1; // Active l'interruption

    /* Setup de l'encodeur QE1 */

    ADPCFG |= 0x0038; // Configure QEI pins as digital inputs

    RPINR14bits.QEA1R = 20; // Pin RP20
    RPINR14bits.QEB1R = 21; // Pin RP21
    QEI1CONbits.QEIM = 0; // Disable QEI Module
    QEI1CONbits.CNTERR = 0; // Clear any count errors
    QEI1CONbits.QEISIDL = 0; // Continue operation during sleep
    QEI1CONbits.SWPAB = 1; // QEA and QEB swapped
    QEI1CONbits.PCDOUT = 0; // Normal I/O pin operation
    DFLT1CONbits.CEID = 1; // Count error interrupts disabled
    DFLT1CONbits.QEOUT = 1; // Digital filters output enabled for QEn pins
    DFLT1CONbits.QECK = 5; // 1:64 clock divide for digital filter for QEn
    POS1CNT = 32768; // Remise du compteur a 0
    MAX1CNT = 65535; // Valeur max
    QEI1CONbits.QEIM = 6; // X4 mode with position counter reset by Index

    /* Setup de l'encodeur QE2 */

    RPINR16bits.QEA2R = 25; // Pin RP25
    RPINR16bits.QEB2R = 24; // Pin RP24
    QEI2CONbits.QEIM = 0; // Disable QEI Module
    QEI2CONbits.CNTERR = 0; // Clear any count errors
    QEI2CONbits.QEISIDL = 0; // Continue operation during sleep
    QEI2CONbits.SWPAB = 0; // QEA and QEB not swapped
    QEI2CONbits.PCDOUT = 0; // Normal I/O pin operation
    DFLT2CONbits.CEID = 1; // Count error interrupts disabled
    DFLT2CONbits.QEOUT = 1; // Digital filters output enabled for QEn pins
    DFLT2CONbits.QECK = 5; // 1:64 clock divide for digital filter for QEn
    POS2CNT = 32768; // Remise du compteur a 0
    MAX2CNT = 65535; // Valeur max
    QEI2CONbits.QEIM = 6; // X4 mode with position counter reset by Index


    // Setup de l'écran
    setupLCD();

    // Setup ADC
    ADC_ON();
}