#pragma once
#include "Core.hpp"
// #include "Cache.hpp"
class Processor
{
public:
    int memory[4096] = {0};
    int clock = 0;
    Core cores[2];
    long long top = 0;
    // void upload(Core cores[]);
    void run(int d);
    void writeCSV(const vector<vector<string>> &data, const string &filename,int i);
    void writeCSV1(const vector<vector<string>> &data, const string &filename,int i);
    Cache cache;
    // Add any other member functions or data members if needed
};
// class Tag
// {
// public:
//     int core = -1;
//     int address;
// };
// class Cache
// {
// public:
//     vector<list<Tag>> set;
//     unsigned int cacheSize;
//     unsigned int blockSize = 8;
//     unsigned int numBlocks = 8;
//     unsigned int assoc = 2;
//     unsigned int nSets = 4;
//     unsigned int missLatency = 4;
// };


