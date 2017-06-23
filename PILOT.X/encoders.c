#include "encoders.h"
#include "setup.h"

long getLeftEncoder() {
    long res = POS1CNT - 32768;
    POS1CNT = 32768;
    return res;
}

long getRightEncoder() {
    long res = POS2CNT - 32768;
    POS2CNT = 32768;
    return res;
}

void setupEncoders() {

    // QE1 encoder (left)
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

    // QE2 encoder
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
}