#include "../random.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int num_rand = 10000; //define number of pseudo-random numbers to generate
    double number; //create variable to store a random number
    FILE *file = fopen("data/random_out.dat", "w"); //create output file to which random numbers are written
    for(int i=0; i<num_rand; i++){ //for loop to generate num_rand number of pseudo-random numbers
        number = generateNextUniform(); //generate pseudo-random number and store in array
        fprintf(file, "%f\n", number); //write numbers to file
    }
}

