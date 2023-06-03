#include "Neuron.h"

Neuron::Neuron(const uint& num_inputs, const uint& input_width, double (*activation)(double), double (*activationDerivative)(double), const uint& head_index, const uint& output_width)
{
    //ctor
    this->num_inputs = num_inputs;
    this->input_width = input_width;
    this->weights = new double[num_inputs];
    this->RandomizeWeights();
    this->activation = activation;
    this->activationDerivative = activationDerivative;
    this->head_index = head_index;
    this->output_width = output_width;

    uint total_input_buffer_length = num_inputs*input_width;
    this->input_buffer = new double[total_input_buffer_length];
    this->output_buffer = new double[output_width];
    memset(input_buffer, 0, total_input_buffer_length*sizeof(double));
    memset(output_buffer, 0, output_width*sizeof(double));
}

Neuron::~Neuron()
{
    //dtor
    delete[] this->weights;
    delete[] this->input_buffer;
    delete[] this->output_buffer;
}

void Neuron::RandomizeWeights(){
    double val;
    double pool_width = 1;
    for(uint i=0; i<this->num_inputs; i++){
        val = pool_width * (((double)rand())/((double)RAND_MAX));
        this->weights[i] = val;
        pool_width -= val;
    }
}
// "output_width" = input_width + num_inputs("num_weights")
void Neuron::Process(){

    for(uint i=0x0; i<num_inputs; i++){
        for(uint j=0x0; j<input_width; j++){
            output_buffer[j] += weights[i]*input_buffer[i*input_width+j];
        }
        output_buffer[input_width+0x1+head_index+i] = input_buffer[i*input_width];
    }
    double activation_value = activation(output_buffer[0]);
    for(uint i=0x1; i<input_width; i++){
        output_buffer[i] *= activationDerivative(output_buffer[0]);
    }
}

void Neuron::StoreInput(double* buffer){
    memcpy(buffer, input_buffer, num_inputs*input_width*sizeof(double));
}

void Neuron::LoadOutput(double* buffer){
    memcpy(buffer, output_buffer, output_width*sizeof(double));
}

void Neuron::AdjustWeights(double* d_weights){
    for(uint i=0x0; i<this->num_inputs; i++){
        this->weights[i] += d_weights[i];
    }
}

uint Neuron::GetNumInputs(){
    return this->num_inputs;
}
