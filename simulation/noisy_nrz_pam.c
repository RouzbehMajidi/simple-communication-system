#include "random.h"

int N[2] = {10, 20}; //number of samples per symbol period
int M_sym = 100; //number of symbol periods

float NOISE_POWER = 0.1; //noise power

int main() {
    double value; //double to store NRZ PAM bit
    double noise; //double to store noise for each encoded bit
    double signal; //double to store the summation of the value and noise

    FILE *file = fopen("../data/NRZ_PAM_with_noise.dat", "w"); //open data file to save data
    if (file == NULL) { //if file cannot be created
        printf("Error opening file!\n"); //print an error
        return 1;
    }
    for (int m=0; m<M; m++){ //loop over the symbol periods
        value = generateNextSignal(); //generate a NRZ PAM bit (1 or -1) for each symbol period
        for(int n=0; n<N; n++){ //loop over the samples for each symbol period
            noise = sqrt(NOISE_POWER/2)*generateNextGaussian(); //generate AWGN with specified noise power 
            signal = value + noise; //add noise to the signal
            fprintf(file,"%f\n", signal); //print the signal to the file
        }
    }

    fclose(file); //close the file
    return 0;
}