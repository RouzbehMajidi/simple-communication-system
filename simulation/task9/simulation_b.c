#include <signal.h>

#include "../lpf.h"
#include "../random.h"
#include "../utils.h"

const int MAX_NUMBER_OF_SYMBOLS = 250000;
const int SAMPLES_PER_SYMBOL = 5;

double NOISE_POWER = 10000;
const double MIN_NOISE_POWER = 0.001;
const double SNR_STEP = 2;

const double T_SYMBOL = 0.01; //seconds
const double TIME_STEP = 0.0001;

static volatile int isRunning = 1;

void keyBoardIntercept(int value) {
    isRunning = 0;
}

int main(void) {
    signal(SIGINT, keyBoardIntercept);

    FILE *snrOutput = fopen("data/task9/part_b/SNR_output_5.dat", "w");
    FILE *errorRateOutput = fopen("data/task9/part_b/error_rate_output_5.dat", "w");

    if (snrOutput == NULL || 
        errorRateOutput == NULL) {

        printf("Error opening file!\n");
        return 1;
    }

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

    int runCount = 1;
    while(NOISE_POWER > MIN_NOISE_POWER){
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
            printf(BLU "\rRun: %d - " GRN "Simulation Progress: %0.2lf%%" RESET,runCount, percentComplete);
            fflush(stdout);

            int isSample = currentTime % T_SAMPLE_LONG == 0;
            int isSymbol = currentTime % T_SYMBOL_LONG == 0;
            int isNextSymbol = (currentTime + 1) % T_SYMBOL_LONG == 0;
            
            if(isSymbol){
                symbolCorrelation = 0;
                transmittedSymbol = generateNextSymbol();
                symbolCount ++;
            }

            //Channel Noise (CT) [Channel]
            double noise = generateNextGaussian(0, NOISE_POWER);
            double receivedSignalValue = transmittedSymbol + noise;

            //Low Pass Filter (CT) [Receiver]
            currentSample = nextSample;
            nextSample = discreteFilter(&lpf, currentSample, receivedSignalValue);

            //Correlator (DT) [Receiver - Sample Rate]
            if(isSample){
                symbolCorrelation += nextSample/(lpf.LAMBDA_FACTOR);
                sampleCount ++;
            }

            //Digitization (DT) [Receiver - Symbol Rate]
            if(isNextSymbol){
                receivedSymbol = (symbolCorrelation > 0) ? 1 : -1;
                if(receivedSymbol != transmittedSymbol){
                    errorCount ++;
                }
            }

            currentTime ++;
        }
        fprintf(snrOutput, "%0.4lf\n",SAMPLES_PER_SYMBOL/(NOISE_POWER));
        fprintf(errorRateOutput, "%0.10lf\n",(double) errorCount/symbolCount);

        runCount++;
        NOISE_POWER /= SNR_STEP;
        
    }

    fclose(snrOutput);
    fclose(errorRateOutput);

    return 0;
}