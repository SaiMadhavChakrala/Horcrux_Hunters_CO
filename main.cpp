#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define f(i, a, n) for (ll i = a; i < n; i++)
#define rf(i, n, a) for (ll i = n - 1; i >= a; i--)
#define pb push_back
#define pii pair<int, int>
class Core
{
public:
    int reg[32];

    int pc = 0;
    vector<string> program;
    map<string, int> labels;
    void execute(int memory[]);
};
void Core::execute(int memory[])
{
    vector<string> parts;
    string s;
    if(pc>=program.size())
        return;
    stringstream ss(program[pc]);
    while (getline(ss, s, ' '))
    {
        // s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        if (s[s.size() - 1] == ':' && parts.size() == 0)
        {
            if (labels[s.substr(0,s.size()-1)] == 0)
            {
                labels[s.substr(0,s.size()-1)] = pc + 1;
                cout << "The Label \"" << s << "\" is in Line no. " << labels[s] << endl;
            }
        }
        else if (s != "\0")
            parts.push_back(s);
    }
    // for (auto i : parts)
    // {
    //     cout << j << ":" << i << endl;
    //     j++;
    // }
    // cout << j << "th time" << endl;
    // j++;
    string opcode = parts[0];
    if (opcode == "ADD" || opcode == "ADDI")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2;
        if (opcode == "ADD")
            rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        else
            rs2 = stoi(parts[3]);
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 + rs2;
        cout << "Addition in progress" << endl;
    }
    else if (opcode == "SUB")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 - rs2;
    }
    else if (opcode == "MUL")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 * rs2;
    }
    else if (opcode == "DIV")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 / rs2;
    }
    else if (opcode == "LI")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1;
    }
    else if (opcode == "LW")
    {
        vector<string> source;
        string s;
        stringstream ss(parts[2]);
        while (getline(ss, s, '('))
        {
            source.push_back(s);
        }
        int offset = stoi(source[0]);
        int location = stoi(source[1].substr(1, source[1].size() - 1));
        cout << offset << " " << location << endl;
        int rs1 = memory[offset + location];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1;
    }
    else if (opcode == "SW")
    {
        vector<string> source;
        string s;
        stringstream ss(parts[2]);
        while (getline(ss, s, '('))
        {
            source.push_back(s);
        }
        int offset = stoi(source[0]);
        int location = stoi(source[1].substr(1, source[1].size() - 1));
        cout << offset << " " << location << endl;
        int &rd1 = memory[offset + location];
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1;
    }
    else if (opcode == "BNE")
    {
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int rs2 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 != rs2)
        {
            string label = parts[3];
            cout << labels[parts[3]]<< endl;
            if (labels[label] != 0)
            {
                pc = labels[label] - 2;
            }
            else
            {
                int j;
                while (pc < program.size())
                {
                    string s = "";
                    for (j = 0; j < program[pc].size(); j++)
                    {
                        if (program[pc][j] == ':')
                        {
                            break;
                        }
                    }
                    for (int k = 0; k < j; k++)
                    {
                        if (program[pc][k] != ' ')
                        {
                            s += program[pc][k];
                        }
                    }
                    if (s == label)
                    {
                        pc--;
                        break;
                    }
                    pc++;
                }
            }
        }
    }
    pc += 1;
}
class Processor
{
public:
    int memory[4096] = {0};
    int clock = 0;
    Core cores[2];
    void run()
    {
        while(cores[0].pc<cores[0].program.size()||cores[1].pc<cores[1].program.size())
        {
            cores[0].execute(memory);
            cores[1].execute(memory);
        }
    }
};
int main()
{
    Processor sim;
    sim.cores[0].reg[1] = 0;
    sim.cores[0].reg[3] = 5;
    sim.cores[0].program.push_back("Loop:  ADDI X1 X1 1");
    sim.cores[0].program.push_back("BNE X1 X3 Loop");
    sim.run();
    return 0;
}