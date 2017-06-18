#ifndef PID_H
#define	PID_H

typedef struct PID PID;

struct PID {
    double kp;
    double ki; // Decrease static error but also decrease stability
    double kd; // Increase statility

    // Variables de l'asservissement
    long oldError_steps;
    long error_steps;
    long dError_steps;
    long command;
    double coefBoost;
};

void initControllers(double, double, double, double);
void applyControllers();

#endif

