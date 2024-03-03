#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#include "Processor.hpp"
// #include "Core.hpp"
// #include "Core.cpp"
void Processor::run()
{
    cores[0].init();
    // printf("%p\n", memory);
    cout << "-------Before running-------" << endl;
    cout << left << setw(5) << "REG" << setw(8) << setw(10) << "Core1" << setw(8) << setw(10) << "Core2" << endl;
    for (int i = 0; i < 32; i++)
    {
        cout << left << setw(7) << "X" + to_string(i) << setw(8) << setw(10) << cores[0].reg[i] << setw(8) << setw(10) << cores[1].reg[i] << endl;
    }
    while (cores[0].pc < cores[0].program.size() || cores[0].id.opcode.size() != 0 || cores[0].ex.opcode.size() != 0 || cores[0].mem.opcode.size() != 0)
    {
        cores[0].stagewise_execute(memory, top, 0);
        cores[1].stagewise_execute(memory, top, 0);
        // cores[1].stagewise_execute(memory, top, 1);
        // cores[0].execute(memory, top, 0);
        // cores[1].execute(memory, top, 0);
        // cout << left << setw(5) << "REG" << setw(8) << setw(10) << "Core1" << setw(8) << setw(10) << "Core2" << endl;
        // for (int i = 0; i < 32; i++)
        // {
        //     cout << left << setw(7) << "X" + to_string(i) << setw(8) << setw(10) << cores[0].reg[i] << setw(8) << setw(10) << cores[1].reg[i] << endl;
        // }
    }
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