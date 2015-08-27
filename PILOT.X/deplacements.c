#include <math.h>
#include <stdlib.h>
#include "asservissements.h"
#include "deplacements.h"
#include "odometrie.h"
#include "pilot hardware setup.h"
#include "robot.h"

extern Asservissement asservDist;
extern Asservissement asservOrient;
extern Odometrie odometrie;
extern Robot robot;

Deplacements deplacements;

// Initialise la gestion des deplacements
void initDeplacements() {
    deplacements.actionEnCours = ARRET;
    deplacements.coefVitesseMax = 0.0;
    deplacements.consigneDistance_pas = robot.dist_pas;
    deplacements.consigneOrient_pas = robot.orient_pas;
    deplacements.distAcc_pas = 0;
    deplacements.distDepart_pas = 0;
}

// Effectue une translation du robot
void avancer(int dDistObj_mm, double acc_ms2) { // Accélération en m/s2

    deplacements.distDepart_pas = robot.dist_pas;

    /* Calcul de la distance d'accélération */

    double acc_pasT2 = acc_ms2 * 1000.0 * odometrie.COEF_DIST_PAS_PAR_MM / pow(F_INTERRUPTION_HZ, 2.0); // Conversion de l'accélération en unité robot (pas/période2)

    double vitesseMax_pasT = VITESSE_MAX_M_PAR_S * 1000.0 * odometrie.COEF_DIST_PAS_PAR_MM / F_INTERRUPTION_HZ; // Conversion de la vitesse max du robot en unité robot (pas/période)

    deplacements.distAcc_pas = pow(vitesseMax_pasT, 2.0) / (2.0 * acc_pasT2);

    // Pour aller droit
    asservDist.coefBoost = 1.0;
    asservOrient.coefBoost = 2.0;

    // Vitesse max à 100%
    deplacements.coefVitesseMax = 1.0;
    deplacements.commandeMaxMoteur = COMMANDE_MAX_MOTEURS * deplacements.coefVitesseMax;

    // Conversion de l'orientation en pas
    deplacements.consigneDistance_pas = robot.dist_pas + ((double) dDistObj_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    
    // Pour la gestion des deplacements
    deplacements.actionEnCours = TRANSLATION;

    // Met la fonction en pause tant que la translation est en cours
    while (deplacements.actionEnCours) {
        afficherOdometrie();
    }
}

// Fait reculer le robot
void reculer(int dDistObj_mm, double acc_ms2) {
    avancer(-dDistObj_mm, acc_ms2);
}

// Effectue une rotation du robot
void tourner(int dOrientObj_deg) {

    // Pour tourner sur place
    asservDist.coefBoost = 2.0;
    asservOrient.coefBoost = 1.0;

    // Vitesse max reduite à 50%
    deplacements.coefVitesseMax = 0.5;
    deplacements.commandeMaxMoteur = COMMANDE_MAX_MOTEURS * deplacements.coefVitesseMax;

    // Conversion de l'orientation en pas
    deplacements.consigneOrient_pas += ((double) dOrientObj_deg) * odometrie.COEF_ROT_PAS_PAR_DEG;

    // Pour la gestion des deplacements
    deplacements.actionEnCours = ROTATION;

    // Met la fonction en pause tant que la rotation est en cours
    while (deplacements.actionEnCours) {
        afficherOdometrie();
    }
}

// Se déplace vers un objectif de position et d'orientation
void deplacer(int xObj_mm, int yObj_mm, int orientObj_deg, double acc_ms2) {
    
    long xObj_pas = ((double) xObj_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    long yObj_pas = ((double) yObj_mm) * odometrie.COEF_DIST_PAS_PAR_MM;
    
    long dx_pas = xObj_pas - robot.x_pas;
    long dy_pas = yObj_pas - robot.y_pas;

    // Changement de repère vers repère robot
    double dOrientRobot_rad = ((double) (robot.orient_pas - robot.orientInit_pas)) / odometrie.COEF_ROT_PAS_PAR_RAD;
    long xObjRobot_pas = ((double) dx_pas) * cos(dOrientRobot_rad) + ((double) dy_pas) * sin(dOrientRobot_rad);
    long yObjRobot_pas = ((double) dy_pas) * cos(dOrientRobot_rad) - ((double) dx_pas) * sin(dOrientRobot_rad);

    /* Corrige son orientation pour s'orienter vers la cible */

    tourner(atan(((double) xObjRobot_pas) / (yObjRobot_pas != 0 ? ((double) yObjRobot_pas) : 1.0)) * odometrie.COEF_ROT_PAS_PAR_RAD / odometrie.COEF_ROT_PAS_PAR_DEG);

    /* Se dirige vers la position désirée (x et y) */

    long dDist_mm = sqrt(pow((double) dx_pas, 2.0) + pow((double) dy_pas, 2.0)) / odometrie.COEF_DIST_PAS_PAR_MM;

    if (yObjRobot_pas > 0) {
        avancer(dDist_mm, acc_ms2);
    } else {
        reculer(dDist_mm, acc_ms2);
    }

    /* Corrige son orientation pour attendre l'orientation désirée */

    tourner(-(fmod((double) robot.orient_pas, 360.0 * odometrie.COEF_ROT_PAS_PAR_DEG) / odometrie.COEF_ROT_PAS_PAR_DEG - orientObj_deg));
}

// Determine si on est arrive et gere les obstacles
void gestionDeplacements() {
    if (deplacements.actionEnCours) {

        if (deplacements.actionEnCours == TRANSLATION) {
            long distParcourue_pas = labs(robot.dist_pas - deplacements.distDepart_pas);

            // Accélération
            if (distParcourue_pas < deplacements.distAcc_pas && labs(asservDist.erreur_pas) > deplacements.distAcc_pas) {
                deplacements.commandeMaxMoteur = ((double) distParcourue_pas) / ((double) deplacements.distAcc_pas) * (COMMANDE_MAX_MOTEURS * deplacements.coefVitesseMax - COMMANDE_MIN_MOT_ACC) + COMMANDE_MIN_MOT_ACC;

            // Décélération
            } else if (labs(asservDist.erreur_pas) < deplacements.distAcc_pas) {
                deplacements.commandeMaxMoteur = ((double) labs(asservDist.erreur_pas)) / ((double) deplacements.distAcc_pas) * (COMMANDE_MAX_MOTEURS * deplacements.coefVitesseMax - COMMANDE_MIN_MOT_ACC) + COMMANDE_MIN_MOT_ACC;
            }
        }

        // Arrivée
        if (labs(asservOrient.erreur_pas) < (0.5 * odometrie.COEF_ROT_PAS_PAR_DEG) && labs(asservOrient.derivee_pas) < 20 && labs(asservDist.erreur_pas) < (20.0 * odometrie.COEF_DIST_PAS_PAR_MM) && labs(asservDist.derivee_pas) < 1000) {
            asservDist.coefBoost = 1.0;
            asservOrient.coefBoost = 1.0;
            deplacements.commandeMaxMoteur = COMMANDE_MAX_MOTEURS;
            deplacements.actionEnCours = ARRET;
        }
    }
}