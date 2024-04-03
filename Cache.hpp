#include <bits/stdc++.h>
#include <list>
#include <vector>
using namespace std;
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
    unsigned int cacheSize;
    unsigned int blockSize = 8;
    unsigned int numBlocks = 8;
    unsigned int assoc = 2;
    unsigned int nSets = 4;
    unsigned int missLatency = 4;
};