#ifndef NEURALNETWORKTRAINER_H
#define NEURALNETWORKTRAINER_H

#include "NeuralNetwork.h"
#include <iostream> //verbose
#include <fstream> //save weights
#include <windows.h> //multithreading & colors

typedef unsigned char uchar;
typedef unsigned long long ull;

class NeuralNetworkTrainer
{
    public:
        NeuralNetworkTrainer(NeuralNetwork* neural_network, double* inputs, double* outputs, const uint& training_set_size);
        virtual ~NeuralNetworkTrainer();
        void RunTraining(const double& accuracy);
        void RunMultithreadedTraining(const uchar& num_threads, const double& accuracy);
        void SaveWeights(double* w_buffer);

    protected:

    private:
        NeuralNetwork* neural_network = NULL;
        double* inputs = NULL;
        double* outputs = NULL;
        uint training_set_size;

        double* concurrent_weights_buffer = NULL;
};

#endif // NEURALNETWORKTRAINER_H
