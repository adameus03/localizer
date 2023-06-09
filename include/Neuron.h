#ifndef NEURON_H
#define NEURON_H

#include <random>
#include <ctime>
#include <cstring>

typedef unsigned int uint;

/* Buffering unit*/
class Neuron
{
    public:
        Neuron(const uint& num_inputs, const uint& input_width, double (*activation)(double), double (*activationDerivative)(double), const uint& head_index, const uint& output_width);
        virtual ~Neuron();
        void Process();
        void StoreInput(double* buffer);
        void LoadOutput(double* buffer);
        void PutWeights(double* weights);
        void GetWeights(double* weights);
        void AdjustWeights(double* d_weights);
        uint GetNumInputs();

    protected:

    private:
        double* weights;
        uint num_inputs;
        uint input_width;
        void RandomizeWeights();
        double (*activation)(double);
        double (*activationDerivative)(double);
        //double* pSegment
        uint head_index;
        uint output_width;
        double* input_buffer;
        double* output_buffer;
};

#endif // NEURON_H
