/*
 * Fichier:         lcd.h
 * Description :    Routines pour écran LCD HD44780 en mode 4 bits
 * Projet :         Robot Development Board 2013 (version 3.4)
 * Auteur :         Christopher BUREL
 * Version :        14 janvier 2013
 */

#ifndef __LCD_H
#define __LCD_H

#include "../Common Files Robot Dev Board/p33FJ128MC804.h"

/* Définition des ports */

#define LCD_RS  _LATA7      // Register select
#define LCD_E   _LATA10     // Enable
#define LCD_D4  _LATA8      // Data
#define LCD_D5  _LATB4
#define LCD_D6  _LATA4
#define LCD_D7  _LATA9

/* Orientation des ports */

#define TRIS_LCD_RS  _TRISA7
#define TRIS_LCD_E   _TRISA10
#define TRIS_LCD_D4  _TRISA8
#define TRIS_LCD_D5  _TRISB4
#define TRIS_LCD_D6  _TRISA4
#define TRIS_LCD_D7  _TRISA9

#define LCD_FCY  40    // 40 MIPS

/* Macros */
#define LCD_CLEAR   writeCmdLCD(0x01)

/* Display ON/OFF Control defines */

#define LCD_ON      0x0f  // Display on
#define LCD_OFF     0x0b  // Display off
#define CURSOR_ON   0x0f  // Cursor on
#define CURSOR_OFF  0x0d  // Cursor off
#define BLINK_ON    0x0f  // Cursor Blink
#define BLINK_OFF   0x0e  // Cursor No Blink

/* Cursor or Display Shift defines */

#define SHIFT_CUR_LEFT    0x13  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0x17  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0x1b  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0x1f  /* Display shifts to the right */

/* Function Set defines */

#define FOUR_BIT   0x2f  /* 4-bit Interface               */
//#define EIGHT_BIT  0x3f  /* 8-bit Interface               */
#define LINE_5X7   0x33  /* 5x7 characters, single line   */
#define LINE_5X10  0x37  /* 5x10 characters               */
#define LINES_5X7  0x38  /* 5x7 characters, multiple line */

#define putcXLCD WriteDataLCD

/* Prototypes des fonctions */

void setupLCD(void);
void SetCGRamAddr(unsigned char);
void SetDDRamAddr(unsigned char);
unsigned char ReadAddrLCD(void);
void writeCmdLCD(unsigned char);
void WriteDataLCD( unsigned char);
void putsLCD(char *);
void putrsLCD(const unsigned char *);
void wait(unsigned long int count);
void enableMemo(void);
void LCD_texte(char *, char, char);
void LCD_nombre(int ligne, int value);
#endif
