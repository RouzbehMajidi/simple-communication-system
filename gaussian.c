#include "random.h"

int main() {
    FILE *file = fopen("random_out_gaussian.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int i = 0;
    while(i < 20000){
        float number = 0;
        int j = 0;
        while(j < 12){
            number += generateNext();
            j ++;
        }
        fprintf(file,"%f\n", number);
        i ++;
    }

    fclose(file);
    return 0;
}