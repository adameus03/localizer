#include "NeuralNetworkTrainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(NeuralNetwork* neural_network, double* inputs, double* outputs, const uint& training_set_size)
{
    //ctor
    this->neural_network = neural_network;
    this->inputs = inputs;
    this->outputs = outputs;
    this->training_set_size = training_set_size;
}

NeuralNetworkTrainer::~NeuralNetworkTrainer()
{
    //dtor
}

void NeuralNetworkTrainer::RunTraining(const double& accuracy){
    std::cout << "!! Start training" << std::endl;
    double* inputs_head = inputs;
    double* outputs_head = outputs;

    uint nn_inputs_num = neural_network->GetStructure()[0];
    uint nn_outputs_num = neural_network->GetStructure()[neural_network->GetNumLayers()];

    neural_network->AllocateGradient();

    double adjustment_size = 1;

    double loss_1, loss_2;

    uint epoch_index = 0;

    do {
        std::cout << "--- Epoch " << epoch_index++ << " ---" << std::endl;
        for(uint i=0x0; i<this->training_set_size; i++){
            loss_1 = neural_network->Loss(outputs_head);
            neural_network->Computation(inputs_head, outputs_head, adjustment_size);
            loss_2 = neural_network->Loss(outputs_head);

            if(loss_2 > loss_1) { adjustment_size /= 2; }

            inputs_head += nn_inputs_num;
            outputs_head += nn_outputs_num;
        }
    }
    while(loss_2 > accuracy);

    neural_network->DeallocateGradient();

    std::cout << "!! End training" << std::endl;
}
