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

    double adjustment_size =  /*1*/ 0.0001;

    //double loss, last_loss;

    uint epoch_index = 0;


    double* verbose_weights = new double[neural_network->GetTotalNumWeights()/*8*//*38*/];
    double* verbose_outputs = new double[neural_network->GetStructure()[neural_network->GetNumLayers()]/*2*/];

    //double* p_last_loss = NULL;

    double* losses = new double[this->training_set_size];

    while(true) {
        inputs_head = inputs;
        outputs_head = outputs;
        //getchar();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        //std::cout << "\033[35;106m --- Epoch " << epoch_index++ << " ---\033[m" << std::endl;
        ///std::cout << "--- Epoch " << epoch_index++ << " ---" << std::endl;
        //getchar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << "adjustment_size = " << adjustment_size << std::endl;

        uchar breakout = 0x0;

        for(uint i=0x0; i<this->training_set_size; i++){

            neural_network->StoreInput(inputs_head);


            /*neural_network->GetWeights(verbose_weights);
            std::cout << "weights ";
            for(uint i=0x0; i<neural_network->GetTotalNumWeights(); i++){                    ///////////////////////
                std::cout <<verbose_weights[i] << " ";     //  print weights    //
            }                                             //                   //
            std::cout << std::endl;                      ///////////////////////*/



            //neural_network->GetWeights(weights);
            //neural_network->Computation(/*inputs_head, */outputs_head, adjustment_size);
            /*if(i == 12277){
                std::cout << "here" << std::endl;
            }*/
            neural_network->Computation();
            losses[i] = neural_network->Loss(outputs_head);



            /*neural_network->LoadOutput(verbose_outputs);
            std::cout << "outputs: ";
            for(uint i=0x0; i<neural_network->GetStructure()[neural_network->GetNumLayers()]; i++){
                std::cout << verbose_outputs[i] << " ";
            }
            std::cout << std::endl;*/


            /*std::cout << "loss: ";
            std::cout << loss;
            std::cout << std::endl;*/





            //loss_2 = neural_network->Loss(outputs_head);

            //if(p_last_loss != NULL){
                /* if(loss >= *p_last_loss) { adjustment_size /= 2; } */
            //}

            //last_loss = loss;
            //p_last_loss = &last_loss;
            //losses[i] = loss;

            /*if(loss <= accuracy) {
                std::cout << "LOSS <= ACCURACY ( " << loss << " <= " << accuracy << ")" << std::endl;
                breakout = 0x1;
                break;
            }*/
            neural_network->ImproveAfterComputation(outputs_head, adjustment_size);

            inputs_head += nn_inputs_num;
            outputs_head += nn_outputs_num;
        }
        /*if(breakout){
            std::cout << "BREAKOUT" << std::endl;
            std::cout << this->training_set_size << std::endl;
            break;
        }*/
        //
        /*neural_network->GetWeights(verbose_weights);
        std::cout << "weights ";
        for(uint i=0x0; i<neural_network->GetTotalNumWeights(); i++){                    ///////////////////////
            std::cout <<verbose_weights[i] << " ";     //  print weights    //
        }                                             //                   //
        std::cout << std::endl;  */                    ///////////////////////

        neural_network->GetWeights(verbose_weights);
        this->SaveWeights(verbose_weights);





        /*neural_network->LoadOutput(verbose_outputs);
        std::cout << "outputs: ";
        for(uint i=0x0; i<neural_network->GetStructure()[neural_network->GetNumLayers()]; i++){
            std::cout << verbose_outputs[i] << " ";
        }
        std::cout << std::endl;*/


        /*std::cout << "losses: ";
        for(uint i=0x0; i<this->training_set_size; i++){
            std::cout << losses[i] << " ";
        }
        std::cout << std::endl;*/


        double losses_sum = 0;
        for(uint i=0x0; i<this->training_set_size; i++){
            losses_sum += losses[i];
        }
        double losses_avg = losses_sum / (double)(this->training_set_size);

        std::cout << "avg loss: ";
        std::cout << losses_avg;
        std::cout << std::endl;

        //if(p_last_loss != NULL){
            //if(loss >= *p_last_loss) { adjustment_size /= 2; } //////
        //}

        //last_loss = loss;
        //p_last_loss = &last_loss;
        if(losses_avg <= accuracy) {
            std::cout << "LOSSES_AVG <= ACCURACY ( " << losses_avg << " <= " << accuracy << ")" << std::endl;
            //breakout = 0x1;
            break;
        }

    }
    //while(loss > accuracy);



    /*neural_network->GetWeights(verbose_weights);
    std::cout << "Final weights ";
    for(uint i=0x0; i</neural_network->GetTotalNumWeights(); i++){                    /////////////////////////////
        std::cout <<verbose_weights[i] << " ";                                              //  print final weights    //
    }                                                                                       //                         //
    std::cout << std::endl;                                                                 /////////////////////////////

    neural_network->LoadOutput(verbose_outputs);
    std::cout << "\"Final outputs\": ";
    for(uint i=0x0; i<neural_network->GetStructure()[neural_network->GetNumLayers()]; i++){
        std::cout << verbose_outputs[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "Final loss: ";
    std::cout << loss;
    std::cout << std::endl;*/






    neural_network->DeallocateGradient();

    std::cout << "!! End training" << std::endl;
}

void NeuralNetworkTrainer::SaveWeights(double* w_buffer){
    /*for(ull i=0x0; i<this->neural_network->GetTotalNumWeights(); i++){

    }*/
    uchar* buf = reinterpret_cast<uchar*>(w_buffer);
    ull buf_size = this->neural_network->GetTotalNumWeights() * sizeof(double);

    std::ofstream f_out("weights\\weights.bin", std::ofstream::trunc|std::ofstream::binary);
    std::filebuf* f_out_pbuf = f_out.rdbuf();
    f_out_pbuf->sputn((char*)buf, buf_size);
    f_out.close();

}



DWORD WINAPI ThreadFunction(LPVOID lpParam){
    //ull* threadData = static_cast<ull*>(lpParam);
    //ull index = *threadData;
    //ull batchSize = *(threadData+0x1);
    return 0;
}

void NeuralNetworkTrainer::RunMultithreadedTraining(const uchar& num_threads, const double& accuracy){
    std::cout << "!! Start training" << std::endl;
    double* inputs_head = NULL;
    double* outputs_head = NULL;

    uint nn_inputs_num = neural_network->GetStructure()[0];
    uint nn_outputs_num = neural_network->GetStructure()[neural_network->GetNumLayers()];

    neural_network->AllocateGradient();

    double adjustment_size =  /*1*/ 0.0001;

    uint epoch_index = 0;

    double* verbose_weights = new double[neural_network->GetTotalNumWeights()/*8*//*38*/];
    double* verbose_outputs = new double[neural_network->GetStructure()[neural_network->GetNumLayers()]/*2*/];

    double* losses = new double[this->training_set_size];

    while(true) {
        inputs_head = inputs;
        outputs_head = outputs;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        //std::cout << "--- Epoch " << epoch_index++ << " ---" << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << "adjustment_size = " << adjustment_size << std::endl;
        uchar breakout = 0x0;





        for(uint i=0x0; i<this->training_set_size; i++){
            neural_network->StoreInput(inputs_head);
            neural_network->Computation();
            losses[i] = neural_network->Loss(outputs_head);

            neural_network->ImproveAfterComputation(outputs_head, adjustment_size);

            inputs_head += nn_inputs_num;
            outputs_head += nn_outputs_num;
        }





        neural_network->GetWeights(verbose_weights);
        this->SaveWeights(verbose_weights);

        double losses_sum = 0;
        for(uint i=0x0; i<this->training_set_size; i++){
            losses_sum += losses[i];
        }
        double losses_avg = losses_sum / (double)(this->training_set_size);

        std::cout << "avg loss: " << losses_avg << std::endl;

        if(losses_avg <= accuracy) {
            std::cout << "LOSSES_AVG <= ACCURACY ( " << losses_avg << " <= " << accuracy << ")" << std::endl;
            break;
        }
    }

    neural_network->DeallocateGradient();

    std::cout << "!! End training" << std::endl;
}
