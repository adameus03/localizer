#include "train_localizer.h"

void train(){
    //uint* structure = new uint[4]{2, 4, 3, 2};
    uint* structure = new uint[5]{2, 20, 10, 5, 2};


    uint num_layers = 4;
    //uint num_layers = 3;

    //double* weights = new double[38]; // 2*5+5*4+4*2 = 38 //
    //double* weights = new double[12];
    //memset(weights, 1, 38*sizeof(double));
    //std::fill_n(weights, /*38*/12, 1);


    double (**activation)(double) = new RealFunction[4/*2*/]{sigmoid, sigmoid, sigmoid, sigmoid};
    double (**activationDerivative)(double) = new RealFunction[4/*2*/]{sigmoid_d, sigmoid_d, sigmoid_d, sigmoid_d};
    NeuralNetwork nn(structure, num_layers, activation, activationDerivative);


    //nn.PutWeights(weights);

    ull training_set_size = 0;


    DataSource ds_in("train_data\\inputs.bin");
    DataSource ds_out("train_data\\outputs.bin");

    double* inputs = new double[225772/100]; //ds_in.GetData(training_set_size);
    double* outputs = new double[225772/100]; //ds_out.GetData(training_set_size);
    ds_in.GetBatch(inputs, 0x0, 225772/100);
    ds_out.GetBatch(outputs, 0x0, 225772/100);


    training_set_size = 112886/100;//112886;
    //double* inputs = new double[8]{0,1,1,0,1,2,2,1}; //
    //double* outputs = new double[8]{1,0,0,1,2,1,1,2}; //

    NeuralNetworkTrainer nnt(&nn, inputs, outputs, training_set_size);

    nnt.RunTraining(0/*0.0001*/);
}



CRITICAL_SECTION criticalSection;

/*DWORD WINAPI ThreadFunction(LPVOID lpParam){ // Under dev
    //ull* threadData = static_cast<ull*>(lpParam);
    //ull index = *threadData;
    //ull batchSize = *(threadData+0x1);

    //double* inputs = new double[225772];
    //double* outputs = new double[225772];
    //ds_in.GetBatch(inputs, 0x0, 225772);
    //ds_out.GetBatch(outputs, 0x0, 225772);

    //double* inputs = new double[batchSize];
    //double* outputs = new double[batchSize];
    //ds_in.GetBatch(inputs, index, batchSize);
    //ds_out.GetBatch(outputs, index, batchSize);

    //NeuralNetworkTrainer nnt(&nn, inputs, outputs, batchSize>>0x1);
}*/

void multithreaded_train(){ /* Under dev */
    uint* structure = new uint[5]{2, 20, 10, 5, 2};
    uint num_layers = 4;
    double (**activation)(double) = new RealFunction[4]{sigmoid, sigmoid, sigmoid, sigmoid};
    double (**activationDerivative)(double) = new RealFunction[4]{sigmoid_d, sigmoid_d, sigmoid_d, sigmoid_d};
    NeuralNetwork nn(structure, num_layers, activation, activationDerivative);

    DataSource ds_in("train_data\\inputs.bin");
    DataSource ds_out("train_data\\outputs.bin");

    double* inputs = new double[225772]; //ds_in.GetData(training_set_size);
    double* outputs = new double[225772]; //ds_out.GetData(training_set_size);
    ds_in.GetBatch(inputs, 0x0, 225772);
    ds_out.GetBatch(outputs, 0x0, 225772);


    ull training_set_size = 112886;//112886;

    NeuralNetworkTrainer nnt(&nn, inputs, outputs, training_set_size);

    nnt.RunTraining(0);

}
