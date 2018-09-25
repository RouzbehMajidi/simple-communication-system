#include "random.h"

int N = 10;
int M = 100;

int main() {
    FILE *file = fopen("random_out_signal.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int m = 0;
    while(m < M){
        float number = generateNext();
        int value = (number > 0) ? 1 : -1;
        int n = 0;
        while(n < N){
            fprintf(file,"%d\n", value);
            n ++;
        }
        m ++;
    }

    fclose(file);
    return 0;
}