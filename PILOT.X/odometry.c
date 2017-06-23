#include <math.h>
#include "encoders.h"
#include "moves.h"
#include "odometry.h"
#include "robot.h"
#include "setup.h"
#include "utils.h"

extern Moves moves;
extern Robot robot;

Odometry odometrie;

// Initialise l'odométrie
void initOdometry(long x0_mm, long y0_mm, long orientInit_deg) {

    // Calcul les constantes de conversion
    odometrie.COEF_DIST_PAS_PAR_MM = RESOLUTION_ENCODEURS_PAS * 4.0 / (PI * DIAMETRE_ROUES_CODEUSES_MM);
    odometrie.COEF_ROT_PAS_PAR_RAD = ENTRAXE_CODEUSES_MM * odometrie.COEF_DIST_PAS_PAR_MM;
    odometrie.COEF_ROT_PAS_PAR_DEG = odometrie.COEF_ROT_PAS_PAR_RAD * PI / 180.0;

    // Initialise les variables internes des encodeurs au point milieu pour éviter les problemes de depassement
    POS1CNT = 32768;
    POS2CNT = 32768;

    // Initialise les variables des encodeurs
    odometrie.encodeurGauche_steps = 0;
    odometrie.encodeurDroit_steps = 0;

    // Initialise les variables de position du robot
    robot.x_mm = x0_mm;
    robot.y_mm = y0_mm;
    robot.x_steps = ((double) x0_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    robot.y_steps = ((double) y0_mm) * odometrie.COEF_DIST_PAS_PAR_MM;

    robot.orientInit_steps = ((double) orientInit_deg) * odometrie.COEF_ROT_PAS_PAR_DEG;
    robot.orient_steps = robot.orientInit_steps;
    robot.ancOrient_steps = robot.orientInit_steps;

    LCD_CLEAR;
    LCD_texte("ActionEnCours :", 1, 1);
    LCD_texte("x_mm :", 2, 1);
    LCD_texte("y_mm :", 3, 1);
    LCD_texte("orient_deg :", 4, 1);
}

// Calcul de la position du robot par approximation lin�aire (Odometry)
void computeRobotPosition() {
    long dDist_steps, dx_steps, dy_steps, deltaOrient_steps;
    double orientMoy_rad; // Orientation moyenne du robot entre deux positions (radians)

    // Enregiste l'ancienne distance parcourue (pas)
    robot.ancDist_steps = robot.dist_steps;

    // Calcule la nouvelle distance parcourue (pas)
    robot.dist_steps = (odometrie.encodeurDroit_steps + odometrie.encodeurGauche_steps) / 2;

    // Stockage de l'ancienne orientation dans la variable appropriee (pas)
    robot.ancOrient_steps = robot.orient_steps;

    // Calcule la nouvelle orientation (pas)
    robot.orient_steps = robot.orientInit_steps + odometrie.encodeurDroit_steps - odometrie.encodeurGauche_steps;

    // Calcule l'évolution de l'orientation (pas)
    deltaOrient_steps = robot.orient_steps - robot.ancOrient_steps;

    // Calcule l'orientation moyenne (rad)
    orientMoy_rad = (robot.ancOrient_steps + robot.orient_steps) / (2 * odometrie.COEF_ROT_PAS_PAR_RAD);

    // Calcule la derivée de la distance parcourue
    dDist_steps = robot.dist_steps - robot.ancDist_steps;

    // Calcule les variations de position
    dx_steps = round_long(dDist_steps * cos(orientMoy_rad)); // cos and sin return double
    dy_steps = round_long(dDist_steps * sin(orientMoy_rad));

    // Stocke la nouvelle position
    robot.x_steps += dx_steps;
    robot.y_steps += dy_steps;

    // Conversions
    robot.x_mm = (long) robot.x_steps / odometrie.COEF_DIST_PAS_PAR_MM;
    robot.y_mm = (long) robot.y_steps / odometrie.COEF_DIST_PAS_PAR_MM;
    robot.orient_deg = (int) round_long(robot.orient_steps / odometrie.COEF_ROT_PAS_PAR_DEG);
}

// Met à jour les variables des encodeurs
void getEncodersValues() {
    odometrie.encodeurGauche_steps += getLeftEncoder();
    odometrie.encodeurDroit_steps += getRightEncoder();
}

// Affiche les infos de l'odométrie
void displayOdometry() {
    LCD_nombre(1, moves.currentAction);
    LCD_nombre(2, robot.x_mm);
    LCD_nombre(3, robot.y_mm);
    LCD_nombre(4, robot.orient_deg);
}