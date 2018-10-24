#include "random.h"

long A = 23597; //define multiplier
long B = 0; //define increment
long M = 2147483647; //define modulus
long SEED = 111111*8+3; //define initial seed such that its modulo 8 is 3

double generateNextUniform(){ //define uniformly distributed random number generation (between 0 and 1)
    SEED = ((A * SEED + B) % M); //multiplicative congruential formula
    return SEED / (double) M; //return normalized pseudo-random number
}

double generateNextGaussian(){ //define normally distributed random number generation
    double value=0; //define variable to store single random number
    for(int i = 0; i < 12; i++){ //for loop to add 12 uniformly distributed random numbers together
        value += generateNextUniform(); //sum up the pseudo-random numbers
    }
    return value-6; //subtract 6 to make mean 0 and return
}

double generateNextSymbol(){
    return (generateNextUniform() > 0.5) ? 1.0 : -1.0;
}

// int main() {
//     int count = 0;
//     double sum = 0;

//     while(count < 100000000){
//         sum += generateNextUniform();
//         count ++;
//     }
//     sum = sum / 100000000;

//     printf("Sum: %0.10f\n", sum);
//     return 0;
// } 


