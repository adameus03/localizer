#include <iostream>
#include <NeuralNetwork.h>
#include <NeuralNetworkTrainer.h>

typedef unsigned int uint;
typedef double (*RealFunction)(double);


double relu(double x){
    if(x > 0.5) return (x-0.5);
    else return 0.0;
}

double relu_d(double x){
    if(x > 0.5) return 1.0;
    else return 0.0;
}

int main()
{
    uint* structure = new uint[4]{2, 5, 4, 2};
    uint num_layers = 3;
    double (**activation)(double) = new RealFunction[3]{relu, relu, relu};
    double (**activationDerivative)(double) = new RealFunction[3]{relu_d, relu_d, relu_d};
    NeuralNetwork nn(structure, num_layers, activation, activationDerivative);


    return 0;
}
