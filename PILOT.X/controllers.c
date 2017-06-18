#include <math.h>
#include <stdlib.h>
#include "controllers.h"
#include "moves.h"
#include "odometry.h"
#include "pilot hardware setup.h"
#include "robot.h"

extern Moves moves;
extern Odometry odometrie;
extern Robot robot;

PID distController;
PID orientController;

// Initialise les asservissements
void initControllers(double kpDist, double kdDist, double kpOrient, double kdOrient) {

    // Initialisation de l'asservissement de la distance parcourue
    distController.kp = kpDist;
    distController.kd = kdDist;
    distController.oldError_steps = 0;
    distController.error_steps = 0;
    distController.dError_steps = 0;
    distController.command = 0;
    distController.coefBoost = 0.0;

    // Initialisation de l'asservissement de l'orientation
    orientController.kp = kpOrient;
    orientController.kd = kdOrient;
    orientController.oldError_steps = 0;
    orientController.error_steps = 0;
    orientController.dError_steps = 0;
    orientController.command = 0;
    orientController.coefBoost = 0.0;
}

void applyControllers() {
   
    distController.oldError_steps = distController.error_steps;
    distController.error_steps = moves.distanceOrder_steps - robot.dist_steps; // Distance to travel
    distController.dError_steps = distController.error_steps - distController.oldError_steps;
    distController.command = distController.kp * distController.error_steps + distController.kd * distController.dError_steps;
    distController.command = ((double) distController.command) * distController.coefBoost;

    orientController.oldError_steps = orientController.error_steps;
    orientController.error_steps = moves.orientOrder_steps - robot.orient_steps;
    orientController.dError_steps = orientController.error_steps - orientController.oldError_steps;
    orientController.command = orientController.kp * orientController.error_steps + orientController.kd * orientController.dError_steps;
    orientController.command = ((double) orientController.command) * orientController.coefBoost;

    int maxMotorCommand = moves.maxMotorCommand; // Uniquement pour la visibilité du code

    // Gestion des priorités de mouvement
    if ((abs(distController.command) + abs(orientController.command)) > maxMotorCommand) {

        // Priorité à la rotation durant une translation pour aller droit
        if (moves.currentAction == TRANSLATION) {
            if (distController.command > 0) {
                distController.command = maxMotorCommand - abs(orientController.command);
            } else {
                distController.command = -maxMotorCommand + abs(orientController.command);
            }

        // Priorité à la translation durant une rotation pour tourner sur place
        } else if (moves.currentAction == ROTATION) {
            if (orientController.command > 0) {
                orientController.command = maxMotorCommand - abs(distController.command);
            } else {
                orientController.command = -maxMotorCommand + abs(distController.command);
            }
        }
    }

    // Calcul des nouvelles commands des moteurs
    int leftMotorCommand = distController.command - orientController.command;
    int rightMotorCommand = distController.command + orientController.command;

    /* Correction des commandes des moteurs pour ne pas depasser les valeurs min et max (les moteurs sont commandés entre -2000 et 2000) */

    if (leftMotorCommand < -maxMotorCommand) {
        leftMotorCommand = -maxMotorCommand;
    } else if (leftMotorCommand > maxMotorCommand) {
        leftMotorCommand = maxMotorCommand;
    }

    if (rightMotorCommand < -maxMotorCommand) {
        rightMotorCommand = -maxMotorCommand;
    } else if (rightMotorCommand > maxMotorCommand) {
        rightMotorCommand = maxMotorCommand;
    }

    SETPOINT_M1(leftMotorCommand);
    SETPOINT_M2(rightMotorCommand);
}