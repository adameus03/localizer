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
    double* inputs_head = NULL;
    double* outputs_head = NULL;

    uint nn_inputs_num = neural_network->GetStructure()[0];
    uint nn_outputs_num = neural_network->GetStructure()[neural_network->GetNumLayers()];

    neural_network->AllocateGradient();

    double adjustment_size = 1;

    double loss, last_loss;

    uint epoch_index = 0;


    double* verbose_weights = new double[8/*38*/];
    double* verbose_outputs = new double[2];

    double* p_last_loss = NULL;

    while(true) {
        inputs_head = inputs;
        outputs_head = outputs;
        std::cout << "--- Epoch " << epoch_index++ << " ---" << std::endl;
        std::cout << "adjustment_size = " << adjustment_size << std::endl;

        uchar breakout = 0x0;

        for(uint i=0x0; i<this->training_set_size; i++){

            neural_network->StoreInput(inputs_head);


            neural_network->GetWeights(verbose_weights);
            std::cout << "weights ";
            for(uint i=0x0; i<0x8; i++){                    ///////////////////////
                std::cout <<verbose_weights[i] << " ";     //  print weights    //
            }                                             //                   //
            std::cout << std::endl;                      ///////////////////////



            //neural_network->GetWeights(weights);
            //neural_network->Computation(/*inputs_head, */outputs_head, adjustment_size);
            neural_network->Computation();
            loss = neural_network->Loss(outputs_head);



            neural_network->LoadOutput(verbose_outputs);
            std::cout << "outputs: ";
            for(uint i=0x0; i<0x2; i++){
                std::cout << verbose_outputs[i] << " ";
            }
            std::cout << std::endl;


            std::cout << "loss: ";
            std::cout << loss;
            std::cout << std::endl;





            //loss_2 = neural_network->Loss(outputs_head);

            if(p_last_loss != NULL){
                if(loss >= *p_last_loss) { adjustment_size /= 2; }
            }

            last_loss = loss;
            p_last_loss = &last_loss;

            if(loss <= accuracy) {
                breakout = 0x1;
                break;
            }
            neural_network->ImproveAfterComputation(outputs_head, adjustment_size);

            inputs_head += nn_inputs_num;
            outputs_head += nn_outputs_num;
        }
        if(breakout) break;
    }
    //while(loss > accuracy);



    neural_network->GetWeights(verbose_weights);
    std::cout << "Final weights ";
    for(uint i=0x0; i<0x8; i++){                    /////////////////////////////
        std::cout <<verbose_weights[i] << " ";     //  print final weights    //
    }                                             //                         //
    std::cout << std::endl;                      /////////////////////////////

    neural_network->LoadOutput(verbose_outputs);
    std::cout << "\"Final outputs\": ";
    for(uint i=0x0; i<0x2; i++){
        std::cout << verbose_outputs[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "Final loss: ";
    std::cout << loss;
    std::cout << std::endl;






    neural_network->DeallocateGradient();

    std::cout << "!! End training" << std::endl;
}
