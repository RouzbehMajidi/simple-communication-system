#include "../random.h"
#include <time.h>

int main(){
    
    clock_t start, end; //clock values for before and after function call
    double cpu_time = 0; //total time taken by CPU for all function calls
    double cpu_time_sum = 0; //total time taken by CPU for all function calls for the summing case
    double number = 0;
    double sum = 0;

    for(int i=0; i<100000000; i++){ //generate 100 million random numbers
        start = clock(); //record clock tick before function call
        number = generateNextUniform(); //call pseudo-random number generator function
        end = clock(); //record clock tick after function call
        cpu_time += ((double)(end - start))/CLOCKS_PER_SEC; //convert to seconds and add to cpu_time
    }

    printf("%lf", cpu_time); //display total time to console

    for(int i=0; i<100000000; i++){
        start = clock(); //record clock tick before function call
        sum += generateNextUniform(); //call pseudo-random number generator and add value to sum
        end = clock(); //record clock tick after function call
        cpu_time_sum += ((double)(end - start))/CLOCKS_PER_SEC; //convert to sec and add to cpu_time_sum
    }

    double average = sum / 100000000; //find average

    printf("\nAverage: %0.10f\n", average); //print average to console
    printf("%lf", cpu_time_sum); //display total time on console

    return 0;
}