#ifndef LOCALIZER_H
#define LOCALIZER_H

#include "NeuralNetwork.h"
#include "../functions.h"
#include <fstream>
#include <cstring> //memcpy

typedef unsigned char uchar;
typedef unsigned long long ull;

class Localizer
{
    public:
        Localizer(const char* weights_path);
        virtual ~Localizer();
        void CorrectLocation(double& x, double& y);
        void LoadWeights(const char* weights_path);

        void BatchCorrectLocation(const char* input_path, const char* output_path);

    protected:

    private:
        NeuralNetwork* neural_network = NULL;
        double* input = NULL;
        double* output = NULL;
        double* weights = NULL;
        /*double* weights = new double[38]{
            71.0899, -66.3061, -25.04, -48.3774, -19.5328, -19.6738, 7.61884, -18.9486,
            38.2147, 36.8348, 9.2015, 0.197248, 1.03145, 5.5729, -0.990886, -8.43766,
            -1.22508, -0.636766, 7.44189, 0.861939, 1.30414, 1.39756, 0.93117, -11.193,
            -0.131486, 1.28045, 0.214349, -0.302902, -0.506147, -0.113592, -3.90705, 11.1895,
            -2.51862, 29.3181, -3.45548, 2.6115, -0.346773, 10.0454};*/


};

#endif // LOCALIZER_H
