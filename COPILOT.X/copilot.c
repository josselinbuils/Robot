#include "setup.h"

#define MIN(a, b) (a < b ? a : b)
#define RED 0
#define YELLOW 1

int main(void) {
    // Initialise le COPILOT
    setup();


    /* Allume la LED du COPILOT pendant 100ms */

    LED_ON;
    delay_ms(100);
    LED_OFF;

    // Attend le positionnement du bouton de demarrage si pas encore fait
    if (!START) {
        LCD_texte("Demarreur absent", 1, 1);

        while (!START);
    }

    // Attend du désarmement de l'arrêt d'urgence si pas encore fait
    if (U_PWR_X10 < 20) {
        LCD_texte("Arret d'urgence ", 1, 1);

        while (U_PWR_X10 < 20);
    }


    /* Attend l'ordre de démarrage */

    LCD_texte("Attente demarrage", 1, 1);

    // Affiche l'état de charge de la batterie
    if (U_PWR_X10 > 148) { // Charge de 20%
        LCD_texte("%Batterie:", 4, 1);
        LCD_nombre(4, MIN((U_PWR_X10 - 120) / 48 * 100, 100));
    } else {
        LCD_texte("! Batterie faible !", 4, 1);
    }

    while (START);


    /* Démarre le robot */

    // Ordonne au PILOT de démarrer
    START_PILOT = 1;

    LCD_texte("Match en cours...", 1, 1);

    // Active les timers de l'interruption de fin de match
    T2CONbits.TON = 1;

    LCD_texte("Temps restant:", 2, 1);


    /* Effectue les routines durant le match */

    // L'utilisation d'un drapeau évite les conflits d'affichage à la fin du match si la main a été interrompue
    short flag = 1;

    while (1) {
        // Vérifie si le timer de fin de match est toujours actif, donc s'il reste du temps
        if (T2CONbits.TON) {

            // Affiche le temps restant avant la fin du match
            LCD_nombre(2, 90 - (TMR2 + ((unsigned long) TMR3HLD << 16)) / 40000000);

        } else if (flag) {
            LCD_CLEAR;
            LCD_texte("Fin du match", 1, 1);
            flag = 0;
        }
    }

    return 1;
}

// Interruption de fin de match
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void) {

    // Ordonne au PILOT de s'arrêter
    START_PILOT = 0;

    // Efface le drapeau de l'interruption de fin de match
    IFS0bits.T3IF = 0;

    // Desactive les timers de l'interruption de fin de match
    T3CONbits.TON = 0;
    T2CONbits.TON = 0;
}