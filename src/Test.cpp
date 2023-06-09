#include "Test.h"

Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
}

void Test::checker(const uchar& ok, const char* description){
    std::cout << '[' << (ok?"OK":"!!") << "]  " << description << std::endl;
}

void Test::run_tests(){
    this->checker(this->NeuronTest_1(), "NeuronTest_1");
    this->checker(this->NeuronTest_2(), "NeuronTest_2");
    this->checker(this->NeuralNetworkTest_1(), "NeuralNetworkTest_1");
    this->checker(this->NeuralNetworkTest_2(), "NeuralNetworkTest_2");
    this->checker(this->NeuralNetworkTest_3(), "NeuralNetworkTest_3");
    this->checker(this->DataSourceTest(), "DataSourceTest");

}

uchar Test::is_close(const double& a, const double& b, const double& precission){
    if(a>b){
        if(a-b<precission) return 0x1;
    }
    else{
        if(b-a<precission) return 0x1;
    }
    return 0x0;
}

uchar Test::NeuronTest_1(){
    Neuron n(2, 1, relu, relu_d, 0, 9);
    double* weights = new double[2]{1,1};
    double* input = new double[2]{1,1};
    n.PutWeights(weights);
    n.StoreInput(input);
    n.Process();
    double* output = new double[9];
    n.LoadOutput(output);

    uchar retval = 0x1;
    if(output[0] != 1.5) retval = 0x0;
    else if(output[1] != 1) retval = 0x0;
    else if(output[2] != 1) retval = 0x0;
    else if(output[3] != 0) retval = 0x0;
    else if(output[4] != 0) retval = 0x0;
    else if(output[5] != 0) retval = 0x0;
    else if(output[6] != 0) retval = 0x0;
    else if(output[7] != 0) retval = 0x0;
    else if(output[8] != 0) retval = 0x0;

    delete[] weights;
    delete[] input;
    delete[] output;

    return retval;
}

uchar Test::NeuronTest_2(){
    Neuron n(2, 5, relu, relu_d, 2, 9);
    double* weights = new double[2]{1,1};
    double* input = new double[10]{1.5,1,1,0,0, 1.5,0,0,1,1};
    n.PutWeights(weights);
    n.StoreInput(input);
    n.Process();
    double* output = new double[9];
    n.LoadOutput(output);

    uchar retval = 0x1;
    if(output[0] != 2.5) retval = 0x0;
    else if(output[1] != 1) retval = 0x0;
    else if(output[2] != 1) retval = 0x0;
    else if(output[3] != 1) retval = 0x0;
    else if(output[4] != 1) retval = 0x0;
    else if(output[5] != 0) retval = 0x0;
    else if(output[6] != 0) retval = 0x0;
    else if(output[7] != 1.5) retval = 0x0;
    else if(output[8] != 1.5) retval = 0x0;

    delete[] weights;
    delete[] input;
    delete[] output;
    return retval;
}

uchar Test::NeuralNetworkTest_1(){
    double* weights = new double[8]{1,1,1,1,1,1,1,1};
    double* input = new double[2]{1,1};
    double* output = new double[2];

    uint* structure = new uint[3]{2,2,2};
    double (**activation)(double) = new RealFunction[2]{relu, relu};
    double (**activationDerivative)(double) = new RealFunction[2]{relu_d, relu_d};

    NeuralNetwork nn(structure, 2, activation, activationDerivative);
    nn.PutWeights(weights);


    nn.StoreInput(input);
    nn.Computation(/*input*/);
    nn.LoadOutput(output);

    uchar retval = 0x1;
    if(output[0] != 2.5) retval = 0x0;
    else if(output[1] != 2.5) retval = 0x0;

    delete[] weights;
    delete[] input;
    delete[] output;
    delete[] structure;
    delete[] activation;
    delete[] activationDerivative;

    return retval;
}

uchar Test::NeuralNetworkTest_2(){
    double* weights = new double[8]{1,1,1,1,1,1,1,1};
    double* input = new double[2]{1,1};
    double* expected_output = new double[2]{1, 1};
    //double* output = new double[2];

    uint* structure = new uint[3]{2,2,2};
    double (**activation)(double) = new RealFunction[2]{relu, relu};
    double (**activationDerivative)(double) = new RealFunction[2]{relu_d, relu_d};

    NeuralNetwork nn(structure, 2, activation, activationDerivative);
    nn.PutWeights(weights);

    nn.AllocateGradient();
    nn.StoreInput(input);
    nn.Computation();
    //nn.Computation(/*input, */expected_output, 1);
    nn.ImproveAfterComputation(expected_output, 1);
    nn.DeallocateGradient();


    double* workspace = new double[nn.GetWorkspaceSize()];
    nn.GetWorkspace(workspace);
    double* output = new double[2];
    nn.LoadOutput(output);


    nn.GetWeights(weights);
    uchar retval = 0x1;
    if(!is_close(weights[0], 0.6, 0.00001)) retval = 0x0;
    else if(!is_close(weights[1], 0.6, 0.00001)) retval = 0x0;
    else if(!is_close(weights[2], 0.6, 0.00001)) retval = 0x0;
    else if(!is_close(weights[3], 0.6, 0.00001)) retval = 0x0;
    else if(!is_close(weights[4], 0.7, 0.00001)) retval = 0x0;
    else if(!is_close(weights[5], 0.7, 0.00001)) retval = 0x0;
    else if(!is_close(weights[6], 0.7, 0.00001)) retval = 0x0;
    else if(!is_close(weights[7], 0.7, 0.00001)) retval = 0x0;

    delete[] weights;
    delete[] input;
    delete[] expected_output;
    delete[] structure;
    delete[] activation;
    delete[] activationDerivative;

    return retval;

}

uchar Test::NeuralNetworkTest_3(){
    double* weights = new double[8]{0.6,0.6,0.6,0.6,0.7,0.7,0.7,0.7};
    double* input = new double[2]{1,1};
    double* expected_output = new double[2]{1, 1};
    //double* output = new double[2];

    uint* structure = new uint[3]{2,2,2};
    double (**activation)(double) = new RealFunction[2]{relu, relu};
    double (**activationDerivative)(double) = new RealFunction[2]{relu_d, relu_d};

    NeuralNetwork nn(structure, 2, activation, activationDerivative);
    nn.PutWeights(weights);

    nn.AllocateGradient();
    nn.StoreInput(input);
    nn.Computation();
    //nn.Computation(/*input, */expected_output, 1);
    nn.ImproveAfterComputation(expected_output, 1);
    nn.DeallocateGradient();


    double* workspace = new double[nn.GetWorkspaceSize()];
    nn.GetWorkspace(workspace);
    double* output = new double[2];
    nn.LoadOutput(output);


    nn.GetWeights(weights);
    uchar retval = 0x1;
    if(!is_close(weights[0], 1.047, 0.001)) retval = 0x0;
    else if(!is_close(weights[1], 1.047, 0.001)) retval = 0x0;
    else if(!is_close(weights[2], 1.047, 0.001)) retval = 0x0;
    else if(!is_close(weights[3], 1.047, 0.001)) retval = 0x0;
    else if(!is_close(weights[4], 0.9236, 0.001)) retval = 0x0;
    else if(!is_close(weights[5], 0.9236, 0.001)) retval = 0x0;
    else if(!is_close(weights[6], 0.9236, 0.001)) retval = 0x0;
    else if(!is_close(weights[7], 0.9236, 0.001)) retval = 0x0;

    delete[] weights;
    delete[] input;
    delete[] expected_output;
    delete[] structure;
    delete[] activation;
    delete[] activationDerivative;

    return retval;

}



/*uchar Test::NeuralNetworkTest_3(){
    double* weights = new double[8]{1,1,1,1,1,1,1,1};
    double* input = new double[2]{1,1};
    double* output = new double[2];

    uint* structure = new uint[3]{2,2,2};
    double (**activation)(double) = new RealFunction[2]{relu, relu};
    double (**activationDerivative)(double) = new RealFunction[2]{relu_d, relu_d};

    NeuralNetwork nn(structure, 2, activation, activationDerivative);
    nn.PutWeights(weights);


    nn.StoreInput(input);
    nn.Computation(input*//*);
    nn.LoadOutput(output);

    uchar retval = 0x1;
    if(output[0] != 2.5) retval = 0x0;
    else if(output[1] != 2.5) retval = 0x0;

    delete[] weights;
    delete[] input;
    delete[] output;
    delete[] structure;
    delete[] activation;
    delete[] activationDerivative;

    return retval;
}*/

uchar Test::DataSourceTest(){
    DataSource ds_in("train_data\\inputs.bin");
    DataSource ds_out("train_data\\outputs.bin");

    ull training_set_size = 0;
    double* inputs = ds_in.GetData(training_set_size);
    double* outputs = ds_out.GetData(training_set_size);
    delete[] inputs;
    delete[] outputs;

    uchar retval = 0x1;

    //if(!is_close(inputs[0], 7526, 0.00001)) retval = 0x0;
    //if(!is_close(inputs[1], 7549, 0.00001)) retval = 0x0;
    if(training_set_size != 112886) retval = 0x0;

    return retval;
}
