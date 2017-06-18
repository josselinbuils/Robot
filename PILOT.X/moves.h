#ifndef MOVES_H
#define	MOVES_H

#define ARRET 0
#define ROTATION 1
#define TRANSLATION 2

typedef struct Moves Moves;

struct Moves {
    short currentAction;
    long distanceOrder_steps;
    long orientOrder_steps;

    double maxSpeedCoef; // 0 -> 1
    int maxMotorCommand; // Nécessaire pour gérer les phases d'accélération et de décélération (trapèzes)

    long accelDistance_steps; // Distance pour atteindre la vitesse max lors de l'accélération et une vitesse nulle lors de la décélération (pas)
    long startDistance_steps;
};

void initMoves();
void moveForward(int, double);
void moveBack(int, double);
void turn(int);
void move(int, int, int, double);
void manageMoves();

#endif