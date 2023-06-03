#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Neuron.h"
#include <cmath>

typedef unsigned int uint;
typedef double (*RealFunction)(double);

/* Buffering system */
class NeuralNetwork
{
    public:
        NeuralNetwork(uint* structure, const uint& num_layers, double (**activation)(double), double (**activationDerivative)(double));
        virtual ~NeuralNetwork();
        void Computation(double* input);
        void Computation(double* input, double* expected_output, const double& adjustment_size);
        void StoreInput(double* input);
        void LoadOutput(double* output);
        //void GetOutput(double* output);
        double Loss(double* expected_output);
        void LossDerivative(double* expected_output, double* gradient);
        void AllocateGradient();
        void DeallocateGradient();
        uint* GetStructure();
        uint GetNumLayers();

    protected:

    private:
        Neuron** neurons;
        uint* structure; // inputs & neural layers
        uint num_layers;
        uint total_num_neurons;
        uint total_num_weights;
        double (**activation)(double);
        double (**activationDerivative)(double);

        uint max_output_width;
        double* workspace = NULL;
        double* grad_buffer = NULL;
};

#endif // NEURALNETWORK_H
