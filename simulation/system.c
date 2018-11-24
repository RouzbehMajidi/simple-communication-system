#include "lpf.h"
#include "random.h"

const int SAMPLES_PER_SYMBOL = 10;
const int NUMBER_OF_SYMBOLS = 100;

const double LPF_F_3DB = 100;

const float NOISE_POWER = 0.01;

double samples[NUMBER_OF_SYMBOLS*SAMPLES_PER_SYMBOL];

int main() {
    FILE *noisySignalOutput = fopen("data/noisy_signal_output.dat", "w");
    FILE *filteredSignalOutput = fopen("data/filtered_signal_output.dat", "w");

    if (noisySignalOutput == NULL || filteredSignalOutput == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    LPF lpf;

    LPF_init(&lpf,LPF_F_3DB,SAMPLES_PER_SYMBOL);

    LPF_info(&lpf);
     
    printf("Simulation Started.\n");
    samples[0] = 0.0;
    fprintf(filteredSignalOutput,"%0.10lf\n", samples[0]);

    int currentSymbol = 0;
    int k = 0;
    while(currentSymbol < NUMBER_OF_SYMBOLS - 1){
        double value = generateNextSymbol();
        int currentSample = 0;
        while(currentSample < SAMPLES_PER_SYMBOL - 1){
            double noise = NOISE_POWER*generateNextGaussian();
            double signal = value + noise;
            
            samples[k + 1] = discreteFilter(&lpf, samples[k], signal);

            fprintf(noisySignalOutput,"%0.10lf\n", signal);
            fprintf(filteredSignalOutput,"%0.10lf\n", samples[k + 1]/(lpf.LAMBDA_FACTOR));

            k ++;
            currentSample ++;
        }
        currentSymbol ++;
    }

    printf("Simulation Complete.\n");
    return 0;
}