#ifndef TRAIN_LOCALIZER_H_INCLUDED
#define TRAIN_LOCALIZER_H_INCLUDED

#include <iostream>
#include "NeuralNetwork.h"
#include "NeuralNetworkTrainer.h"
#include "DataSource.h"
#include <sys/stat.h>
#include "functions.h"
#include "Test.h" //testing
#include <cstring> //testing (memset)
#include <windows.h> //multithreading

typedef unsigned int uint;
typedef unsigned long long ull;
typedef double (*RealFunction)(double);

void train();
void multithreaded_train();

#endif // TRAIN_LOCALIZER_H_INCLUDED
