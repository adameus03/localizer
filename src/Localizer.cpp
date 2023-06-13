#include "Localizer.h"

Localizer::Localizer(const char* weights_path)
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
    this->LoadWeights(weights_path);
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

void Localizer::LoadWeights(const char* weights_path){
    //const char* path = /*"weights\\weights_trunc_0.0117629_14597.bin";*/ /*"weights\\weights_trunc_0_0118047_7416.bin";*/ /*"weights\\weights.bin";*/ "weights\\weights_0_00428953.bin"; /*"weights\\weights_0_00467.bin"*/;
    const char* path = weights_path;
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

void Localizer::BatchCorrectLocation(const char* input_path, const char* output_path){
    std::ifstream f_in(input_path, std::ifstream::binary);
    std::filebuf* f_in_pbuf = f_in.rdbuf();
    size_t sbuff_size = f_in_pbuf->pubseekoff(0, f_in.end, f_in.in);
    f_in_pbuf->pubseekpos(0, f_in.in);

    uchar* sbuff = new uchar[sbuff_size];
    f_in_pbuf->sgetn((char*)sbuff, sbuff_size);
    f_in.close();

    double* input_data = reinterpret_cast<double*>(sbuff);
    ull num_samples = sbuff_size/sizeof(double)/2;
    double* output_data = new double[num_samples<<0x1];

    double x, y;
    for(ull i=0x0; i<num_samples; i++){
        x = input_data[i<<0x1];
        y = input_data[(i<<0x1)+0x1];

        this->CorrectLocation(x, y);

        output_data[i<<0x1] = x;
        output_data[(i<<0x1)+0x1] = y;
    }

    uchar* dbuff = reinterpret_cast<uchar*>(output_data);
    ull dbuff_size = sbuff_size;

    std::ofstream f_out(output_path, std::ofstream::trunc|std::ofstream::binary);
    std::filebuf* f_out_pbuf = f_out.rdbuf();
    f_out_pbuf->sputn((char*)dbuff, dbuff_size);
    f_out.close();

}
