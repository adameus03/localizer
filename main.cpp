#include <iostream>
#include "Localizer.h"
#include "train_localizer.h" //training
#include <cstring> // strcmp

void usage(char* argv0){
    std::cout << "Usage: " << std::endl;
    std::cout << "    " << argv0 << " train " << std::endl;
    std::cout << "    " << argv0 << " run <weights_path> " << std::endl;
 }

int main(int argc, char** argv)
{
    /*Test test;
    test.run_tests();
    return 0;*/
    //Localizer loca;
    //train(); return 0;

    /*double x = 0.43252613609;//0.988536657913;//0.292227482595;
    double y = 0.480781318768;//0.216041449971;//0.46211715726;

    loca.CorrectLocation(x, y);

    std::cout << "Corrected x: " << x << std::endl;
    std::cout << "Corrected y: " << y << std::endl;*/


    if(argc == 2){
        if(!strcmp("train", argv[1])){
            train();
            return 0;
        }
        else {
            usage(*argv);
            return 0;
        }
    }

    else if(argc == 3){
        if(!strcmp("run", argv[1])){
            //proceed
        }
        else {
            usage(*argv);
            return 0;
        }
    }
    /*else if(argc == 4){
        if(!strcmp("correct", argv[1])){
            //proceed
        }
        else {
            usage(*argv);
            return 0;
        }
    }*/
    else {
        usage(*argv);
        return 0;
    }

    Localizer loca(argv[2]);




    std::cout << "Processing F8 data..." << std::endl;
    std::cout << "f8_1p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_1p.bin", "validation_output_data\\outputs_f8_1p.bin");
    std::cout << "f8_1z..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_1z.bin", "validation_output_data\\outputs_f8_1z.bin");
    std::cout << "f8_2p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_2p.bin", "validation_output_data\\outputs_f8_2p.bin");
    std::cout << "f8_2z..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_2z.bin", "validation_output_data\\outputs_f8_2z.bin");
    std::cout << "f8_3p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_3p.bin", "validation_output_data\\outputs_f8_3p.bin");
    std::cout << "f8_3z..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_3z.bin", "validation_output_data\\outputs_f8_3z.bin");
    std::cout << "f8_random_1p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_random_1p.bin", "validation_output_data\\outputs_f8_random_1p.bin");
    std::cout << "f8_random_2p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f8_random_2p.bin", "validation_output_data\\outputs_f8_random_2p.bin");
    std::cout << "Processing F10 data..." << std::endl;
    std::cout << "f10_1p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_1p.bin", "validation_output_data\\outputs_f10_1p.bin");
    std::cout << "f10_1z..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_1z.bin", "validation_output_data\\outputs_f10_1z.bin");
    std::cout << "f10_2p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_2p.bin", "validation_output_data\\outputs_f10_2p.bin");
    std::cout << "f10_2z..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_2z.bin", "validation_output_data\\outputs_f10_2z.bin");
    std::cout << "f10_3p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_3p.bin", "validation_output_data\\outputs_f10_3p.bin");
    std::cout << "f10_3z..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_3z.bin", "validation_output_data\\outputs_f10_3z.bin");
    std::cout << "f10_random_1p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_random_1p.bin", "validation_output_data\\outputs_f10_random_1p.bin");
    std::cout << "f10_random_2p..." << std::endl;
    loca.BatchCorrectLocation("validation_input_data\\inputs_f10_random_2p.bin", "validation_output_data\\outputs_f10_random_2p.bin");

    std::cout << "Finished processing data." << std::endl;

    return 0;
}
