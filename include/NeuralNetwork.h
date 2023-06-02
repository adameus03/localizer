#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Neuron.h"

typedef unsigned int uint;
typedef double (*RealFunction)(double);

/* Buffering system */
class NeuralNetwork
{
    public:
        NeuralNetwork(uint* structure, const uint& num_layers, double (**activation)(double), double (**activationDerivative)(double));
        virtual ~NeuralNetwork();
        void Computation(double* input);
        void Computation(double* input, double* expected_output);
        void GetOutput(double* output);

    protected:

    private:
        Neuron** neurons;
        uint* structure; // inputs & neural layers
        uint num_layers;
        double (**activation)(double);
        double (**activationDerivative)(double);

};

#endif // NEURALNETWORK_H
