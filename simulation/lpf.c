#include "random.h"
#include <stdio.h>
#include <math.h>

double gammaFactor(double f_3dB, int N){
    double gamma = 4*M_PI*f_3dB*N;
    return gamma / (1 - exp(-gamma));
}

int main(){

    printf("%0.10lf\n", gammaFactor(1,10));

    return 0;
}