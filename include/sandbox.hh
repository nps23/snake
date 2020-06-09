#include <iostream>
#include <random>

namespace Sandbox
{
    void Test()
    {
        std::cout << "Testing from Sandbox" << std::endl;
        std::default_random_engine generator(time(NULL));
        std::uniform_int_distribution<int> distribution(1, 6);
        
        while(true)
        {
            // uniform distribtuion

            int value = distribution(generator);
            std::cout << value << std::endl;
            std::cin.get();
        } 
    }

    void Debug()
    {
        std::cout << "Debug from Sandbox" << std::endl;
    }

};