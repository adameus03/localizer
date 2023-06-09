#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "../functions.h"
//#include "Neuron.h"
#include "NeuralNetwork.h"
#include "DataSource.h"


typedef unsigned char uchar;
typedef unsigned int uint;
typedef double (*RealFunction)(double);

class Test
{
    public:
        Test();
        virtual ~Test();
        void checker(const uchar& ok, const char* description);
        void run_tests();
        uchar is_close(const double& a, const double& b, const double& precission);

        uchar NeuronTest_1();
        uchar NeuronTest_2();
        uchar NeuralNetworkTest_1();
        uchar NeuralNetworkTest_2();
        uchar NeuralNetworkTest_3();
        uchar DataSourceTest();

    protected:

    private:
};

#endif // TEST_H
