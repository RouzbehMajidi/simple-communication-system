#include "random.h"

int A = 997;
int B = 0;
int M_int = 2147483647;
float M_float = 2147483647.0F;
int SEED = -1;

float generateNextUniform(){
    if(SEED == -1){
        SEED =  time(NULL);
    }
    SEED = ((A * SEED + B) % M_int);
    return SEED / M_float;
}

float generateNextGaussian(){
    float value;
    for(int i = 0; i < 12; i++){
        value += generateNextUniform();
        i ++;
    }
    return value;
}

float generateNextSignal(){
    return (generateNextUniform() > 0.0F) ? 1.0F : -1.0F;
}

int main() {
    int count = 0;

    // FILE *file = fopen("random_out.dat", "w");
    // if (file == NULL)
    // {
    //     printf("Error opening file!\n");
    //     return 1;
    // }

    while(count < 100000000){
        int B = count;
        float number = generateNextUniform();
        //fprintf(file,"%f\n", number);
        count ++;
    }

    // fclose(file);
    return 0;
}


