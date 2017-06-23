#include "encoders.h"
#include "setup.h"
#include "uart.h"

_FOSCSEL(FNOSC_PRIPLL) // Primary oscillator (XT, HS, EC) w/ PLL
_FOSC(POSCMD_XT) // XT oscillator
_FWDT(FWDTEN_OFF) // Watchdog Timer disabled

void setup(void) {

    /* Fréquence d'entrée : résonateur XT 10 MHz
     * Fréquence des cycles d'instructions (FCY) : 40 MIPS */

    _PLLPRE = 0; // N1 = 2
    _PLLDIV = 32; // M = 32
    _PLLPOST = 0; // N2 = 2

    // Configurable pins
    SETUP_PIN_19();
    SETUP_PIN_20();
    SETUP_PIN_21();
    SETUP_PIN_22();
    SETUP_PIN_23();
    SETUP_PIN_24();
    SETUP_PIN_25();
    SETUP_PIN_26();

    // Synchronisation pins
    SETUP_PIN_9();
    SETUP_PIN_8();
    SETUP_PIN_3();
    SETUP_PIN_2();
    SETUP_PIN_1();
    SETUP_PIN_44();
    SETUP_PIN_43();
    SETUP_PIN_42();

    // LED
    SETUP_LED();

    // SELECT switch
    SETUP_SELECT();

    // PWM
    SETUP_PWM_MODE();
    SETUP_PWM_PERIOD();
    SETUP_PWM_M1();
    SETUP_PWM_M2();
    SETUP_BRAKE();
    SETUP_DUTY_CYCLE();
    SETUP_DEAD_TIME();
    ENABLE_PWM;

    // Main interruption
    T2CONbits.TON = 0; // Disable timer 2
    T2CONbits.TGATE = 0; // Disable GATE
    T2CONbits.TSIDL = 0;
    T2CONbits.TCS = 0; // Use internal clock
    T2CONbits.T32 = 0; // 16 bits mode
    T2CONbits.TCKPS = 0b11; // 1:256
    TMR2 = 0x00; // Clear register
    PR2 = 781; // Set frequency at 200Hz (40000000 / (F * 256))
    IPC1bits.T2IP = 0x01; // Fix priority
    IFS0bits.T2IF = 0; // Clear interruption flag
    IEC0bits.T2IE = 1; // Enable interruption

    setupEncoders();
    setupLCD();
    setupUART();
    ADC_ON();
}