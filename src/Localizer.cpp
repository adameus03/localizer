#include "Localizer.h"

Localizer::Localizer()
{
    //ctor
    //uint* structure = new uint[4]{2, 5, 4, 2};
    uint* structure = new uint[5]{2, 20, 10, 5, 2};
    uint num_layers = 4;

    double (**activation)(double) = new RealFunction[4]{sigmoid, sigmoid, sigmoid, sigmoid};
    double (**activationDerivative)(double) = new RealFunction[4/*2*/]{sigmoid_d, sigmoid_d, sigmoid_d, sigmoid_d};
    this->neural_network = new NeuralNetwork(structure, num_layers, activation, activationDerivative);

    //this->neural_network->PutWeights(this->weights);

    this->input = new double[2];
    this->output = new double[2];

    this->weights = new double[this->neural_network->GetTotalNumWeights()];
    this->LoadWeights();
}

Localizer::~Localizer()
{
    //dtor
    //delete[] this->neural_network;
    //delete[] this->input;
    //delete[] this->output;
}

void Localizer::CorrectLocation(double& x, double& y){
    this->input[0] = x;
    this->input[1] = y;

    this->neural_network->StoreInput(this->input);
    this->neural_network->Computation();
    this->neural_network->LoadOutput(this->output);

    x = this->output[0];
    y = this->output[1];
}

void Localizer::LoadWeights(){
    const char* path = "weights\\weights_0_00467.bin";
    std::ifstream f_in(path, std::ifstream::binary);
    std::filebuf* f_in_pbuf = f_in.rdbuf();
    size_t sbuff_size = f_in_pbuf->pubseekoff(0, f_in.end, f_in.in);
    f_in_pbuf->pubseekpos(0, f_in.in);
    uchar* sbuff = new uchar[sbuff_size];
    f_in_pbuf->sgetn((char*)sbuff, sbuff_size);
    f_in.close();
    memcpy(reinterpret_cast<char*>(this->weights), (char*)sbuff, sbuff_size);
    this->neural_network->PutWeights(this->weights);
}
