#include "random.h"
#include "lpf.h"

const double ALPHA_(double F_3DB) {
    return 2*M_PI*F_3DB;
}

const double LAMBDA_(double F_3DB, double T, int N){
    return (2*M_PI*F_3DB*T)/N;
}

const double BETA_(double F_3DB, double T, int N) {
    return exp(-LAMBDA_(F_3DB,T,N));
}

const double GAMMA_(double F_3DB, double T, int N){
    return (4*M_PI*F_3DB*T)/N;
}

const double LAMBDA_FACTOR_(double F_3DB, double T, int N){
    double lambda = LAMBDA_(F_3DB,T,N); 
    return  lambda / (1 - exp(-lambda));
}

const double GAMMA_FACTOR_(double F_3DB, double T, int N){
    double gamma = GAMMA_(F_3DB,T,N); 
    return  gamma / (1 - exp(-gamma));
}


int LPF_init(LPF *self, double F_3DB, int N){
    self->F_3DB = F_3DB;
    self->N = N;


    self->T = 1/F_3DB;

    self->ALPHA = ALPHA_(self->F_3DB);
    self->BETA = BETA_(self->F_3DB, self->T, self->N);
    self->LAMBDA = LAMBDA_(self->F_3DB, self->T, self->N);
    self->GAMMA = GAMMA_(self->F_3DB, self->T, self->N);
    
    self->LAMBDA_FACTOR = LAMBDA_FACTOR_(self->F_3DB, self->T, self->N);
    self->GAMMA_FACTOR = GAMMA_FACTOR_(self->F_3DB, self->T, self->N);

    return 0;
}

double filterStepResponse(double t,double F_3DB){
    return 1 - exp( -ALPHA_(F_3DB)*t);
}

double discreteFilter(LPF *lpf, double y_t0, double x_t0){
    return ((lpf->BETA)*y_t0 + (lpf->LAMBDA)*x_t0)/(lpf->LAMBDA_FACTOR);
}


// int main(){

    // int N = 10; //Samples per symbol
    // int K_CT = N*N; //Number of CT samples
    // int K_DT = K_CT/N; //Number of DT samples
    // int T = K_CT;
    // double F_3DB  = 1 / (double) T; //3dB cutoff of low pass filter

    // double continuousResponse[K_CT];
    // double discreteResponse[K_DT + 1];
//     FILE *continuousOutput = fopen("data/lpf_continuous.dat", "w");
//     FILE *discreteOutput = fopen("data/lpf_discrete.dat", "w");
    
//     if (continuousOutput == NULL || discreteOutput == NULL) {
//         printf("Error opening file!\n");
//         return 1;
//     }

//     printf("Lambda Factor : %0.10lf\n", LAMBDA_FACTOR());
//     printf("Gamma Factor : %0.10lf\n", GAMMA_FACTOR());
//     printf("\tAlpha : %0.10lf\n", ALPHA());
//     printf("\tBeta : %0.10lf\n", BETA());
//     printf("\tGamma : %0.10lf\n", GAMMA());
//     printf("\tLambda : %0.10lf\n", LAMBDA());

//     int X = 1; //Unit step is always 1 for t or n > 0

//     //Continuous Response
//     for(int i = 0; i < K_CT; i ++){
//         fprintf(continuousOutput, "%0.6lf\n", filterStepResponse(i));
//     }

//     discreteResponse[0] = 0;

//     //Discrete Response
//     for(int i = 0; i < K_DT; i ++){
//         discreteResponse[i + 1] = discreteFilter(discreteResponse[i], X);
//     }

//     for(int i = 0; i < K_DT + 1; i ++){
//         fprintf(discreteOutput, "%0.6lf\n", discreteResponse[i]);
//     }

//     printf("Simulation Complete\n");

//     fclose(continuousOutput);
//     fclose(discreteOutput);
//     return 0;
// }