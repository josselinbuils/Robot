#ifndef ROBOT_H
#define	ROBOT_H

// Paramètres du robot
#define DIAMETRE_ROUES_CODEUSES_MM 53.0 // Diamètre des roues codeuses (mm)
#define ENTRAXE_CODEUSES_MM 354.0 // Entraxe entre les roues codeuses (mm)
#define F_INTERRUPTION_HZ 200.0 // Fréquence de l'interruption (Hz)
#define COMMANDE_MAX_MOTEURS 1500.0 // Commande max du moteur 0 -> 2000 (1500 correspond à 12V au niveau des moteurs quand la LiPo 4 cellules est entièrement chargée)
#define COMMANDE_MIN_MOT_ACC 300.0 // Commande min des moteurs pendant les phases d'accélération et de décélération
#define RESOLUTION_ENCODEURS_PAS 2000.0 // Nombre d'impulsions par tour des roues codeuses
#define VITESSE_MAX_M_PAR_S 1.0 // Vitesse max du robot en m/s

typedef struct Robot Robot;

struct Robot {

    // Robot position
    long x_steps;
    long y_steps;
    long x_mm;
    long y_mm;

    // Distance traveled by the robot (pas)
    long dist_steps;
    long ancDist_steps;

    // Robot Orientation
    long orientInit_steps;
    long ancOrient_steps;
    long orient_steps;
    int orient_deg;
};

#endif	/* ROBOT_H */

