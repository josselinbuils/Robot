#include <math.h>
#include <stdlib.h>
#include "controllers.h"
#include "moves.h"
#include "odometry.h"
#include "pilot hardware setup.h"
#include "robot.h"

extern PID distController;
extern PID orientController;
extern Odometry odometrie;
extern Robot robot;

Moves moves;

// Initialise la gestion des moves
void initMoves() {
    moves.currentAction = ARRET;
    moves.maxSpeedCoef = 0.0;
    moves.distanceOrder_steps = robot.dist_steps;
    moves.orientOrder_steps = robot.orient_steps;
    moves.accelDistance_steps = 0;
    moves.startDistance_steps = 0;
}

// Effectue une translation du robot
void moveForward(int dDistObj_mm, double acc_ms2) { // Accélération en m/s2

    moves.startDistance_steps = robot.dist_steps;

    /* Calcul de la distance d'accélération */

    double acc_stepsT2 = acc_ms2 * 1000.0 * odometrie.COEF_DIST_PAS_PAR_MM / pow(F_INTERRUPTION_HZ, 2.0); // Conversion de l'accélération en unité robot (pas/période2)

    double vitesseMax_stepsT = VITESSE_MAX_M_PAR_S * 1000.0 * odometrie.COEF_DIST_PAS_PAR_MM / F_INTERRUPTION_HZ; // Conversion de la vitesse max du robot en unité robot (pas/période)

    moves.accelDistance_steps = pow(vitesseMax_stepsT, 2.0) / (2.0 * acc_stepsT2);

    // Pour aller droit
    distController.coefBoost = 1.0;
    orientController.coefBoost = 2.0;

    // Vitesse max à 100%
    moves.maxSpeedCoef = 1.0;
    moves.maxMotorCommand = COMMANDE_MAX_MOTEURS * moves.maxSpeedCoef;

    // Conversion de l'orientation en pas
    moves.distanceOrder_steps = robot.dist_steps + ((double) dDistObj_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    
    // Pour la gestion des deplacements
    moves.currentAction = TRANSLATION;

    // Met la fonction en pause tant que la translation est en cours
    while (moves.currentAction) {
        displayOdometry();
    }
}

// Fait reculer le robot
void moveBack(int dDistObj_mm, double acc_ms2) {
    moveForward(-dDistObj_mm, acc_ms2);
}

// Effectue une rotation du robot
void turn(int dOrientObj_deg) {

    // Pour tourner sur place
    distController.coefBoost = 2.0;
    orientController.coefBoost = 1.0;

    // Vitesse max reduite à 50%
    moves.maxSpeedCoef = 0.5;
    moves.maxMotorCommand = COMMANDE_MAX_MOTEURS * moves.maxSpeedCoef;

    // Conversion de l'orientation en pas
    moves.orientOrder_steps += ((double) dOrientObj_deg) * odometrie.COEF_ROT_PAS_PAR_DEG;

    // Pour la gestion des moves
    moves.currentAction = ROTATION;

    // Met la fonction en pause tant que la rotation est en cours
    while (moves.currentAction) {
        displayOdometry();
    }
}

// Se déplace vers un objectif de position et d'orientation
void move(int xObj_mm, int yObj_mm, int orientObj_deg, double acc_ms2) {

    long xObj_steps = ((double) xObj_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    long yObj_steps = ((double) yObj_mm) * odometrie.COEF_DIST_PAS_PAR_MM;

    long dx_steps = xObj_steps - robot.x_steps;
    long dy_steps = yObj_steps - robot.y_steps;

    // Changement de repère vers repère robot
    double dOrientRobot_rad = ((double) (robot.orient_steps - robot.orientInit_steps)) / odometrie.COEF_ROT_PAS_PAR_RAD;
    long xObjRobot_steps = ((double) dx_steps) * cos(dOrientRobot_rad) + ((double) dy_steps) * sin(dOrientRobot_rad);
    long yObjRobot_steps = ((double) dy_steps) * cos(dOrientRobot_rad) - ((double) dx_steps) * sin(dOrientRobot_rad);

    /* Corrige son orientation pour s'orienter vers la cible */

    turn(atan(((double) xObjRobot_steps) / (yObjRobot_steps != 0 ? ((double) yObjRobot_steps) : 1.0)) * odometrie.COEF_ROT_PAS_PAR_RAD / odometrie.COEF_ROT_PAS_PAR_DEG);

    /* Se dirige vers la position désirée (x et y) */

    long dDist_mm = sqrt(pow((double) dx_steps, 2.0) + pow((double) dy_steps, 2.0)) / odometrie.COEF_DIST_PAS_PAR_MM;

    if (yObjRobot_steps > 0) {
        moveForward(dDist_mm, acc_ms2);
    } else {
        moveBack(dDist_mm, acc_ms2);
    }

    /* Corrige son orientation pour attendre l'orientation désirée */

    turn(-(fmod((double) robot.orient_steps, 360.0 * odometrie.COEF_ROT_PAS_PAR_DEG) / odometrie.COEF_ROT_PAS_PAR_DEG - orientObj_deg));
}

// Determine si on est arrive et gere les obstacles
void manageMoves() {
    if (moves.currentAction) {

        if (moves.currentAction == TRANSLATION) {
            long distParcourue_steps = labs(robot.dist_steps - moves.startDistance_steps);

            // Acceleration
            if (distParcourue_steps < moves.accelDistance_steps && labs(distController.error_steps) > moves.accelDistance_steps) {
                moves.maxMotorCommand = ((double) distParcourue_steps) / ((double) moves.accelDistance_steps) * (COMMANDE_MAX_MOTEURS * moves.maxSpeedCoef - COMMANDE_MIN_MOT_ACC) + COMMANDE_MIN_MOT_ACC;

            // Decelération
            } else if (labs(distController.error_steps) < moves.accelDistance_steps) {
                moves.maxMotorCommand = ((double) labs(distController.error_steps)) / ((double) moves.accelDistance_steps) * (COMMANDE_MAX_MOTEURS * moves.maxSpeedCoef - COMMANDE_MIN_MOT_ACC) + COMMANDE_MIN_MOT_ACC;
            }
        }

        // Arrivée
        if (labs(orientController.error_steps) < (0.5 * odometrie.COEF_ROT_PAS_PAR_DEG) && labs(orientController.dError_steps) < 20 && labs(distController.error_steps) < (20.0 * odometrie.COEF_DIST_PAS_PAR_MM) && labs(distController.dError_steps) < 1000) {
            distController.coefBoost = 1.0;
            orientController.coefBoost = 1.0;
            moves.maxMotorCommand = COMMANDE_MAX_MOTEURS;
            moves.currentAction = ARRET;
        }
    }
}