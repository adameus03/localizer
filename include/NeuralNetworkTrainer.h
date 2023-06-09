#ifndef NEURALNETWORKTRAINER_H
#define NEURALNETWORKTRAINER_H

#include "NeuralNetwork.h"
#include <iostream> //verbose

typedef unsigned char uchar;

class NeuralNetworkTrainer
{
    public:
        NeuralNetworkTrainer(NeuralNetwork* neural_network, double* inputs, double* outputs, const uint& training_set_size);
        virtual ~NeuralNetworkTrainer();
        void RunTraining(const double& accuracy);

    protected:

    private:
        NeuralNetwork* neural_network = NULL;
        double* inputs = NULL;
        double* outputs = NULL;
        uint training_set_size;
};

#endif // NEURALNETWORKTRAINER_H
