#include "../random.h"

int main(){
    int num_rand = 20000; //define number of pseudo-random numbers to generate
    double number; //create variable to store a random number
    FILE *file = fopen("data/random_gaussian_out.dat", "w"); //create output file for random numbers
    
    //for loop to generate num_rand number of pseudo-random numbers
    for(int i=0; i<num_rand; i++){
        //generate pseudo-random number
        number = generateNextGaussian();
        //write numbers to file
        fprintf(file, "%f\n", number); 
    }
    
    fclose(file);
    return 0;
}