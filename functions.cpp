#include "functions.h"

double sigmoid(double x){
    return -1+2.0/(1.0+exp(-x));
}

double sigmoid_d(double x){
    double emx = exp(-x);
    double den = 1+emx;
    den *= den;
    return 2.0*emx/den;

}


double relu(double x){
    if(x > 0) return x;
    else return 0.0;
}

double relu_d(double x){
    if(x > 0) return 1.0;
    else return 0.0;
}
