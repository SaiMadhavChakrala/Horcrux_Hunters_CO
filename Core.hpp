#pragma once
#include <bits/stdc++.h>
#define ll long long int
using namespace std;

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
};