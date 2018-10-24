#include "random.h"

int main(){
    FILE *file = fopen("random_Gaussian_out.dat", "r"); //open data file containing random numbers
    int N = 10000; //number of random numbers
    double numbers[N]; //create storage array of length 10000 for random numbers
    for (int i=0; i<N; i++){ //loop 10000 times through file
        fscanf(file, "%lf\n", &numbers[i]); //read the file and store the random number into the array
    }
    double x = 0; //create and initialize variable to store sample average
    for(int i=0; i<N; i++){ //loop through numbers array
        x+=numbers[i]; //sum up the numbers array
    }
    x/=N; //divide x by length of numbers array and return
    double C[100]; //create array to store autocovariances
    for(int m=0; m<100; m++){ //loop through 100 values of m
        C[m] = 0; //create variable to store the sum
        for(int i=0; i<(N-m); i++){ //loop through sequence of consecutive pseudo-random numbers
            C[m] += (numbers[i]-x)*(numbers[i+m]-x); //calculate sum of consecutive sequence
        }
        C[m] /= (double)(N - m - 1); //finish autocovariance calculation
    }
    FILE *file2 = fopen("autocovariance2_Gaussian.dat", "w"); //create output file for autocovariances
    for(int m=0; m<100; m++){
        fprintf(file2, "%f\n", C[m]); //write numbers to file
    }
    
}
