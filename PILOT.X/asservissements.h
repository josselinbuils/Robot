/* 
 * File:   asservissements.h
 * Author: josselinbuils
 *
 * Created on 14 juin 2015, 15:23
 */

#ifndef ASSERVISSEMENTS_H
#define	ASSERVISSEMENTS_H

typedef struct Asservissement Asservissement;

struct Asservissement {
    // Coefficients de l'asservissement
    double KP; // Coefficient proportionnel : augmente la rapidite et reduit l'erreur statique mais diminue la stabilite
    double KD; // Coefficient derivee : augmente la rapidite et la stabilite

    // Variables de l'asservissement
    long ancErreur_pas;
    long erreur_pas;
    long derivee_pas;
    long commande;
    double coefBoost;
};

// Prototypes des fonctions
void initAsservissements(double, double, double, double);
void asservir();

#endif	/* ASSERVISSEMENTS_H */

