#include "random.h"

int main() {
    FILE *file = fopen("data/noise.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    for(int i = 0; i < 20000; i++){
        double number = generateNextGaussian(0,1);
        fprintf(file,"%lf\n", number);
    }

    fclose(file);
    return 0;
}