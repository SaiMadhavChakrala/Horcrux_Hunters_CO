#pragma once
#include <bits/stdc++.h>
#include "Cache.hpp"
// #include "Processor.hpp"
#define ll long long int
using namespace std;
class IF
{
public:
    vector<string> parts;
    void split(int memory, ll &top, int i);
    int pc = -1;
    int latency = 0;
};
class Registers
{
public:
    int rs1, rs2, rd1, offset, ans, latency = 0, pc;
    string label;
    string opcode = "";
};
class Instruction
{
public:
    string type = "";
    ll latency = 0;
};
struct Variable_p
{
    int address;
    string data_type;
    int value;
    int size;
};
class Core
{
public:
    Registers id, ex, mem;
    IF if_reg;
    long long int n_ins = 0, clock = 0;
    int reg[32] = {0};
    int pc = 0;
    vector<string> program;
    string segment = ".text";
    map<string, Variable_p> variables;
    map<ll, string> address_datatype;
    map<string, int> labels;
    void execute(int memory[], ll &top, int i);
    void go_to(vector<string> &parts, string label);
    stack<int> rec;
    int regf(string s);
    map<string, Instruction> m;
    vector<Registers> history;
    void init();
    void stagewise_execute(int memory[], ll &top, int ind, Cache &cache);
    void write_back(int ind);
    void meme(int memory[], int top, int ind,Cache &cache);
    void exe(int ind);
    void id_rf(int memory[], ll &top, int ind);
    void ins_fetch();
    void reset(Registers &r);
    void copy(Registers &rd, Registers rs);
    bool check_stall(Registers r);
    bool check_hazard(Registers a, Registers b);
    void stall(vector<int> temp);
    void rev_HisDelete(int temp);
};
