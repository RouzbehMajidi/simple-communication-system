#include "../random.h"
#include <time.h>

int main(){
    
    clock_t start, end; //clock values for before and after function call
    double number = 0; //store pseudo-random numbers
    double sum = 0; //store sum of pseudo-random numbers

    start = clock(); //record clock tick before function call
    for(int i=0; i<100000000; i++){ //generate 100 million random numbers
        number = generateNextUniform(); //call pseudo-random number generator function
    }
    end = clock(); //record clock tick after function call
    double cpu_time = ((double)(end - start))/CLOCKS_PER_SEC; // total time take for all calls

    printf("%lf", cpu_time); //display total time to console

    start = clock(); //record clock tick before function call
    for(int i=0; i<100000000; i++){
        sum += generateNextUniform(); //call pseudo-random number generator and add value to sum
    }
    float average = sum / 100000000; //find average
    end = clock(); //record clock tick after function call
    double cpu_time_sum = ((double)(end - start))/CLOCKS_PER_SEC; //total time taken for all calls

    printf("\nAverage: %0.10f\n", average); //print average to console
    printf("%lf", cpu_time_sum); //display total time on console

    return 0;
}
