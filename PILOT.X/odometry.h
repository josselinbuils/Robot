#ifndef ODOMETRIE_H
#define	ODOMETRIE_H

typedef struct Odometry Odometry;

struct Odometry {
    // Coefficients de conversion
    double COEF_DIST_PAS_PAR_MM; // Coefficient de conversion de nombre de pas en distance (pas/mm)
    double COEF_ROT_PAS_PAR_RAD; // Coefficient de conversion de nombre de pas en radians (pas/rad)
    double COEF_ROT_PAS_PAR_DEG; // Coefficient de conversion de nombre de pas en degres (pas/degres)

    // Variables des encodeurs (pas)
    long encodeurGauche_steps;
    long encodeurDroit_steps;
};

void initOdometry(long, long, long);
void computeRobotPosition();
void getEncodersValues();
void displayOdometry();

#endif