#pragma once
#include "Core.hpp"
class Processor
{
public:
    int memory[4096] = {0};
    int clock = 0;
    Core cores[2];
    long long top = 0;
    void run(int d, int policy);
    void writeCSV(const vector<vector<string>> &data, const string &filename, int i);
    void writeCSV1(const vector<vector<string>> &data, const string &filename, int i);
    Cache cache;
    // Add any other member functions or data members if needed
};
