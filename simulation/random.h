#include <stdio.h>
#include <math.h>

//define variables
extern long A;
extern long B;
extern long M;
extern long SEED;

//define functions
double generateNextUniform();
double generateNextGaussian(double mean, double variance);
int generateNextSymbol();