#include "lpf.h"
#include "random.h"

const int SAMPLES_PER_SYMBOL = 20;
const int NUMBER_OF_SYMBOLS = 100;

const double LPF_F_3DB = 100;

const float NOISE_POWER = 0.10;

double currentSample = 0.0;
double nextSample = 0.0;


int main() {
    FILE *transmittedSignalOutput = fopen("data/task7/transmitted_signal_output.dat", "w");
    FILE *receivedSignalOutput = fopen("data/task7/received_signal_output.dat", "w");
    FILE *filteredSignalOutput = fopen("data/task7/filtered_signal_output.dat", "w");

    if (transmittedSignalOutput == NULL || receivedSignalOutput == NULL || filteredSignalOutput == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    LPF lpf;

    LPF_init(&lpf,LPF_F_3DB,SAMPLES_PER_SYMBOL);

    LPF_info(&lpf);
     
    printf("Simulation Started.\n");
    currentSample = 0.0;
    fprintf(filteredSignalOutput,"%0.10lf\n", currentSample);

    int currentSymbol = 0;
    int k = 0;
    while(currentSymbol < NUMBER_OF_SYMBOLS - 1){
        double value = generateNextSymbol();
        int currentSampleIndex = 0;
        while(currentSampleIndex < SAMPLES_PER_SYMBOL - 1){
            double noise = generateNextGaussian(0, NOISE_POWER);;
            double signal = value + noise;
            
            currentSample = nextSample;
            nextSample = discreteFilter(&lpf, currentSample, signal);

            fprintf(transmittedSignalOutput,"%0d\n", (int) value);
            fprintf(receivedSignalOutput,"%0.10lf\n", signal);
            fprintf(filteredSignalOutput,"%0.10lf\n", nextSample);

            k ++;
            currentSampleIndex ++;
        }
        currentSymbol ++;
    }

    printf("Simulation Complete.\n");
    return 0;
}