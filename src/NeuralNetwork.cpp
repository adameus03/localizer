#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(uint* structure, const uint& num_layers, double (**activation)(double), double (**activationDerivative)(double))
{
    //ctor
    this->num_layers = num_layers;
    this->structure = new uint[this->num_layers+0x1];
    memcpy(this->structure, structure, (num_layers+0x1)*sizeof(uint));
    this->activation = new RealFunction[this->num_layers];
    this->activationDerivative = new RealFunction[this->num_layers];
    memcpy(this->activation, activation, this->num_layers*sizeof(RealFunction));
    memcpy(this->activationDerivative, activationDerivative, this->num_layers*sizeof(RealFunction));

    uint total_num_neurons = 0;
    for(uint i=0; i<num_layers; i++){
        total_num_neurons += this->structure[i];
    }
    this->neurons = new Neuron*[total_num_neurons];
    uint neuron_index = 0;

    uint input_width_accumulator = 1;
    uint output_width;
    for(uint i=0; i<num_layers; i++){
        for(uint j=0; j<this->structure[i+1]; j++){
            output_width = input_width_accumulator + this->structure[i]*this->structure[i+1];
            this->neurons[neuron_index] = new Neuron(this->structure[i], input_width_accumulator, this->activation[i], this->activationDerivative[i], j*this->structure[i], output_width);
            input_width_accumulator = output_width;
            neuron_index++;
        }
    }
}

NeuralNetwork::~NeuralNetwork()
{
    //dtor
}

void NeuralNetwork::Computation(double* input){

}

void NeuralNetwork::Computation(double* input, double* expected_output){

}

void NeuralNetwork::GetOutput(double* output){

}






//How about creating your own filesystem?
