#include <iostream>
#include "NeuralNetwork.h"
#include "NeuralNetworkTrainer.h"
#include "DataSource.h"
#include <sys/stat.h>
#include "functions.h"
#include "Test.h" //testing
#include <cstring> //testing (memset)

typedef unsigned int uint;
typedef unsigned long long ull;
typedef double (*RealFunction)(double);


int main()
{
    /*Test test;
    test.run_tests();
    return 0;*/

    //uint* structure = new uint[4]{2, 5, 4, 2};
    uint* structure = new uint[3]{2, 2, 2};
    uint num_layers = 2;
    //double* weights = new double[38]; // 2*5+5*4+4*2 = 38 //
    double* weights = new double[12];
    //memset(weights, 1, 38*sizeof(double));
    std::fill_n(weights, /*38*/12, 1);
    double (**activation)(double) = new RealFunction[/*3*/2]{relu, relu/*, relu*/};
    double (**activationDerivative)(double) = new RealFunction[/*3*/2]{relu_d, relu_d/*, relu_d*/};
    NeuralNetwork nn(structure, num_layers, activation, activationDerivative);
    nn.PutWeights(weights);

    ull training_set_size = 0;
    /*DataSource ds_in("train_data\\inputs.bin");
    DataSource ds_out("train_data\\outputs.bin");
    double* inputs = ds_in.GetData(training_set_size);
    double* outputs = ds_out.GetData(training_set_size);*/
    training_set_size = 1; //
    double* inputs = new double[2]{1,1}; //
    double* outputs = new double[2]{1,1}; //
    NeuralNetworkTrainer nnt(&nn, inputs, outputs, training_set_size);

    nnt.RunTraining(0.0001);

    return 0;
}
