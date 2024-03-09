#pragma once
#include "Core.hpp"
class Processor
{
public:
    int memory[4096] = {0};
    int clock = 0;
    Core cores[2];
    long long top = 0;
    // void upload(Core cores[]);
    void run(int d);

    // Add any other member functions or data members if needed
};
