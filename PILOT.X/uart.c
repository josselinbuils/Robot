/**
 * Manages UART communication
 */

#include "setup.h"
#include "uart.h"
#include "utils.h"

#define FCY_HZ 40000000 // FCY_HZ = Fosc / 2
#define BAUDRATE_HZ 115200

/**
 * Set up UART
 */
void setupUART() {

    // Pins configuration
    RPINR18bits.U1RXR = 0x02; // Make Pin RP2 U1RX (Pin 23)
    RPOR1bits.RP3R = 0x03; // Make Pin RP3 U1TX (Pin 24)

    // UART configuration
    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = round_long((double) FCY_HZ / (16 * BAUDRATE_HZ) - 1);

    // Interrupt configuration
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 1; // Enable UART TX interrupt

    // Enable UART
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX

    delay_ms(1);
    U1TXREG = 'c';
}

void __attribute__((__interrupt__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
    U1TXREG = 'h'; // Transmit one character
}