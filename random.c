#include "random.h"

int A = 997;
int B = 0;
int M_int = 2147483647;
float M_float = 2147483647.0F;
int SEED = -1;

int count = 0;

float generateNext(){
    if(SEED == -1){
        SEED =  time(NULL);
    }
    SEED = ((A * SEED + B) % M_int);
    return SEED / M_float;
}

// int main() {
//     FILE *file = fopen("random_out.dat", "w");
//     if (file == NULL)
//     {
//         printf("Error opening file!\n");
//         return 1;
//     }

//     while(count < 10000000){
//         int B = count;
//         float number = generateNext();
//         fprintf(file,"%f\n", number);
//         count ++;
//     }

//     fclose(file);
//     return 0;
// }


