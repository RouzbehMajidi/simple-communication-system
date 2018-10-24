#include "../random.h"

int main(){
    FILE *inputFile= fopen("data/random_out.dat", "r"); //open data file containing uniform random numbers
    FILE *outputFile = fopen("data/autocovariance.dat", "w"); //create output file for autocovariances

    int N = 10000; //number of random numbers
    double numbers[N]; //create storage array of length 10000 for random numbers
    double x = 0; //create and initialize variable to store sample average

     //loop through numbers array
    for(int i=0; i<N; i++){
        fscanf(inputFile, "%lf\n", &numbers[i]); 
        //sum up the numbers array
        x+=numbers[i]; 
    }

    //divide x by length of numbers array
    x/=N; 
    
    //loop through 100 values of m
    for(int m=0; m<100; m++){ 
        //create variable to store the autocovariance
        double autocovariance = 0; 

        //loop through sequence of consecutive pseudo-random numbers
        for(int i=0; i<(N-m); i++){
            //calculate sum of consecutive sequence
            autocovariance += (numbers[i]-x)*(numbers[i+m]-x);
        }

        //finish autocovariance calculation
        autocovariance /= (double)(N - m - 1);

        //write autocovariance to file 
        fprintf(outputFile, "%f\n", autocovariance);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}