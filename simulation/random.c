#include "random.h"

long A = 23597; //define multiplier
long B = 0; //define increment
long M = 0x7FFFFFFF; //define modulus
long SEED = 111111*8+3; //define initial seed such that its modulo 8 is 3


double generateNextUniform(){ //define uniformly distributed random number generation (between 0 and 1)
    SEED = ((A * SEED + B) & M); //multiplicative congruential formula using bitwise mask
    return SEED / (double) M; //return normalized pseudo-random number
}

//define normally distributed random number generation
double generateNextGaussian(double mean, double variance){
    double value=-6 + mean; //define variable to store single random number and initialize to -6 + mean
    for(int i = 0; i < 12; i++){ //for loop to add 12 uniformly distributed random numbers together
        value += generateNextUniform(); //sum up the pseudo-random numbers
    }
    return value*sqrt(variance); //return value centered at the specified mean with specified variance
}

int generateNextSymbol(){ //define function to generate NRZ PAM signal of pseudo-random values
    return (generateNextUniform() > 0.5) ? 1.0 : -1.0; //encode signal as 1s and -1s
}

// int main() {
//     int count = 0;
//     double sum = 0;
//     int N = 100000000;

//     // FILE *file = fopen("data/random_out.dat", "w");
//     // if (file == NULL) {
//     //     printf("Error opening file!\n");
//     //     return 1;
//     // }

//     while(count < N){
//         double value = generateNextUniform();
//         sum += value;
//         // fprintf(file,"%lf\n",value);
//         count ++;
//     }

//     sum = sum / N;

//     // fclose(file);
//     printf("Sum: %0.10f\n", sum);
//     return 0;
// } 