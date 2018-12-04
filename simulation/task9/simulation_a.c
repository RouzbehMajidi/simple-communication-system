#include <signal.h>

#include "../lpf.h"
#include "../random.h"
#include "../utils.h"

const int MAX_NUMBER_OF_SYMBOLS = 1000; //Set constant for total number of symbols to simulate runs
const int SAMPLES_PER_SYMBOL = 5; //Set constant for maximum errors to look for per simulation run

double NOISE_POWER = 0.1; //Variable for simulation noise power

const double T_SYMBOL = 0.01; //seconds //Symbol period of signal
const double TIME_STEP = 0.001; //Time step of signal

static volatile int isRunning = 1; //Boolean helper to gracefully stop simulation without loss of results

void keyBoardIntercept(int value) {
    isRunning = 0;
}

int main(void) {
    signal(SIGINT, keyBoardIntercept); //Attach helper function to intercept keyboard interrupts

    //Open output files
    FILE *transmittedSymbolOutput = fopen("data/task9/part_a/transmitted_symbol_output.dat", "w");
    FILE *receivedSignalOutput = fopen("data/task9/part_a/received_signal_output.dat", "w");
    FILE *filteredSignalOutput = fopen("data/task9/part_a/filtered_signal_output.dat", "w");

    //check output files successfully opened
    if (transmittedSymbolOutput == NULL || 
        receivedSignalOutput == NULL || 
        filteredSignalOutput == NULL) {

        printf("Error opening file!\n");
        return 1;
    }

    NOISE_POWER = (NOISE_POWER * T_SYMBOL)/ SAMPLES_PER_SYMBOL; //Adjust noise variance

    LPF lpf; //Initialize pointer to low pass filter
    
    double LPF_F_3DB = 0.218/T_SYMBOL;  //Setup LPF 3dB cutoff frequency
    double T_SAMPLE = T_SYMBOL/SAMPLES_PER_SYMBOL; //Setup sample period
    double MAX_TIME = T_SYMBOL*MAX_NUMBER_OF_SYMBOLS; //Setup max simulation time

    long T_SYMBOL_LONG = (long) (T_SYMBOL/TIME_STEP); //Convert symbol period to long
    long T_SAMPLE_LONG = (long) (T_SAMPLE/TIME_STEP); //Convert sample period to long
    long MAX_TIME_LONG = (long) (MAX_TIME/TIME_STEP); //Convert max time to long

    LPF_init(&lpf, LPF_F_3DB, T_SYMBOL, SAMPLES_PER_SYMBOL); //Initialize LPF
    LPF_info(&lpf); //Print LPF info

    //Print Simulation info
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
        percentComplete = ((double)(currentTime + 1)/MAX_TIME_LONG)*100; //percent complete
        printf(BLU "\rSimulation Progress: %0.2lf%%" RESET,percentComplete);
        fflush(stdout);

        int isSample = currentTime % T_SAMPLE_LONG == 0;  //Determine if current time is a sample
        int isSymbol = currentTime % T_SYMBOL_LONG == 0; //Determine if current time is start of a symbol
        int isNextSymbol = (currentTime + 1) % T_SYMBOL_LONG == 0; //Determine if current time is end of symbol
        
        //Check this is the start of a symbol generate a symbol value
        if(isSymbol){
            symbolCorrelation = 0; //reset correlator
            transmittedSymbol = generateNextSymbol(); //generate next signal
            symbolCount ++; //increase symbol count
        }
        fprintf(transmittedSymbolOutput,"%d\n", transmittedSymbol);

        //Channel Noise (CT) [Channel]
        double noise = generateNextGaussian(0, NOISE_POWER); //Generate next noise value
        double receivedSignalValue = transmittedSymbol + noise; //add noise to signal
        fprintf(receivedSignalOutput, "%0.10lf\n", receivedSignalValue);

        //Low Pass Filter (CT) [Receiver]
        currentSample = nextSample; //update lastsample variable
        nextSample = discreteFilter(&lpf, currentSample, receivedSignalValue); //filter next sample
        fprintf(filteredSignalOutput, "%0.10lf\n", nextSample/(lpf.LAMBDA_FACTOR)); //Print result to output

        currentTime ++; //increment current time
    }

    if(isRunning){
        printf(GRN "\n\nSimulation Complete.\n" RESET);
    }else{
        printf(YEL "\n\nSimulation Ended.\n" RESET);
    }
    
    //Output simulation info
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