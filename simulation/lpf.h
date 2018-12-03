#include <stdio.h>
#include <math.h>

typedef struct LPF {
    double F_3DB; //3dB cutoff frequency of the low pass filter
    int N; //samples per symbol
    double T; //symbol period

    //constants
    double ALPHA; 
    double BETA;
    double GAMMA;
    double LAMBDA;

    double LAMBDA_FACTOR;
    double GAMMA_FACTOR;
} LPF;

//function to initialize the low pass filter
int LPF_init(LPF *self, double F_3DB, double T, int N);
//function that returns values of the variables in the LPF struct
int LPF_info(LPF *self);

//discrete time representation of the low pass filter
double discreteFilter(LPF *lpf, double y_t0, double x_t0);

//continuous time representation of the low pass filter
double filterStepResponse(double t,double F_3DB);

