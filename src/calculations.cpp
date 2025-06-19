#include <raymath.h>

const double beta = 0.3;
const double RMAX = 150;

double calc_r(Vector2 pos1, Vector2 pos2) {
    return Vector2Length(Vector2Subtract(pos2, pos1));
}

double F(double r, double a) {
    if (r < beta) {
        return (r/beta) - 1.0;
    } 
    else if (beta < r && r < 1.0) {
        return a * (1 - (abs((2 * r) - 1) - beta) / (1 - beta));
    }
    else {
        return 0;
    }
}

