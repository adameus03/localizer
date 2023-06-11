#include <iostream>
#include "Localizer.h"
#include "train_localizer.h" //training


int main()
{
    /*Test test;
    test.run_tests();
    return 0;*/

    //train(); return 0;

    Localizer loca;

    double x = 0.43252613609;//0.988536657913;//0.292227482595;
    double y = 0.480781318768;//0.216041449971;//0.46211715726;

    loca.CorrectLocation(x, y);

    std::cout << "Corrected x: " << x << std::endl;
    std::cout << "Corrected y: " << y << std::endl;


    return 0;
}
