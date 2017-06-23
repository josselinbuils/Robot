#include "controllers.h"
#include "moves.h"
#include "odometry.h"
#include "setup.h"
#include "robot.h"

#define RED 0
#define YELLOW 1

Robot robot;

int main(void) {

    // Initialize PILOT
    setup();

    // Initialize robot variables to avoid issues
    robot.x_mm = 0;
    robot.x_steps = 0;
    robot.y_mm = 0;
    robot.y_steps = 0;
    robot.ancDist_steps = 0;
    robot.dist_steps = 0;
    robot.orientInit_steps = 0;
    robot.ancOrient_steps = 0;
    robot.orient_steps = 0;
    robot.orient_deg = 0;

    // Turn on PILOT LED during 100ms
    LED_ON;
    delay_ms(100);
    LED_OFF;

    LCD_texte("Wait for COPILOT", 1, 1);
    LCD_texte("Team:", 3, 1);

    // Wait for start command from COPILOT
    while (!START_PILOT) {
        // Use SELECT switch to choose team
        if (TEAM == YELLOW) {
            LCD_texte("Yellow", 3, 16);
        } else {
            LCD_texte("Red", 3, 16);
        }
    }

    initOdometry(0, 0, 90);

    // Initialize moves management /!\ Have to be done after odometry initialization
    initMoves();

    // Initialize PID controllers
    initControllers(0.4, 3.0, 0.35, 5.0); // kp distance, kd distance, kp orientation, kd orientation

    // Enable main interruption timer /!\ Have to be done after odometry initialization
    T2CONbits.TON = 1;

    moveForward(500, 2.0);
    turn(90);
    moveForward(500, 2.0);
    turn(90);
    moveForward(500, 2.0);
    turn(90);
    moveForward(500, 2.0);
    turn(90);

    while (1) {
        displayOdometry();
    }

    return 0;
}

// Main interruption: 200Hz
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {

    if (START_PILOT) {
        // Erase TIMER2 register
        TMR2 = 0x00;

        getEncodersValues();
        computeRobotPosition();
        applyControllers();
        manageMoves();

        // Clear interruption flag
        IFS0bits.T2IF = 0;

    } else {
        // Stop motors
        BRAKE_M1;
        BRAKE_M2;

        // Clear interruption flag
        IFS0bits.T2IF = 0;

        // Stop main interruption timer
        T2CONbits.TON = 0;
    }
}