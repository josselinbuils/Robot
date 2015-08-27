/*
 * Fichier:         lcd.h
 * Description :    Routines pour écran LCD HD44780 en mode 4 bits
 * Projet :         Coupe de France de Robotique 2015
 * Auteur :         Christopher BUREL, Josselin BUILS
 * Version :        20 juillet 2014
 */

#include "lcd.h"

// Affiche un nombre en fin de ligne
void LCD_nombre(int ligne, int value) {

    // Défini le caractère qui sera affiché devant le nombre comme un espace
    int f = 32;

    // Vérifie si c'est un nombre négatif
    if (value < 0) {
        value = -value; // Rend la valeur positive
        f = 45; // Défini le caractère qui sera affiché devant le nombre comme un signe -
    }

    /* Détermine la valeur de chaque caractère pour l'affichage */

    int e = value;
    int d = e / 10;
    int c = d / 10;
    int b = c / 10;
    int a = b / 10;

    a %= 10;
    b %= 10;
    c %= 10;
    d %= 10;
    e %= 10;

    a += 48;
    b += 48;
    c += 48;
    d += 48;
    e += 48;

    // Transforme les caractères vides en espaces
    if (a == 48) {
        a = 32;

        if (b == 48) {
            b = 32;

            if (c == 48) {
                c = 32;

                if (d == 48) {
                    d = 32;
                }
            }
        }
    }

    // Défini la valeur hexadécimale de la ligne
    switch (ligne) {
        case 1:
            ligne = 0x00;
            break;
        case 2:
            ligne = 0x40;
            break;
        case 3:
            ligne = 0x14;
            break;
        case 4:
            ligne = 0x54;
            break;
    }

    /* Affiche les caractères */

    SetDDRamAddr(ligne + (0x0E)); // Défini la position du curseur
    WriteDataLCD(f); // Affiche le caractère
    WriteDataLCD(a); // Affiche le caractère
    WriteDataLCD(b); // Affiche le caractère
    WriteDataLCD(c); // Affiche le caractère
    WriteDataLCD(d); // Affiche le caractère
    WriteDataLCD(e); // Affiche le caractère
}

// Écrit un texte positionné
void LCD_texte(char *texte, char ligne, char curseur)
{
    switch (ligne) {
        case 1:
            ligne = 0x00;
            break;
        case 2:
            ligne = 0x40;
            break;
        case 3:
            ligne = 0x14;
            break;
        case 4:
            ligne = 0x54;
            break;
    }

    SetDDRamAddr(ligne + curseur - 1); // Défini la position du curseur
    
    // Affiche les caractères du texte sur l'écran
    while (*texte) {
        WriteDataLCD(*texte);
        texte++;
    }
}


/********************************************************************
*       Function Name:  setupLCD                                     *
*       Return Value:   void                                         *
*       Parameters:     void                                         *
*       Description:    This routine configures the LCD. Based on    *
*                       the Hitachi HD44780 LCD controller. The      *
*                       routine will configure the I/O pins of the   *
*                       microcontroller, setup the LCD for 4-bit     *
*                       mode and clear the display.
**********************************************************************/
void setupLCD(void)
{
    wait(16000);    // Wait for more than 15 msec after VCC rises to 4.5 V

    // Make port output
    TRIS_LCD_RS  = 0;
    TRIS_LCD_E   = 0;
    TRIS_LCD_D4  = 0;
    TRIS_LCD_D5  = 0;
    TRIS_LCD_D6  = 0;
    TRIS_LCD_D7  = 0;

    LCD_RS = 0;
    LCD_E = 0;

    // write to port
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    enableMemo();

    wait(5000);    // Wait for more than 4.1 msec

    // write to port
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    enableMemo();

    wait(200);    // Wait for more than 100 usec

    // write to port
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    enableMemo();

    wait(200);

    // write to port
    LCD_D4 = 0;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    enableMemo();

    writeCmdLCD(0x28);   // Function set: 4 bit data, L1652
    writeCmdLCD(0x06);   // Entry Mode: Inc 1, no shift
    writeCmdLCD(0x0C);   // Display ON, Cursor off, no blink
    writeCmdLCD(0x01);   // Clear Display
    writeCmdLCD(0x80);   // Set Cursor to top left

    return;
}

/********************************************************************
*       Function Name:  SetDDRamAddr                                *
*       Return Value:   void                                        *
*       Parameters:     CGaddr: display data address                *
*       Description:    This routine sets the display data address  *
*                       of the Hitachi HD44780 LCD controller. The  *
*                       user must check to see if the LCD controller*
*                       is busy before calling this routine.        *
********************************************************************/
void SetDDRamAddr(unsigned char bValue)
{
    unsigned char bTemp;
    bTemp = bValue | 0x80;

    // wait 1milsec for not busy
    wait(1000);

    // clear RS for Instruction
    LCD_RS = 0;

    // write ms nibble to port
    LCD_D4 = (bTemp >> 4 & 0x00000001);
    LCD_D5 = (bTemp >> 4 & 0x00000002) >> 1;
    LCD_D6 = (bTemp >> 4 & 0x00000004) >> 2;
    LCD_D7 = (bTemp >> 4 & 0x00000008) >> 3;

    enableMemo();

    wait(2);

    // write ls nibble to port
    LCD_D4 = (bValue & 0x00000001);
    LCD_D5 = (bValue & 0x00000002) >> 1;
    LCD_D6 = (bValue & 0x00000004) >> 2;
    LCD_D7 = (bValue & 0x00000008) >> 3;

    enableMemo();

    return;
}

/********************************************************************
*       Function Name:  writeCmdLCD                                *
*       Return Value:   void                                        *
*       Parameters:     cmd: command to send to LCD                 *
*       Description:    This routine writes a command to the Hitachi*
*                       HD44780 LCD controller. The user must check *
*                       to see if the LCD controller is busy before *
*                       calling this routine.                       *
********************************************************************/
void writeCmdLCD(unsigned char bValue)
{
    unsigned char bTemp;
    bTemp = bValue;

    // wait 1milsec for not busy
    wait(1000);

    // clear RS for Instruction
    LCD_RS = 0;

    // write ms nibble to port
    LCD_D4 = (bTemp >> 4 & 0x00000001);
    LCD_D5 = (bTemp >> 4 & 0x00000002) >> 1;
    LCD_D6 = (bTemp >> 4 & 0x00000004) >> 2;
    LCD_D7 = (bTemp >> 4 & 0x00000008) >> 3;

    enableMemo();

    wait(2);

    // write ls nibble to port
    LCD_D4 = (bValue & 0x00000001);
    LCD_D5 = (bValue & 0x00000002) >> 1;
    LCD_D6 = (bValue & 0x00000004) >> 2;
    LCD_D7 = (bValue & 0x00000008) >> 3;

    enableMemo();

    return;
}

/********************************************************************
*       Function Name:  WriteDataLCD                               *
*       Return Value:   void                                        *
*       Parameters:     data: data byte to be written to LCD        *
*       Description:    This routine writes a data byte to the      *
*                       Hitachi HD44780 LCD controller. The user    *
*                       must check to see if the LCD controller is  *
*                       busy before calling this routine. The data  *
*                       is written to the character generator RAM or*
*                       the display data RAM depending on what the  *
*                       previous SetxxRamAddr routine was called.   *
********************************************************************/
void WriteDataLCD(unsigned char bValue) {
    unsigned char bTemp;
    bTemp = bValue;

    // wait 1milsec for not busy
    wait(1000);

    // clear RS for Instruction
    LCD_RS = 1;

    // write ms nibble to port
    LCD_D4 = (bTemp >> 4 & 0x00000001);
    LCD_D5 = (bTemp >> 4 & 0x00000002) >> 1;
    LCD_D6 = (bTemp >> 4 & 0x00000004) >> 2;
    LCD_D7 = (bTemp >> 4 & 0x00000008) >> 3;

    enableMemo();

    wait(2);

    // write ls nibble to port
    LCD_D4 = (bValue & 0x00000001);
    LCD_D5 = (bValue & 0x00000002) >> 1;
    LCD_D6 = (bValue & 0x00000004) >> 2;
    LCD_D7 = (bValue & 0x00000008) >> 3;

    enableMemo();

    return;
}

// Wait in usec
void wait(unsigned long int count) {
    count = count * LCD_FCY;    // count = usec
    while(count--);
}

// Memorisation of data in LCD, toggle enable for > 1 usec
void enableMemo(void) {
    LCD_E = 1;
    wait(2);
    LCD_E = 0;
}
