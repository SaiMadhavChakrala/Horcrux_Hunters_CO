#include "header.hpp"
class Tag
{
public:
    int core = -1;
    int address;
};
class Cache
{
public:
    vector<list<Tag>> set;
    unsigned int cacheSize=512;
    unsigned int blockSize = 16;
    unsigned int numBlocks = 32;
    unsigned int assoc = 32;
    unsigned int nSets = 1;
    unsigned int missLatency = 1;
};