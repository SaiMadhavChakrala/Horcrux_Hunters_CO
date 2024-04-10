#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#include "Processor.hpp"
void Processor::writeCSV(const vector<vector<string>> &data, const string &filename, int i)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    file << "Ins\\Clock"
         << ",";
    for (int i = 0; i < data.size(); i++)
    {
        file << i << ",";
    }
    file << endl;
    for (size_t col = 0; col < data[data.size() - 1].size(); ++col)
    {
        file << cores[i].program[col] << ",";
        for (size_t row = 0; row < data.size(); ++row)
        {
            file << data[row][col];
            if (row != data.size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }
    file.close();
}
void Processor::writeCSV1(const vector<vector<string>> &data, const string &filename, int i)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    file << "Ins\\Clock"
         << ",";
    for (int i = 0; i < data.size(); i++)
    {
        file << i << ",";
    }
    file << endl;
    for (size_t col = 0; col < data[data.size() - 1].size(); ++col)
    {
        file << cores[i].program[col] << ",";
        for (size_t row = 0; row < data.size(); ++row)
        {
            file << data[row][col];
            if (row != data.size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }
    file.close();
}
void Processor::run(int d, int policy)
{
    // cache.init_cache();
    cout << log2(cache.nSets) << endl;
    for (int i = 0; i < cache.nSets; i++)
    {
        list<Tag> x;
        cache.set.push_back(x);
    }
    cout << cache.set.size() << endl;
    cout << "-------Before running-------" << endl;
    cout << left << setw(5) << "REG" << setw(8) << setw(10) << "Core1" << setw(8) << setw(10) << "Core2" << endl;
    for (int i = 0; i < 32; i++)
    {
        cout << left << setw(7) << "X" + to_string(i) << setw(8) << setw(10) << cores[0].reg[i] << setw(8) << setw(10) << cores[1].reg[i] << endl;
    }
    ll i = 1;
    cout << endl;
    if (d == 0)
        cout << "------Data Forwarding Enabled-------" << endl;
    else
        cout << "------Data Forwarding Disabled-------" << endl;
    cout << endl;
    while (cores[1].pc < cores[1].program.size() || cores[1].if_reg.parts.size() != 0 || cores[1].id.opcode.size() != 0 || cores[1].ex.opcode.size() != 0 || cores[1].mem.opcode.size() != 0 || cores[0].if_reg.parts.size() != 0 || cores[0].pc < cores[0].program.size() || cores[0].id.opcode.size() != 0 || cores[0].ex.opcode.size() != 0 || cores[0].mem.opcode.size() != 0)
    {
        if (cores[0].if_reg.parts.size() != 0 || cores[0].pc < cores[0].program.size() || cores[0].id.opcode.size() != 0 || cores[0].ex.opcode.size() != 0 || cores[0].mem.opcode.size() != 0)
            cores[0].stagewise_execute(memory, top, d, cache, 0, policy);
        if (cores[1].if_reg.parts.size() != 0 || cores[1].pc < cores[1].program.size() || cores[1].id.opcode.size() != 0 || cores[1].ex.opcode.size() != 0 || cores[1].mem.opcode.size() != 0)
            cores[1].stagewise_execute(memory, top, d, cache, 1, policy);
        // cout << left << setw(5) << "REG" << setw(8) << setw(10) << "Core1" << setw(8) << setw(10) << "Core2" << endl;
        // for (int i = 0; i < 32; i++)
        // {
        //     cout << left << setw(7) << "X" + to_string(i) << setw(8) << setw(10) << cores[0].reg[i] << setw(8) << setw(10) << cores[1].reg[i] << endl;
        // }
        // cout << "--------------------------------Memory---------------------------------" << endl;
        // for (int i = 0; i < 40; i++)
        // {
        //     cout << memory[i] << " ";
        // }
        // cout << endl;
        // cout << "-----Cache-----" << endl;
        // for (int i = 0; i < cache.nSets; i++)
        // {
        //     cout << "index:" << i << endl;
        //     for (auto j : cache.set[i])
        //     {
        //         // if (j.core == -1)
        //         //     cout << j.address << " " << *((int *)j.address) << endl;
        //         // else
        //         //     cout << j.address << " Core:" << j.core << endl;
        //         cout << j.address << " Core:" << j.core << endl;
        //     }
        // }
        // cout << endl;
    }
    cout << "--------------Core:1---------------" << endl;
    cout << "Total No.of Cycles   : " << cores[0].clock << endl;
    cout << "Instructions Executed: " << cores[0].n_ins << endl;
    cout << "IPC                  : " << ((double)cores[0].n_ins / cores[0].clock) << endl;
    cout << "CPI                  : " << ((double)cores[0].clock / cores[0].n_ins) << endl;
    cout << "Cache Misses         : " << cores[0].cache_miss << "+" << cores[0].if_miss << endl;
    cout << "Cache Hits           : " << cores[0].hits << "+" << cores[0].if_hit << endl;
    cout << "--------------Core:2---------------" << endl;
    cout << "Total No.of Cycles   : " << cores[1].clock << endl;
    cout << "Instructions Executed: " << cores[1].n_ins << endl;
    cout << "IPC                  : " << ((double)cores[1].n_ins / cores[1].clock) << endl;
    cout << "CPI                  : " << ((double)cores[1].clock / cores[1].n_ins) << endl;
    cout << "Cache Misses         : " << cores[1].cache_miss << "+" << cores[1].if_miss << endl;
    cout << "Cache Hits           : " << cores[1].hits << "+" << cores[1].if_hit << endl;
    cout << endl;
    cout << "Total Cache Acesses  : " << cores[1].if_hit + cores[0].if_hit + cores[0].hits + cores[1].hits + cores[0].cache_miss + cores[1].cache_miss << endl;
    cout << "Total Cache Misses   : " << cores[1].cache_miss + cores[0].cache_miss + cores[1].if_miss + cores[0].if_miss << endl;
    cout << "Miss Rate            : " <<((cores[1].cache_miss + cores[0].cache_miss + cores[1].if_miss + cores[0].if_miss)/(double)(cores[1].if_hit + cores[0].if_hit + cores[0].hits + cores[1].hits + cores[0].cache_miss + cores[1].cache_miss)) <<endl;
    string s = "";
    std::ofstream outFile("output.txt");
    for (int i = 0; i < 32; i++)
    {
        s.append(to_string(cores[0].reg[i]));
        s.append("\n");
    }
    if (outFile.is_open())
    {
        outFile << s << std::endl;
        outFile.close();
    }
    else
    {
        std::cerr << "Error opening output.txt" << std::endl;
    }
    s = "";
    std::ofstream out("data.txt");
    for (int i = 0; i < 32; i++)
    {
        s.append(to_string(cores[1].reg[i]));
        s.append("\n");
    }
    if (out.is_open())
    {
        out << s << std::endl;
        out.close();
    }
    else
    {
        std::cerr << "Error opening output.txt" << std::endl;
    }
    cout << endl
         << "---------After Running---------" << endl;
    cout << left << setw(5) << "REG" << setw(8) << setw(10) << "Core1" << setw(8) << setw(10) << "Core2" << endl;
    for (int i = 0; i < 32; i++)
    {
        cout << left << setw(7) << "X" + to_string(i) << setw(8) << setw(10) << cores[0].reg[i] << setw(8) << setw(10) << cores[1].reg[i] << endl;
    }
    cout << "--------------------------------Memory---------------------------------" << endl;
    for (int i = 0; i < 40; i++)
    {
        cout << memory[i] << " ";
    }
    cout << endl;
    writeCSV1(cores[1].pipeline, "out2.csv", 1);
    writeCSV(cores[0].pipeline, "out1.csv", 0);
}
