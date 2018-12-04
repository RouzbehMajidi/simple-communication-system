#include <signal.h>

#include "../lpf.h"
#include "../random.h"
#include "../utils.h"

const int MAX_NUMBER_OF_SYMBOLS = 250000; //Set constant for total number of symbols to simulate per simulation runs
const int MAX_ERRORS = 1000; //Set constant for maximum errors to look for per simulation run
const int SAMPLES_PER_SYMBOL = 10; //Set constant for number of samples to take per symbol

double NOISE_POWER = 10000; //Variable for simulation noise power
const double MIN_NOISE_POWER = 0.001; //Minimum simulation noise power to stop at
const double SNR_STEP = 2; //Step to divide noise power by after ever simulation run

const double T_SYMBOL = 0.01; //seconds //Symbol period of signal
const double TIME_STEP = 0.001; //Time step of signal

static volatile int isRunning = 1; //Boolean helper for gracefully stoping simulation without loss of results

//Helper function for interncepting keyboard interrupts
void keyBoardIntercept(int value) {
    isRunning = 0;
}

int main(void) {
    signal(SIGINT, keyBoardIntercept); //Attach helper function to intercept keyboard interrupts

    FILE *output = fopen("data/task8/output.dat", "w");  //Open output file

    //check output file successfully opened
    if (output == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    LPF lpf; //Initialize pointer to low pass filter
    
    double LPF_F_3DB = 1/T_SYMBOL; //Setup LPF 3dB cutoff frequency
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

    int runCount = 1; //set run counter variable 
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

        //Simulation Counters
        int errorCount = 0;
        int symbolCount = 0;
        int sampleCount = 0;

        double percentComplete = 0;

        //Simulation Loop
        while(currentTime < MAX_TIME_LONG && isRunning){

            percentComplete = ((double)(currentTime + 1)/MAX_TIME_LONG)*100; //percent complete

            printf(BLU "\rRun: %d - " GRN "Simulation Progress: %0.2lf%%" RESET,runCount, percentComplete); 
            fflush(stdout);

            int isSample = currentTime % T_SAMPLE_LONG == 0; //Determine if current time is a sample 
            int isSymbol = currentTime % T_SYMBOL_LONG == 0; //Determine if current time is start of a symbol
            int isNextSymbol = (currentTime + 1) % T_SYMBOL_LONG == 0; //Determine if current time is end of symbol
            
            //Check this is the start of a symbol generate a symbol value
            if(isSymbol){
                symbolCorrelation = 0; //reset correlator
                transmittedSymbol = generateNextSymbol(); //generate next signal
                symbolCount ++; //increase symbol count
            }

            //Channel Noise (CT) [Channel]
            double noise = generateNextGaussian(0, NOISE_POWER); //Generate next noise value
            double receivedSignalValue = transmittedSymbol + noise; //add noise to signal

            //Low Pass Filter (CT) [Receiver]
            currentSample = nextSample; //update lastsample variable
            nextSample = discreteFilter(&lpf, currentSample, receivedSignalValue); //filter next sample

            //Correlator (DT) [Receiver - Sample Rate]
            //Check if sample is symbol
            if(isSample){
                symbolCorrelation += nextSample/(lpf.LAMBDA_FACTOR); //Update symbol correlator
                sampleCount ++; //Increase sample count
            }

            //Digitization (DT) [Receiver - Symbol Rate]
            //Check if symbol has ended 
            if(isNextSymbol){
                receivedSymbol = (symbolCorrelation > 0) ? 1 : -1; //Compare correlator with signal levels
                if(receivedSymbol != transmittedSymbol){
                    errorCount ++; //If sent signal does not match received signal increment error count
                }
                //Stop simulation if error count has reached max value
                if(errorCount == MAX_ERRORS){
                    break;
                }
            }
            //Increment current simulation time
            currentTime ++;
        }
        //Print results to file
        fprintf(output, "%0.6lf,",NOISE_POWER);
        fprintf(output, "%0.4lf,",SAMPLES_PER_SYMBOL/(NOISE_POWER));
        fprintf(output, "%d,",errorCount);
        fprintf(output, "%d\n",symbolCount);

        runCount++; //Increment run counter
        NOISE_POWER /= SNR_STEP; //Update noise power
        
    }

    fclose(output); //Close file

    return 0;
}