#ifndef ODOMETRIE_H
#define	ODOMETRIE_H

#define PI 3.141592653

typedef struct Odometrie Odometrie;

struct Odometrie {
    // Coefficients de conversion
    double COEF_DIST_PAS_PAR_MM; // Coefficient de conversion de nombre de pas en distance (pas/mm)
    double COEF_ROT_PAS_PAR_RAD; // Coefficient de conversion de nombre de pas en radians (pas/rad)
    double COEF_ROT_PAS_PAR_DEG; // Coefficient de conversion de nombre de pas en degres (pas/degres)

    // Variables des encodeurs (pas)
    long encodeurGauche_pas;
    long encodeurDroit_pas;
};

// Prototypes des fonctions
void initOdometrie(long, long, long);
void calculPositionRobot(void);
void saisieEncodeurs(void);
void afficherOdometrie(void);
double round(double);

#endif