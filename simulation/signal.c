#include "random.h"

int N = 10;
int M = 100;

float NOISE_POWER = 0.1;

int main() {
    FILE *file = fopen("data/signal.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int m = 0;
    while(m < M){
        float value = generateNextSignal();
        int n = 0;
        while(n < N){
            float noise = (NOISE_POWER/2)*generateNextGaussian();
            float signal = value + noise;
            fprintf(file,"%f\n", signal);
            // fprintf(file, "\t - Signal: %f\n", value);
            // fprintf(file, "\t - Noise: %f\n", noise);
            n ++;
        }
        m ++;
    }

    fclose(file);
    return 0;
}