#include <math.h>
#include "deplacements.h"
#include "odometrie.h"
#include "pilot hardware setup.h"
#include "robot.h"

extern Deplacements deplacements;
extern Robot robot;

Odometrie odometrie;

// Initialise l'odométrie
void initOdometrie(long x0_mm, long y0_mm, long orientInit_deg) {

    // Calcul les constantes de conversion
    odometrie.COEF_DIST_PAS_PAR_MM = RESOLUTION_ENCODEURS_PAS * 4.0 / (PI * DIAMETRE_ROUES_CODEUSES_MM);
    odometrie.COEF_ROT_PAS_PAR_RAD = ENTRAXE_CODEUSES_MM * odometrie.COEF_DIST_PAS_PAR_MM;
    odometrie.COEF_ROT_PAS_PAR_DEG = odometrie.COEF_ROT_PAS_PAR_RAD * PI / 180.0;

    // Initialise les variables internes des encodeurs au point milieu pour éviter les problemes de depassement
    POS1CNT = 32768;
    POS2CNT = 32768;

    // Initialise les variables des encodeurs
    odometrie.encodeurGauche_pas = 0;
    odometrie.encodeurDroit_pas = 0;

    // Initialise les variables de position du robot
    robot.x_mm = x0_mm;
    robot.y_mm = y0_mm;
    robot.x_pas = ((double) x0_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    robot.y_pas = ((double) y0_mm) * odometrie.COEF_DIST_PAS_PAR_MM;

    robot.orientInit_pas = ((double) orientInit_deg) * odometrie.COEF_ROT_PAS_PAR_DEG;
    robot.orient_pas = robot.orientInit_pas;
    robot.ancOrient_pas = robot.orientInit_pas;

    LCD_CLEAR;
    LCD_texte("ActionEnCours :", 1, 1);
    LCD_texte("x_mm :", 2, 1);
    LCD_texte("y_mm :", 3, 1);
    LCD_texte("orient_deg :", 4, 1);
}

// Calcul de la position du robot par approximation lin�aire (Odometrie)
void calculPositionRobot(void) {
    int dDist_pas, dx_pas, dy_pas, deltaOrient_pas;
    double orientMoy_rad; // Orientation moyenne du robot entre deux positions (radians)

    // Enregiste l'ancienne distance parcourue (pas)
    robot.ancDist_pas = robot.dist_pas;

    // Calcule la nouvelle distance parcourue (pas)
    robot.dist_pas = (odometrie.encodeurDroit_pas + odometrie.encodeurGauche_pas) / 2;

    // Stockage de l'ancienne orientation dans la variable appropriee (pas)
    robot.ancOrient_pas = robot.orient_pas;

    // Calcule la nouvelle orientation (pas)
    robot.orient_pas = robot.orientInit_pas + odometrie.encodeurDroit_pas - odometrie.encodeurGauche_pas;

    // Calcule l'évolution de l'orientation (pas)
    deltaOrient_pas = robot.orient_pas - robot.ancOrient_pas;

    // Calcule l'orientation moyenne (rad)
    orientMoy_rad = ((double) (robot.ancOrient_pas + robot.orient_pas)) / (2.0 * odometrie.COEF_ROT_PAS_PAR_RAD);

    // Calcule la derivée de la distance parcourue
    dDist_pas = robot.dist_pas - robot.ancDist_pas;

    // Calcule les variations de position
    dx_pas = round(((double) dDist_pas) * cos(orientMoy_rad));
    dy_pas = round(((double) dDist_pas) * sin(orientMoy_rad));

    // Stocke la nouvelle position
    robot.x_pas += dx_pas;
    robot.y_pas += dy_pas;

    // Conversions
    robot.x_mm = ((double) robot.x_pas) / odometrie.COEF_DIST_PAS_PAR_MM;
    robot.y_mm = ((double) robot.y_pas) / odometrie.COEF_DIST_PAS_PAR_MM;
    robot.orient_deg = round(((double) robot.orient_pas) / odometrie.COEF_ROT_PAS_PAR_DEG);
}

// Met à jour les variables des encodeurs
void saisieEncodeurs(void) {
    odometrie.encodeurGauche_pas += (POS1CNT - 32768);
    odometrie.encodeurDroit_pas += (POS2CNT - 32768);

    POS1CNT = 32768;
    POS2CNT = 32768;
}

// Affiche les infos de l'odométrie
void afficherOdometrie(void) {
    LCD_nombre(1, deplacements.actionEnCours);
    LCD_nombre(2, robot.x_mm);
    LCD_nombre(3, robot.y_mm);
    LCD_nombre(4, robot.orient_deg);
}

// Retourne l'arrondi d'un nombre
double round(double x) {
    return (x - ((int) x)) >= 0.5 ? x + 1 : x;
}