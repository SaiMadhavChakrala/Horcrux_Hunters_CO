#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define f(i, a, n) for (ll i = a; i < n; i++)
#define rf(i, n, a) for (ll i = n - 1; i >= a; i--)
#define pb push_back
#define pii pair<int, int>
class Variable_p
{
public:
    int address;
    int value;
    string data_type;
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
    void execute(int memory[], ll &top);
    void go_to(vector<string> &parts,string label);
    stack<int> rec;
};
void Core::go_to(vector<string> &parts,string label)
{
    // string label = parts[3];
    // cout << labels[parts[3]] << endl;
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
void Core::execute(int memory[], ll &top)
{
    vector<string> parts;
    string s;
    if (pc >= program.size())
        return;
    cout << "Program counter:" << pc + 1 << endl;
    for (int i = 0; i < program[pc].size(); i++)
    {
        if (program[pc][i] == ',')
            program[pc][i] = ' ';
    }
    stringstream ss(program[pc]);
    while (getline(ss, s, ' '))
    {
        // s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        if (s[s.size() - 1] == ':' && parts.size() == 0 && segment == ".text")
        {
            if (labels[s.substr(0, s.size() - 1)] == 0)
            {
                labels[s.substr(0, s.size() - 1)] = pc + 1;
                cout << "The Label \"" << s << "\" is in Line no. " << labels[s.substr(0, s.size() - 1)] << endl;
            }
        }
        else if (s != "\0")
            parts.push_back(s);
    }
    for (auto i : parts)
    {
        cout << i << endl;
    }
    cout << endl;
    string opcode = "";
    if (!parts.empty())
        opcode = parts[0];
    if (opcode == ".text")
    {
        segment = ".text";
        pc++;
        return;
    }
    if (opcode == ".data")
    {
        pc++;
        segment = ".data";
        execute(memory, top);
        return;
    }
    else if (segment == ".data")
    {
        for (int i = 0; i < parts.size(); i++)
        {
            cout << parts[i] << endl;
        }
        cout << "Hello madhav" << parts[0][parts[0].size() - 1] << endl;
        if (!parts.empty() && parts[0][parts[0].size() - 1] == ':')
        {
            int n = parts.size();
            ll m = top;
            Variable_p a;
            a.address = (int)(memory + top);
            for (int i = top; i < m + n - 2; i++)
            {
                memory[i] = stoi(parts[i - m + 2]);
                cout << memory[i] << " ";
                cout << "top:" << top << endl;
                top++;
            }
            cout << endl;
            parts[0] = parts[0].substr(0, parts[0].size() - 1);
            a.data_type = parts[1];
            if (parts[1] == ".word")
                a.size = 4;
            a.value = stoi(parts[2]);
            variables[parts[0]] = a;
            cout << *((int *)a.address) << " " << a.address << " " << a.size << " " << a.data_type << endl;
            cout << "Hi" << endl;
        }
        pc++;
        execute(memory, top);
    }
    else if (opcode == "mv")
    {
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        rd1 = rs1;
        cout << reg[stoi(parts[1].substr(1, parts[1].size()))] << endl;
    }
    else if (opcode == "la")
    {
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        string rs1 = parts[2];
        rd1 = variables[rs1].address;
        cout << "load address" << rd1 << endl;
    }
    else if (opcode == "add" || opcode == "addi")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2;
        if (opcode == "add")
            rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        else
            rs2 = stoi(parts[3]);
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 + rs2;
        cout << "Addition in progress" << endl;
    }
    else if (opcode == "sub")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 - rs2;
    }
    else if (opcode == "mul")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 * rs2;
    }
    else if (opcode == "div")
    {
        int rs1 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        int rs2 = reg[stoi(parts[3].substr(1, parts[3].size()))];
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1 / rs2;
    }
    else if (opcode == "li")
    {
        cout << parts[2] << endl;
        int rs1 = stoi(parts[2]);
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1;
    }
    else if (opcode == "lw")
    {
        vector<string> source;
        string s;
        stringstream ss(parts[2]);
        while (getline(ss, s, '('))
        {
            source.push_back(s);
        }
        int offset = stoi(source[0]);
        int location = reg[stoi(source[1].substr(1, source[1].size() - 1))];
        cout << offset << " " << location << endl;
        cout << "Location:" << location << endl;
        int rs1 = *((int *)(location + offset));
        int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        rd1 = rs1;
        cout << "Load Word:" << rd1 << endl;
    }
    else if (opcode == "sw")
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
        location = (reg[location] - (int)memory) / 4;
        cout << "location:" << location + offset / 4 << endl;
        int &rd1 = memory[location + offset / 4];
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        cout << rs1 << endl;
        rd1 = rs1;
    }
    else if (opcode == "bne")
    {
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int rs2 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 != rs2)
        {
            string label = parts[3];
            go_to(parts,label);
        }
    }
    else if (opcode == "beq")
    {
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int rs2 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 == rs2)
        {
            string label = parts[3];
            go_to(parts,label);
        }
    }
    else if (opcode == "blt")
    {
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int rs2 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 < rs2)
        {
            string label = parts[3];
            go_to(parts,label);
        }
    }
    else if (opcode == "bgt")
    {
        int rs1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int rs2 = reg[stoi(parts[2].substr(1, parts[2].size()))];
        cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 > rs2)
        {
            string label = parts[3];
            go_to(parts,label);
        }
    }
    else if (opcode == "jal")
    {
        rec.push(pc + 1);
        reg[stoi(parts[1].substr(1, parts[1].size()))] = pc + 1;
        string label = parts[2];
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
    else if (opcode == "ret")
    {
        if (!rec.empty())
        {
            pc = rec.top() - 1;
            rec.pop();
        }
    }
    else if (opcode == "j")
    {
        string label = parts[1];
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
    pc += 1;
    if (pc >= program.size() && !rec.empty())
    {
        pc = rec.top();
        rec.pop();
    }
}
class Processor
{
public:
    int memory[4096] = {0};
    int clock = 0;
    Core cores[2];
    ll top = 0;
    void upload(Core cores[]);
    void run()
    {
        printf("%p\n", memory);
        cout << "--------------Before running----------" << endl;
        for (int i = 0; i < 32; i++)
        {
            cout << "X" << i << "    " << cores[0].reg[i] << endl;
        }
        while (cores[0].pc < cores[0].program.size() || cores[1].pc < cores[1].program.size())
        {
            cores[0].execute(memory, top);
            cores[1].execute(memory, top);
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
        cout << "--------------After Running---------------" << endl;
        cout<<"   Core1 "<<"    Core2"<<endl;
        for (int i = 0; i < 32; i++)
        {
            cout << "X" << i << "    " << cores[0].reg[i]<<"  "<<cores[1].reg[i] << endl;
        }
        cout << "-------------Memory----------------" << endl;
        for (int i = 0; i < 40; i++)
        {
            cout << memory[i] << " ";
        }
        cout << endl;
    }
};
int main()
{
    Processor sim;
    std::string filepath = "./Testfile[1].txt";
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filepath << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        sim.cores[0].program.push_back(line);
        // cout << line << endl;
    }
    file.close();
    std::string filepath2 = "./Testfile[2].txt";
    std::ifstream file2(filepath2);
    if (!file2.is_open())
    {
        std::cerr << "Unable to open file: " << filepath2 << std::endl;
        return 1;
    }
    std::string line2;
    while (std::getline(file2, line2))
    {
        sim.cores[1].program.push_back(line2);
        // cout << line << endl;
    }
    sim.run();
    string s = "";

    file2.close();

    return 0;
}