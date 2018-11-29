#include <signal.h>

#include "../lpf.h"
#include "../random.h"
#include "../utils.h"

const int MAX_NUMBER_OF_SYMBOLS = 25;
const int SAMPLES_PER_SYMBOL = 10;

double NOISE_POWER = 0.1;

const double T_SYMBOL = 0.01; //seconds
const double TIME_STEP = 0.0001;

static volatile int isRunning = 1;

void keyBoardIntercept(int value) {
    isRunning = 0;
}

int main(void) {
    signal(SIGINT, keyBoardIntercept);

    FILE *transmittedSymbolOutput = fopen("data/task9/part_a/transmitted_symbol_output.dat", "w");
    FILE *receivedSignalOutput = fopen("data/task9/part_a/received_signal_output.dat", "w");
    FILE *filteredSignalOutput = fopen("data/task9/part_a/filtered_signal_output.dat", "w");

    if (transmittedSymbolOutput == NULL || 
        receivedSignalOutput == NULL || 
        filteredSignalOutput == NULL) {

        printf("Error opening file!\n");
        return 1;
    }

    NOISE_POWER = (NOISE_POWER * T_SYMBOL)/ SAMPLES_PER_SYMBOL;

    LPF lpf;
    
    double LPF_F_3DB = 0.218/T_SYMBOL;
    double T_SAMPLE = T_SYMBOL/SAMPLES_PER_SYMBOL;
    double MAX_TIME = T_SYMBOL*MAX_NUMBER_OF_SYMBOLS;

    long T_SYMBOL_LONG = (long) (T_SYMBOL/TIME_STEP);
    long T_SAMPLE_LONG = (long) (T_SAMPLE/TIME_STEP);
    long MAX_TIME_LONG = (long) (MAX_TIME/TIME_STEP);

    LPF_init(&lpf, LPF_F_3DB, T_SYMBOL, SAMPLES_PER_SYMBOL);
    LPF_info(&lpf);


    printf(MAG "\nSimulation Started.\n" RESET);
    printf("\tTime Step: %0.10e seconds\n",TIME_STEP);
    printf("\tSymbol Period: %0.10e s OR 1 SYMBOL every %ld time step(s)\n",T_SYMBOL,T_SYMBOL_LONG);
    printf("\tSample Period: %0.10e s OR 1 SAMPLE every %ld time step(s)\n",T_SAMPLE, T_SAMPLE_LONG);
    printf("\tMax Time: %lf s OR %ld time step(s)\n\n",MAX_TIME, MAX_TIME_LONG);

    //Simulation time
    long currentTime = 0;

    //Generated Symbol Value
    int transmittedSymbol = 0;

    //LPF State
    double currentSample = 0.0;
    double nextSample = 0.0;

    //Correlator State
    double symbolCorrelation = 0;

    //Digitization
    int receivedSymbol = 0;

    //Counters
    int errorCount = 0;
    int symbolCount = 0;
    int sampleCount = 0;

    double percentComplete = 0;
    

    //Simulation Loop
    while(currentTime < MAX_TIME_LONG && isRunning){
        percentComplete = ((double)(currentTime + 1)/MAX_TIME_LONG)*100;
        printf(BLU "\rSimulation Progress: %0.2lf%%" RESET,percentComplete);
        fflush(stdout);

        int isSample = currentTime % T_SAMPLE_LONG == 0;
        int isSymbol = currentTime % T_SYMBOL_LONG == 0;
        int isNextSymbol = (currentTime + 1) % T_SYMBOL_LONG == 0;
        
        if(isSymbol){
            symbolCorrelation = 0;
            transmittedSymbol = generateNextSymbol();
            symbolCount ++;
        }
        fprintf(transmittedSymbolOutput,"%d\n", transmittedSymbol);

        //Channel Noise (CT) [Channel]
        double noise = generateNextGaussian(0, NOISE_POWER);
        double receivedSignalValue = transmittedSymbol + noise;
        fprintf(receivedSignalOutput, "%0.10lf\n", receivedSignalValue);

        //Low Pass Filter (CT) [Receiver]
        currentSample = nextSample;
        nextSample = discreteFilter(&lpf, currentSample, receivedSignalValue);
        fprintf(filteredSignalOutput, "%0.10lf\n", nextSample/(lpf.LAMBDA_FACTOR));

        currentTime ++;
    }

    if(isRunning){
        printf(GRN "\n\nSimulation Complete.\n" RESET);
    }else{
        printf(YEL "\n\nSimulation Ended.\n" RESET);
    }
    
    printf("\tSample rate: %d samples per symbol \n", SAMPLES_PER_SYMBOL);
    printf("\tNoise power: %0.3lf * signal power ≡ %0.2lf dBW\n", NOISE_POWER, 10*log10(NOISE_POWER));
    printf("\tSNR: %0.2lf dBW\n", 10*log10(1/NOISE_POWER));
    printf("\tSymbols generated: %d \n", symbolCount);
    printf("\tNumber of samples: %d \n", sampleCount);

    fclose(transmittedSymbolOutput);
    fclose(receivedSignalOutput);
    fclose(filteredSignalOutput);

    return 0;
}