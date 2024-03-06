#pragma once
#include <bits/stdc++.h>
#define ll long long int
using namespace std;
class IF
{
public:
    vector<string> parts;
    void split(int memory, ll &top, int i);
    int pc=-1;
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
    void stagewise_execute(int memory[], ll &top, int ind);
    void write_back(int ind);
    void meme(int memory[], int top, int ind);
    void exe(int ind);
    void id_rf(int memory[], ll &top, int ind);
    void ins_fetch();
    void reset(Registers &r);
    void copy(Registers &rd, Registers rs);
    bool check_stall(Registers r);
    void stall(vector<int> temp);
    void rev_HisDelete(int temp);
};