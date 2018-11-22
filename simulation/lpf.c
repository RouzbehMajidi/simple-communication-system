#include "random.h"
#include <stdio.h>
#include <math.h>

const int N = 10; //Samples per symbol
const int K = 100; //Number of discrete samples
const int T = 100;
const double F_3DB  = 1/ (double) T; //3dB cutoff of low pass filter

double continuousResponse[K];
double discreteResponse[K];

const double ALPHA() {
    return 2*M_PI*F_3DB;
}

const double LAMBDA(){
    return (2*M_PI*F_3DB*T)/N;
}

const double BETA() {
    return exp(-LAMBDA());
}

const double GAMMA(){
    return (4*M_PI*F_3DB*T)/N;
}

const double GAMMA_FACTOR(){
    double gamma = GAMMA(); 
    return  gamma / (1 - exp(-gamma));
}

double filterStepResponse(double t){
    return 1 - exp( -ALPHA()*t);
}

int main(){
    FILE *continuousOutput = fopen("data/lpf_continuous.dat", "w");
    FILE *discreteOutput = fopen("data/lpf_discrete.dat", "w");
    
    if (continuousOutput == NULL || discreteOutput == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Gamma Factor : %0.10lf\n", GAMMA_FACTOR());

    int X = 1; //Unit step is always 1 for t or n > 0

    //Continuous Response
    for(int i = 0; i < K; i ++){
        fprintf(continuousOutput, "%0.6lf\n", filterStepResponse(i));
    }

    //Discrete Response
    for(int i = 0; i < (K - 1); i ++){
        discreteResponse[i + 1] = BETA()*discreteResponse[i] + LAMBDA()*X;
    }

    for(int i = 0; i < K; i ++){
        fprintf(discreteOutput, "%0.6lf\n", discreteResponse[i]);
    }

    printf("Simulation Complete\n");
    return 0;
}