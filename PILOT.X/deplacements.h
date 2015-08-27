#ifndef DEPLACEMENTS_H
#define	DEPLACEMENTS_H

// Pour la comprehension du code
#define ARRET 0
#define ROTATION 1
#define TRANSLATION 2

typedef struct Deplacements Deplacements;

struct Deplacements {
    short actionEnCours;
    long consigneDistance_pas;
    long consigneOrient_pas;

    double coefVitesseMax; // Varie de 0 à 1
    int commandeMaxMoteur; // Nécessaire pour gérer les phases d'accélération et de décélération (trapèzes)

    long distAcc_pas; // Distance pour atteindre la vitesse max lors de l'accélération et une vitesse nulle lors de la décélération (pas)
    long distDepart_pas;
};

// Prototypes des fonctions
void initDeplacements();
void avancer(int, double);
void reculer(int, double);
void tourner(int);
void deplacer(int, int, int, double);
void gestionDeplacements();

#endif