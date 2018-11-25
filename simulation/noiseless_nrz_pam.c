#include "random.h"

int N[2] = {10, 20}; //number of samples per symbol period
int M_sym = 100; //number of symbol periods

int main() {
    double value; //double to store NRZ PAM bit

    FILE *file1 = fopen("data/NRZ_PAM_no_noise_10.dat", "w"); //open data file to save data for N=10
    FILE *file2 = fopen("data/NRZ_PAM_no_noise_20.dat", "w"); //open data file to save data for N=20
    if (file1 == NULL || file2 == NULL) { //if file cannot be created
        printf("Error opening file!\n"); //print an error
        return 1;
    }
    //N=10
    for (int m=0; m<M_sym; m++){ //loop over the symbol periods
        value = generateNextSymbol(); //generate a NRZ PAM bit (1 or -1) for each symbol period
        for(int n=0; n<N[0]; n++){ //loop over the samples for each symbol period
            fprintf(file1,"%f\n", value); //save the encoded bit to the file
        }
    }

    //N=20
    for (int m=0; m<M_sym; m++){ //loop over the symbol periods
        value = generateNextSymbol(); //generate a NRZ PAM bit (1 or -1) for each symbol period
        for(int n=0; n<N[1]; n++){ //loop over the samples for each symbol period
            fprintf(file2,"%f\n", value); //save the encoded bit to the file
        }

    }

    fclose(file1); //close the first file
    fclose(file2); //close the second file
    return 0;
}