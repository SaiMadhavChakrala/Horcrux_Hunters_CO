#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#include "Processor.hpp"
void Processor::run(int d)
{
    // cache.init_cache();
    cout << log2(cache.nSets) << endl;
    for (int i = 0; i < cache.nSets; i++)
    {
        list<Tag> x;
        cache.set.push_back(x);
    }
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
            cores[0].stagewise_execute(memory, top, d, cache,0);
        if (cores[1].if_reg.parts.size() != 0 || cores[1].pc < cores[1].program.size() || cores[1].id.opcode.size() != 0 || cores[1].ex.opcode.size() != 0 || cores[1].mem.opcode.size() != 0)
            cores[1].stagewise_execute(memory, top, d, cache,1);
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
        //         cout << j.address << " " << *((int *)j.address) << endl;
        //     }
        // }
        // cout << endl;
    }
    cout << "--------------Core:1---------------" << endl;
    cout << "Total No.of Cycles   : " << cores[0].clock << endl;
    cout << "Instructions Executed: " << cores[0].n_ins << endl;
    cout << "IPC                  : " << ((double)cores[0].n_ins / cores[0].clock) << endl;
    cout << "CPI                  : " << ((double)cores[0].clock / cores[0].n_ins) << endl;
    cout << "--------------Core:2---------------" << endl;
    cout << "Total No.of Cycles   : " << cores[1].clock << endl;
    cout << "Instructions Executed: " << cores[1].n_ins << endl;
    cout << "IPC                  : " << ((double)cores[1].n_ins / cores[1].clock) << endl;
    cout << "CPI                  : " << ((double)cores[1].clock / cores[1].n_ins) << endl;
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
}
