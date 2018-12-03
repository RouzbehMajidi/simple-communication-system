#include <signal.h>

#include "../lpf.h"
#include "../random.h"
#include "../utils.h"

const int MAX_NUMBER_OF_SYMBOLS = 1000; //maximum number of symbols to generate
const int SAMPLES_PER_SYMBOL = 10; //samples per symbol

double NOISE_POWER = 0; //noise power relative to signal power (set to zero for no noise)

const double T_SYMBOL = 0.01; //symbol period in seconds
const double TIME_STEP = 0.0005; //time step to simulate continuous time

static volatile int isRunning = 1; //used to allow keyboard intercept to stop the board at will

void keyBoardIntercept(int value) { //if key press detected during runtime
    isRunning = 0; //stop the program
}

int main(void) {
    signal(SIGINT, keyBoardIntercept); //listen for key press

    //create files to store tx signal, rx signal, and lpf rx signal
    FILE *transmittedSymbolOutput = fopen("data/Task7/transmitted_signal_output_no_noise.dat", "w");
    FILE *receivedSignalOutput = fopen("data/Task7/received_signal_output_no_noise.dat", "w");
    FILE *filteredSignalOutput = fopen("data/Task7/filtered_signal_output_no_noise.dat", "w");

    //check if any of the files were not created successfully
    if (transmittedSymbolOutput == NULL || 
        receivedSignalOutput == NULL || 
        filteredSignalOutput == NULL) {

        printf("Error opening file!\n"); //print error
        return 1;
    }

    //adjust noise power based on symbol period and sampling rate
    NOISE_POWER = (NOISE_POWER * T_SYMBOL)/ SAMPLES_PER_SYMBOL; 

    LPF lpf; //create LPF object
    
    double LPF_F_3DB = 1/T_SYMBOL; //define 3dB cutoff frequency of lpf
    double T_SAMPLE = T_SYMBOL/SAMPLES_PER_SYMBOL; //define sample interval
    double MAX_TIME = T_SYMBOL*MAX_NUMBER_OF_SYMBOLS; //define max time of simulation

    //convert above doubles to longs to prevent overflow in calculations
    long T_SYMBOL_LONG = (long) (T_SYMBOL/TIME_STEP);
    long T_SAMPLE_LONG = (long) (T_SAMPLE/TIME_STEP);
    long MAX_TIME_LONG = (long) (MAX_TIME/TIME_STEP);


    LPF_init(&lpf, LPF_F_3DB, T_SYMBOL, SAMPLES_PER_SYMBOL); //initialize LPF
    LPF_info(&lpf); //print LPF info to console

    //print statements to console about program status and parameters
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
    int errorCount = 0; //error counter
    int symbolCount = 0; //symbol counter
    int sampleCount = 0; //sample counter

    double percentComplete = 0; //percentage of program complete
    

    //Simulation Loop
    while(currentTime < MAX_TIME_LONG && isRunning){
        //calculate and print program progress to console as percent out of 100%
        percentComplete = ((double)(currentTime + 1)/MAX_TIME_LONG)*100;
        printf(BLU "\rSimulation Progress: %0.2lf%%" RESET,percentComplete);
        fflush(stdout);

        //determine whether current value should be sampled
        int isSample = currentTime % T_SAMPLE_LONG == 0;

        //differentiate between symbols
        int isSymbol = currentTime % T_SYMBOL_LONG == 0; 
        int isNextSymbol = (currentTime + 1) % T_SYMBOL_LONG == 0;
        
        if(isSymbol){ //if time to generate new symbol
            symbolCorrelation = 0;
            transmittedSymbol = generateNextSymbol(); //generate random value for symbol
            symbolCount ++; //increment symbol count
        }
        fprintf(transmittedSymbolOutput,"%d\n", transmittedSymbol); //print tx symbol to file

        //Channel Noise (CT) [Channel]
        double noise = generateNextGaussian(0, NOISE_POWER); //generate noise power
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
    printf("\tSNR: %0.2lf dB\n", 10*log10(1/NOISE_POWER));
    printf("\tSymbols generated: %d \n", symbolCount);
    printf("\tNumber of samples: %d \n", sampleCount);

    fclose(transmittedSymbolOutput);
    fclose(receivedSignalOutput);
    fclose(filteredSignalOutput);

    return 0;
}