#include "utils.h"

long round_long(double a) {
    long b = (long) a;

    if (a >= 0) {
       return (a - b) >= 0.5 ? (b + 1) : b;
    } else {
        return (b - a) >= 0.5 ? (b - 1) : b;
    }
}