#include "lpf.h"
#include "utils.h"

//define alpha constant
const double ALPHA_(double F_3DB) {
    return 2*M_PI*F_3DB;
}

//define lambda constant
const double LAMBDA_(double F_3DB, double T, int N){
    return (2*M_PI*F_3DB*T)/N;
}

//define beta constant
const double BETA_(double F_3DB, double T, int N) {
    return exp(-LAMBDA_(F_3DB,T,N));
}

//define gamma constant
const double GAMMA_(double F_3DB, double T, int N){
    return (4*M_PI*F_3DB*T)/N;
}

//define lambda factor (similar to gamma factor, but in terms of lambda constant)
const double LAMBDA_FACTOR_(double F_3DB, double T, int N){
    double lambda = LAMBDA_(F_3DB,T,N); 
    return  lambda / (1 - exp(-lambda));
}

//define gamma factor
const double GAMMA_FACTOR_(double F_3DB, double T, int N){
    double gamma = GAMMA_(F_3DB,T,N); 
    return  gamma / (1 - exp(-gamma));
}

//construction function definition
int LPF_init(LPF *self, double F_3DB, double T, int N){
    //initialize the values of all variables in the LPF struct
    self->F_3DB = F_3DB;
    self->N = N;

    self->T = T;

    self->ALPHA = ALPHA_(self->F_3DB);
    self->BETA = BETA_(self->F_3DB, self->T, self->N);
    self->LAMBDA = LAMBDA_(self->F_3DB, self->T, self->N);
    self->GAMMA = GAMMA_(self->F_3DB, self->T, self->N);
    
    self->LAMBDA_FACTOR = LAMBDA_FACTOR_(self->F_3DB, self->T, self->N);
    self->GAMMA_FACTOR = GAMMA_FACTOR_(self->F_3DB, self->T, self->N);

    return 0;
}

//print the values of the variables of the LPF struct
int LPF_info(LPF *self){
    printf(MAG "LPF Info\n" RESET);
    printf("\t3dB Frequency : %0.2lf Hz \n", self->F_3DB);
    printf("\tN : %d samples per symbol\n", self->N);
    printf("\tT : %0.3lf symbol period\n\n", self->T);
    printf("\tLambda Factor : %0.10lf\n", self->LAMBDA_FACTOR);
    printf("\tGamma Factor : %0.10lf\n\n", self->GAMMA_FACTOR);
    printf("\tAlpha : %0.10lf\n", self->ALPHA);
    printf("\tBeta : %0.10lf\n", self->BETA);
    printf("\tGamma : %0.10lf\n", self->GAMMA);
    printf("\tLambda : %0.10lf\n", self->LAMBDA);

    return 0;
}

//discrete time representation of the low pass filter
double discreteFilter(LPF *lpf, double y_t0, double x_t0){
    return ((lpf->BETA)*y_t0 + (lpf->LAMBDA)*x_t0);
}

//continuous time representation of the low pass filter
double filterStepResponse(double t,double F_3DB){
    return 1 - exp( -ALPHA_(F_3DB)*t);
}


// int main(){

//     int N = 10; //Samples per symbol
//     int K_CT = N*N; //Number of CT samples
//     int K_DT = K_CT/N; //Number of DT samples
//     int T = K_CT; //symbol period
//     double F_3DB  = 1 / (double) T; //3dB cutoff of low pass filter

//     double continuousResponse[K_CT]; //array to store the continuous time response values
//     double discreteResponse[K_DT + 1]; //array to store the discrete time response values
//     FILE *continuousOutput = fopen("data/Task6/lpf_continuous.dat", "w"); //file to store ct response
//     FILE *discreteOutput = fopen("data/Task6/lpf_discrete.dat", "w"); //file to store dt response
    
//     if (continuousOutput == NULL || discreteOutput == NULL) { //check if files are created properly
//         printf("Error opening file!\n"); //print error if files are NULL
//         return 1;
//     }

//     LPF lpf; //create LPF type
//     LPF_init(&lpf, F_3DB, T, N); //initialize the LPF
//     LPF_info(&lpf); //print LPF info to terminal

//     //print information about the parameters of the low pass filter
//     // printf("Lambda Factor : %0.10lf\n", LAMBDA_FACTOR());
//     // printf("Gamma Factor : %0.10lf\n", GAMMA_FACTOR());
//     // printf("\tAlpha : %0.10lf\n", ALPHA());
//     // printf("\tBeta : %0.10lf\n", BETA());
//     // printf("\tGamma : %0.10lf\n", GAMMA());
//     // printf("\tLambda : %0.10lf\n", LAMBDA());

//     int X = 1; //unit step input for t or n > 0

//     //Continuous Response
//     for(int i = 0; i < K_CT; i ++){ //loop through samples
//         //print ct response to file
//         fprintf(continuousOutput, "%0.6lf\n", filterStepResponse(i, F_3DB));
//     }

//     discreteResponse[0] = 0; //set initial value of dt response to 0

//     //Discrete Response
//     for(int i = 0; i < K_DT; i ++){ //loop through samples
//         //generate dt response
//         discreteResponse[i + 1] = discreteFilter(&lpf, discreteResponse[i], X); 
//     }

//     //Print discrete response
//     for(int i = 0; i < K_DT + 1; i ++){
//         //print dt response to file
//         fprintf(discreteOutput, "%0.6lf\n", discreteResponse[i]);
//     }

//     printf("Simulation Complete\n");

//     //close files
//     fclose(continuousOutput);
//     fclose(discreteOutput);
//     return 0;
// }