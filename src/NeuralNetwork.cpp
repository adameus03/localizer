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
    uint total_num_weights = 0;
    for(uint i=0; i<num_layers; i++){
        total_num_neurons += this->structure[i+1];
        total_num_weights += this->structure[i] * this->structure[i+1];
    }
    //this->total_num_neurons = total_num_neurons;
    this->total_num_weights = total_num_weights;
    this->neurons = new Neuron*[total_num_neurons];
    uint neuron_index = 0;

    uint input_width_accumulator = 1;
    uint output_width;
    for(uint i=0; i<num_layers; i++){
        output_width = input_width_accumulator + this->structure[i]*this->structure[i+1];
        for(uint j=0; j<this->structure[i+1]; j++){

            this->neurons[neuron_index] = new Neuron(this->structure[i], input_width_accumulator, this->activation[i], this->activationDerivative[i], j*this->structure[i], output_width);
            neuron_index++;

        }
        input_width_accumulator = output_width;
    }
    this->max_output_width = output_width;
    uint max_layer_size = 0;

    for(uint i=0; i<this->num_layers; i++){
        if(this->structure[i+1] > max_layer_size){
            max_layer_size = this->structure[i];
        }
    }

    uint workspace_size = this->max_output_width * max_layer_size;
    this->workspace = new double[workspace_size];
    memset(this->workspace, 0, workspace_size*sizeof(double));
}

NeuralNetwork::~NeuralNetwork()
{
    //dtor
    delete[] this->neurons;
    delete[] this->workspace;
    delete[] this->activation;
    delete[] this->activationDerivative;
}

void NeuralNetwork::Computation(double* input){
    uint neuron_index = 0;
    uint input_width_accumulator = 1;
    uint output_width;
    for(uint i=0x0; i<this->num_layers-0x1; i++){
        output_width = input_width_accumulator + this->structure[i]*this->structure[i+1];

        for(uint j=0x0; j<this->structure[i+1]; j++){
            this->neurons[neuron_index]->Process();
            this->neurons[neuron_index]->LoadOutput(this->workspace+output_width*j);
            neuron_index++;
        }

        uint temp_neuron_index = neuron_index;

        for(uint j=0x0; j<this->structure[i+2]; j++){
            this->neurons[neuron_index]->StoreInput(this->workspace+output_width*j);
            neuron_index++;
        }

        neuron_index = temp_neuron_index;
        input_width_accumulator = output_width;
    }

    for(uint j=0x0; j<this->structure[this->num_layers]; j++){
        this->neurons[neuron_index]->Process();
        this->neurons[neuron_index]->LoadOutput(this->workspace+output_width*j);
        neuron_index++;
    }
}

void NeuralNetwork::Computation(double* input, double* expected_output){
    this->Computation(input);

}

/*void NeuralNetwork::GetOutput(double* output){

}*/

void NeuralNetwork::StoreInput(double* input){
    for(uint i=0x0; i<structure[1]; i++){
        this->neurons[i]->StoreInput(input);
    }
}

void NeuralNetwork::LoadOutput(double* output){
    for(uint i=0x0; i<this->structure[num_layers]; i++){
        output[i] = this->workspace[i*max_output_width];
    }
}

double NeuralNetwork::Loss(double* expected_output){
    double sum = 0;
    double term;
    for(uint i=0x0; i<this->structure[num_layers]; i++){
        term = this->workspace[i*max_output_width] - expected_output[i];
        sum += term*term;
    }
    return sum;
}

void NeuralNetwork::LossDerivative(double* expected_output, double* gradient){
    double sum;
    double difference;
    for(uint i=0x0; i<this->total_num_weights; i++){
        sum = 0;
        for(uint j=0x0; j<this->structure[num_layers]; j++){
            difference = this->workspace[j*max_output_width] - expected_output[j];
            sum += difference*this->workspace[j*max_output_width+0x1+i];
        }
        gradient[i] = 2*sum;
    }
}





//How about creating your own filesystem?
