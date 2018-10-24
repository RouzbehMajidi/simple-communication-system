#include "random.h"

int main(){
    int num_rand = 20000; //define number of pseudo-random numbers to generate
    double number; //create variable to store a random number
    FILE *file = fopen("random_Gaussian_out.dat", "w"); //create output file for random numbers
    for(int i=0; i<num_rand; i++){ //for loop to generate num_rand number of pseudo-random numbers
        number = generateNextGaussian(); //generate pseudo-random number and store in array
        fprintf(file, "%f\n", number); //write numbers to file
    }
}