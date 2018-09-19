#include <stdio.h>
#include <time.h>

int A = 997;
int B = 0;
int M_int = 2147483647;
float M_float = 2147483647.0F;
int SEED = 1;

int count = 0;

int generateNext(){
    SEED = (A * SEED + B) % M_int;
    return SEED;
}


int main() {
    SEED =  time(NULL);

    FILE *file = fopen("random_out.dat", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    while(count < 1000000){
        int B = count;
        float number = generateNext() / M_float;
        fprintf(file,"%f\n", number);
        //printf("%f\n", number);
        //getchar(); 
        count ++;
    }

    fclose(file);
    return 0;
    
}


