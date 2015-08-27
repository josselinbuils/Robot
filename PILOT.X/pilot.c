#include "asservissements.h"
#include "deplacements.h"
#include "odometrie.h"
#include "pilot hardware setup.h"
#include "robot.h"

#define ROUGE 0
#define JAUNE 1

Robot robot;

int main(void) {

    // Initialise le PILOT
    setup();

    // Initialise toutes les variables du robot pour éviter les problèmes
    robot.x_mm = 0;
    robot.x_pas = 0;
    robot.y_mm = 0;
    robot.y_pas = 0;
    robot.ancDist_pas = 0;
    robot.dist_pas = 0;
    robot.orientInit_pas = 0;
    robot.ancOrient_pas = 0;
    robot.orient_pas = 0;
    robot.orient_deg = 0;

    /* Allume la LED du pilot pendant 100ms */

    LED_ON;
    delay_ms(100);
    LED_OFF;

    /* Attend l'ordre de démarrage du COPILOT */

    LCD_texte("Attente du COPILOT", 1, 1);
    LCD_texte("Equipe :", 3, 1);

    while (!START_PILOT) {
        // Le choix de l'equipe se fait par l'intermediaire du switch SELECT
        if (EQUIPE == JAUNE) {
            LCD_texte("Jaune", 3, 16);
        } else {
            LCD_texte("Rouge", 3, 16);
        }
    }

    // Initialise l'odométrie
    initOdometrie(0, 0, 90);

    // Initialise la gestion des déplacements   /!\ À faire après avoir initialisé l'odométrie
    initDeplacements();

    // Initialise la gestion des asservissements
    initAsservissements(0.4, 3.0, 0.35, 5.0); // Paramètres : kp distance, kd distance, kp orientation, kd orientation

    // Active le timer de l'interruption principale /!\ Doit être effectuee après l'initialisation de l'odometrie!
    T2CONbits.TON = 1;

    /* Déplacements */

    avancer(500, 2.0);
    tourner(90);
    avancer(1000, 2.0);
    tourner(-90);
    avancer(600, 2.0);
    tourner(-90);
    avancer(1000, 2.0);
    tourner(-90);
    avancer(600, 2.0);
    tourner(-90);
    avancer(1000, 2.0);
    tourner(90);
    avancer(600, 2.0);
    tourner(90);
    avancer(1000, 2.0);
    tourner(90);
    avancer(100, 1 .0);

    // Attend
    while (1) {
        afficherOdometrie();
    }

    return 1;
}

// Interruption principale cadencee a 200Hz

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {

    if (START_PILOT) {
        // Efface le registre du TIMER2
        TMR2 = 0x00;

        // Met a jour les variables des encodeurs
        saisieEncodeurs();

        // Odometrie
        calculPositionRobot();

        // Asservit la position du robot (PD)
        asservir();

        // Détecte l'arrivée
        gestionDeplacements();

        // Efface le drapeau de l'interruption
        IFS0bits.T2IF = 0;
    } else {
        // Arrete les moteurs
        MOTEUR_GAUCHE(0);
        MOTEUR_DROIT(0);

        // Efface le drapeau de l'interruption
        IFS0bits.T2IF = 0;

        // Desactive le timer de l'interruption principale
        T2CONbits.TON = 0;
    }
}