#include <stdio.h>
#include <math.h>

typedef struct LPF {
    double F_3DB;
    int N;
    double T;

    double ALPHA;
    double BETA;
    double GAMMA;
    double LAMBDA;

    double LAMBDA_FACTOR;
    double GAMMA_FACTOR;
} LPF;

int LPF_init(LPF *self, double F_3DB, int N);

double discreteFilter(LPF *lpf, double y_t0, double x_t0);