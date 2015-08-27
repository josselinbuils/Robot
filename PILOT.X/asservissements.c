#include <math.h>
#include <stdlib.h>
#include "asservissements.h"
#include "deplacements.h"
#include "odometrie.h"
#include "pilot hardware setup.h"
#include "robot.h"

extern Deplacements deplacements;
extern Odometrie odometrie;
extern Robot robot;

Asservissement asservDist;
Asservissement asservOrient;

// Initialise les asservissements
void initAsservissements(double kpDist, double kdDist, double kpOrient, double kdOrient) {

    // Initialisation de l'asservissement de la distance parcourue
    asservDist.KP = kpDist;
    asservDist.KD = kdDist;
    asservDist.ancErreur_pas = 0;
    asservDist.erreur_pas = 0;
    asservDist.derivee_pas = 0;
    asservDist.commande = 0;
    asservDist.coefBoost = 0.0;

    // Initialisation de l'asservissement de l'orientation
    asservOrient.KP = kpOrient;
    asservOrient.KD = kdOrient;
    asservOrient.ancErreur_pas = 0;
    asservOrient.erreur_pas = 0;
    asservOrient.derivee_pas = 0;
    asservOrient.commande = 0;
    asservOrient.coefBoost = 0.0;
}


// Asservissement de position PD
void asservir() {

    // Stockage des anciennes erreurs dans les variables appropriees
    asservDist.ancErreur_pas = asservDist.erreur_pas;
    asservOrient.ancErreur_pas = asservOrient.erreur_pas;

    // Calcul des erreurs
    asservDist.erreur_pas = deplacements.consigneDistance_pas - robot.dist_pas; // Correspond a la distance a parcourir
    asservOrient.erreur_pas = deplacements.consigneOrient_pas - robot.orient_pas;

    // Derivée des erreurs
    asservDist.derivee_pas = asservDist.erreur_pas - asservDist.ancErreur_pas;
    asservOrient.derivee_pas = asservOrient.erreur_pas - asservOrient.ancErreur_pas;

    // Calcul des nouvelles commandes de distance et de rotation avec la correction PD
    asservDist.commande =  asservDist.erreur_pas * asservDist.KP + asservDist.derivee_pas * asservDist.KD;
    asservOrient.commande =  asservOrient.erreur_pas * asservOrient.KP + asservOrient.derivee_pas * asservOrient.KD;

    asservDist.commande = ((double) asservDist.commande) * asservDist.coefBoost;
    asservOrient.commande = ((double) asservOrient.commande) * asservOrient.coefBoost;

    int commandeMaxMoteur = deplacements.commandeMaxMoteur; // Uniquement pour la visibilité du code

    // Gestion des priorités de mouvement
    if ((abs(asservDist.commande) + abs(asservOrient.commande)) > commandeMaxMoteur) {

        // Priorité à la rotation durant une translation pour aller droit
        if (deplacements.actionEnCours == TRANSLATION) {
            if (asservDist.commande > 0) {
                asservDist.commande = commandeMaxMoteur - abs(asservOrient.commande);
            } else {
                asservDist.commande = -commandeMaxMoteur + abs(asservOrient.commande);
            }

        // Priorité à la translation durant une rotation pour tourner sur place
        } else if (deplacements.actionEnCours == ROTATION) {
            if (asservOrient.commande > 0) {
                asservOrient.commande = commandeMaxMoteur - abs(asservDist.commande);
            } else {
                asservOrient.commande = -commandeMaxMoteur + abs(asservDist.commande);
            }
        }
    }

    // Calcul des nouvelles commandes des moteurs
    int commandeMoteurGauche = asservDist.commande - asservOrient.commande;
    int commandeMoteurDroit = asservDist.commande + asservOrient.commande;

    /* Correction des commandes des moteurs pour ne pas depasser les valeurs min et max (les moteurs sont commandés entre -2000 et 2000) */

    if (commandeMoteurGauche < -commandeMaxMoteur) {
        commandeMoteurGauche = -commandeMaxMoteur;
    } else if (commandeMoteurGauche > commandeMaxMoteur) {
        commandeMoteurGauche = commandeMaxMoteur;
    }

    if (commandeMoteurDroit < -commandeMaxMoteur) {
        commandeMoteurDroit = -commandeMaxMoteur;
    } else if (commandeMoteurDroit > commandeMaxMoteur) {
        commandeMoteurDroit = commandeMaxMoteur;
    }

    // Commande des moteurs
    MOTEUR_GAUCHE(commandeMoteurGauche);
    MOTEUR_DROIT(commandeMoteurDroit);
}