#include "random.h"

int main() {
    FILE *file = fopen("noise.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    for(int i = 0; i < 20000; i++){
        float number = generateNextGaussian();
        fprintf(file,"%f\n", number);
    }

    fclose(file);
    return 0;
}