#include "random.h"
#include <stdlib.h>

double * read_file(int N, FILE *file){ //function to read numbers from .dat file
    double *numbers = malloc(sizeof(double)*N); //create storage array of length 10000 for random numbers
    for (int i=0; i<N; i++){ //loop 10000 times through file
        fscanf(file, "%lf\n", &numbers[i]); //read the file and store the random number into the array
    }
    return numbers; //return array of 10000 pseudo-random numbers
}

double calc_sample_average(int N, double *numbers){ //function to calculate the sample average
    double x = 0; //create and initialize variable to store sample average
    for(int i=0; i<N; i++){ //loop through numbers array
        x+=numbers[i]; //sum up the numbers array
    }
    return x/N; //divide x by length of numbers array and return
}

double * calc_autocovariance(int N, int x, double *numbers){ //function to calculate the autocovariance
    double *C = malloc(sizeof(double)*100); //create array to store autocovariances
    for(int m=0; m<100; m++){ //loop through 100 values of m
        C[m] = 0; //create variable to store the sum
        for(int i=0; i<(N-m); i++){ //loop through sequence of consecutive pseudo-random numbers
            C[m] += (numbers[i]-x)*(numbers[i+m]-x); //calculate sum of consecutive sequence
        }
        C[m] /= (double)(N - m - 1); //finish autocovariance calculation
    }

    return C; //return all autocovariances
    
}

int main(){
    FILE *file = fopen("random_out.dat", "r"); //open data file containing random numbers

    int N = 10000; //number of random numbers
    double *numbers; //create pointer for numbers

    numbers = read_file(N, file); //read file and store in numbers

    double x = calc_sample_average(N, numbers); //calculate sample average and store in x
    double *C; //create pointer for autocovariances

    C = calc_autocovariance(N, x, numbers); //calculate autocovariances

    FILE *file2 = fopen("autocovariance.dat", "w"); //create output file for autocovariances

    for(int m=0; m<100; m++){
        fprintf(file2, "%f\n", C[m]); //write numbers to file
    }
   
    return 0;
}