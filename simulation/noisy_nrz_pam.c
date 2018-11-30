#include "random.h"
#include "utils.h"

int MAX_NUMBER_OF_SYMBOLS = 250; //number of symbols M
int SAMPLES_PER_SYMBOL[2] = {10, 20}; //sampling rate N

double NOISE_POWER[2] = {0.1, 0.25}; //desired noise power referenced to signal power 

double T_SYMBOL = 0.01; //symbol period in seconds
double TIME_STEP = 0.0001; //time step to simulate continuous time in seconds

int main(void) {

    FILE *file1 = fopen("data/Task5/NRZ_PAM_with_noise_10_0.1.dat", "w"); //open first data file
    FILE *file2 = fopen("data/Task5/NRZ_PAM_with_noise_10_0.25.dat", "w"); //open second data file
    FILE *file3 = fopen("data/Task5/NRZ_PAM_with_noise_20_0.1.dat", "w"); //open third data file
    FILE *file4 = fopen("data/Task5/NRZ_PAM_with_noise_20_0.25.dat", "w"); //open fourth data file

    if (file1 == NULL || file2 == NULL || file3 == NULL || file4 == NULL) { //if files are not created
        printf("Error opening file!\n"); //print error
        return 1;
    }

    double T_SAMPLE[2];
    T_SAMPLE[0] = T_SYMBOL/SAMPLES_PER_SYMBOL[0]; //sample period for N=10
    T_SAMPLE[1] = T_SYMBOL/SAMPLES_PER_SYMBOL[1]; //sample perido for N=20
    double MAX_TIME = T_SYMBOL*MAX_NUMBER_OF_SYMBOLS; //total time of simulation

    //converting doubles to longs for increased range (to prevent overflow)
    long T_SYMBOL_LONG = (long) (T_SYMBOL/TIME_STEP); //symbol period
    long T_SAMPLE_LONG[2]; //sample period
    T_SAMPLE_LONG[0] = (long) (T_SAMPLE[0]/TIME_STEP); //sample period for N=10
    T_SAMPLE_LONG[1] = (long) (T_SAMPLE[1]/TIME_STEP); //sample period of N=20
    long MAX_TIME_LONG = (long) (MAX_TIME/TIME_STEP); //total time of simulation

    //print simulation details to console
    printf(MAG "\nSimulation Started.\n" RESET);
    printf("\tTime Step: %lf\n",TIME_STEP);
    printf("\tSymbol Period: %lf s OR 1 SYMBOL every %ld time step(s)\n",T_SYMBOL,T_SYMBOL_LONG);
    printf("\tMax Time: %lf s OR %ld time step(s)\n\n", MAX_TIME, MAX_TIME_LONG);

    long currentTime = 0;  //current simulation time

    int transmittedSymbol = 0; //Generated Symbol Value

    int receivedSymbol = 0; //received symbol

    int symbolCount = 0; //symbol counter

    double percentComplete = 0; //percentage of completion for simulation

    //Simulation Loop
    while(currentTime < MAX_TIME_LONG){ //loop until maximum simulation time reached
        //simulation progress
        percentComplete = ((double)(currentTime + 1)/MAX_TIME_LONG)*100;
        printf(BLU "\rSimulation Progress: %0.2lf%%" RESET,percentComplete);
        fflush(stdout);

        int isSample[2];
        isSample[0] = currentTime % T_SAMPLE_LONG[0] == 0; //check whether to sample for N=10
        isSample[1] = currentTime % T_SAMPLE_LONG[1] == 0; //check whether to sample for N=20
        int isSymbol = currentTime % T_SYMBOL_LONG == 0; //check if at beginning of symbol period
        int isNextSymbol = (currentTime + 1) % T_SYMBOL_LONG == 0; //check if at beginning of next symbol
        
        if(isSymbol){
            transmittedSymbol = generateNextSymbol(); //generate a symbol (1 or -1)
            symbolCount ++; //increment the symbol count
        }

        //Channel Noise
        double noise[2]; //create array to store noise values
        noise[0] = generateNextGaussian(0, NOISE_POWER[0]); //generate noise with 10% signal power
        noise[1] = generateNextGaussian(0, NOISE_POWER[1]); //generate noise with 25% signal power
        double receivedSignalValue[2]; //create array to store received values
        receivedSignalValue[0] = transmittedSymbol + noise[0]; //add noise (10%) to symbol value
        receivedSignalValue[1] = transmittedSymbol + noise[1]; //add noise (25%) to symbol value
        
        if(isSample[0]){ //if value is sampled
            fprintf(file1, "%0.10lf\n", receivedSignalValue[0]); //store received symbol (10%) in file
            fprintf(file2, "%0.10lf\n", receivedSignalValue[1]); //store received symbol (25%) in file
        }

        if(isSample[1]){ //if value is sampled
            fprintf(file3, "%0.10lf\n", receivedSignalValue[0]); //store received symbol (10%) in file
            fprintf(file4, "%0.10lf\n", receivedSignalValue[1]); //store received symbol (25%) in file
        }


        currentTime ++; //increment current time

    }

    fclose(file1); //close first file
    fclose(file2); //close second file
    fclose(file3); //close third file
    fclose(file4); //close fourth file

    return 0;
}

