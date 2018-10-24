#include "random.h"

long A = 23597; //define multiplier
long B = 0; //define increment
long M = 2147483647; //define modulus
long SEED = 111111*8+3; //define initial seed such that its modulo 8 is 3

double generateNextUniform(){ //define uniformly distributed random number generation (between 0 and 1)
    SEED = ((A * SEED + B) % M); //multiplicative congruential formula
    return SEED / (double) M; //return normalized pseudo-random number
}

/* float generateNextGaussian(){
    float value;
    for(int i = 0; i < 12; i++){
        value += generateNextUniform();
        i ++;
    }
    return value;
} */

/* float generateNextSignal(){
    return (generateNextUniform() > 0.0F) ? 1.0F : -1.0F;
} */

/* int main() {
    int count = 0;

    // FILE *file = fopen("random_out.dat", "w");
    // if (file == NULL)
    // {
    //     printf("Error opening file!\n");
    //     return 1;
    // }

    while(count < 100000000){
        float number = generateNextUniform();
        //fprintf(file,"%f\n", number);
        count ++;
    }

    // fclose(file);
    return 0;
} */


