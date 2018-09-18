#include <stdio.h>
#include <time.h>

int A = 61;
int B = 0;
int M = 997;
int SEED = 1;

int count = 0;

int generateNext(){
    SEED = (A * SEED + B) % M;
    return SEED;
}

int main() {
    SEED =  -1*time(NULL);

    FILE *file = fopen("random_out.dat", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    while(count < 1000){
        int B = count;
        int number = generateNext();
        printf("%d\n", number);
        fprintf(file,"%d\n", number);
        //getchar(); 
        count ++;
    }

    fclose(file);
    return 0;
    
}


