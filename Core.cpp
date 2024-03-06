#include <bits/stdc++.h>
#include "Core.hpp"
#define ll long long int
using namespace std;
void Core::init()
{
    m["addi"].type = "ari";
    m["add"].type = "ari";
    m["mul"].type = "ari";
    m["sub"].type = "ari";
    m["div"].type = "ari";
    m["li"].type = "ari";
    m["mv"].type = "ari";
    m["lw"].type = "mem";
    m["la"].type = "mem";
    m["sw"].type = "mem1";
    m["bgt"].type = "br";
    m["beq"].type = "br";
    m["bne"].type = "br";
    m["blt"].type = "br";
    m["ble"].type = "br";
    m["bge"].type = "br";
    m["j"].type = "jmp";
    m["jal"].type = "jmp";
    m["j"].latency = 1;
    m["addi"].latency = 1;
    m["add"].latency = 1;
    m["mul"].latency = 1;
    m["sub"].latency = 1;
    m["div"].latency = 1;
    m["li"].latency = 1;
    m["mv"].latency = 1;
    m["lw"].latency = 1;
    m["la"].latency = 1;
    m["sw"].latency = 1;
    m["bgt"].latency = 1;
    m["beq"].latency = 1;
    m["bne"].latency = 1;
    m["blt"].latency = 1;
    m["ble"].latency = 1;
    m["bge"].latency = 1;
}
int Core::regf(string s)
{
    if (s[0] == 'X' || s[0] == 'x')
        return stoi(s.substr(1, s.size()));
    if (s[0] == 'a')
        return stoi(s.substr(1, s.size())) + 10;
    if (s == "s0" || s == "s1")
        return stoi(s.substr(1, s.size())) + 8;
    if (s[0] == 's')
        return stoi(s.substr(1, s.size())) + 16;
    if (s == "tp")
        return 4;
    if (s == "t0" || s == "t1" || s == "t2")
        return stoi(s.substr(1, s.size())) + 5;
    if (s[0] == 't')
        return stoi(s.substr(1, s.size())) + 25;
    return -1;
}
void Core::go_to(vector<string> &parts, string label)
{
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
            if (labels[s] == 0)
                labels[s] = pc + 1;
            if (s == label)
            {
                pc--;
                break;
            }
            pc++;
        }
    }
}
void Core::copy(Registers &rd, Registers rs)
{
    rd.ans = rs.ans;
    rd.label = rs.label;
    rd.latency = rs.latency;
    rd.offset = rs.offset;
    rd.rd1 = rs.rd1;
    rd.rs1 = rs.rs1;
    rd.rs2 = rs.rs2;
    rd.pc = rs.pc;
    rd.opcode = rs.opcode;
}
void Core::reset(Registers &r)
{
    r.ans = -1;
    r.label = "";
    r.latency = 0;
    r.offset = -1;
    r.rd1 = -1;
    r.rs1 = -1;
    r.rs2 = -1;
    r.pc = -1;
    r.opcode = "";
}
bool Core::check_stall(Registers rd)
{
    cout << history.size() << endl;
    for (int i = 0; i < history.size(); i++)
    {
        if (rd.pc == history[i].pc)
        {
            copy(history[i], rd);
            return false;
        }
        else if ((rd.rs1 != -1 && rd.rs1 == history[i].rd1) || (rd.rs2 != -1 && rd.rs2 == history[i].rd1))
        {
            cout << "Opcode:" << history[i].opcode << " rd.rs1:" << rd.rs1 << " rd.rs2:" << rd.rs2 << endl;
            return true;
        }
    }
    return false;
}
void Core::write_back()
{
    if (m[mem.opcode].type == "ari")
    {
        int &rd = reg[mem.rd1];
        rd = mem.ans;
        cout << "Write Back: " << reg[mem.rd1] << endl;
    }
    if (m[mem.opcode].type == "mem")
    {
        if (mem.opcode == "la")
        {
            int &rd = reg[mem.rd1];
            rd = mem.ans;
        }
        if (mem.opcode == "lw")
        {
            int &rd = reg[mem.rd1];
            if (mem.rs1 != -1)
                rd = *((int *)(reg[mem.rs1] + mem.offset));
            else
                rd = variables[mem.label].value;
        }
    }
    reset(mem);
}
void Core::meme(int memory[], int top, int i)
{
    copy(mem, ex);
    if (mem.opcode == "j")
    {
        vector<string> a;
        go_to(a, ex.label);
        pc++;
        cout << "Jumped to:" << pc + 1 << endl;
        cout << "Line:" << program[pc] << endl;
        cout << "Mem.pc:" << mem.pc + 1 << endl;
        if (mem.pc + 1 != pc && mem.pc + 2 != pc)
        {
            reset(id);
            if_reg.parts.clear();
        }
        if (mem.pc + 1 == pc)
        {
            cout << "Jumped to:" << pc + 1 << endl;
            reset(id);
            if_reg.parts.clear();
        }
    }
    if (mem.opcode == "sw")
    {
        int location = mem.rs2;
        cout << location << endl;
        cout << reg[location] << endl;
        location = (reg[location] - (int)memory) / 4;
        int &rd1 = memory[location + mem.offset / 4];
        rd1 = reg[mem.rs1];
    }
    if (mem.opcode == "la")
        mem.ans = variables[mem.label].address;
    reset(ex);
}
void Core::exe()
{
    if (ex.opcode.size() == 0)
    {
        cout << "Hi::";
        copy(ex, id);
        cout << ex.rs1 << " " << ex.rs2 << endl;
        if (m[ex.opcode].type == "br")
        {
            cout << "Branch" << endl;
            // stall(temp);
            vector<string> a;
            if (ex.opcode == "beq" && reg[ex.rs1] == reg[ex.rs2])
            {
                go_to(a, ex.label);
                pc++;
                cout << endl
                     << "Jumped to:" << pc + 1 << endl;
                cout << "Line:" << program[pc] << endl;
            }
            else if (ex.opcode == "bgt" && reg[ex.rs1] > reg[ex.rs2])
            {
                go_to(a, ex.label);
                pc++;
                cout << endl
                     << "Jumped to:" << pc + 1 << endl;
                cout << "Line:" << program[pc] << endl;
            }
            else if (ex.opcode == "bne" && reg[ex.rs1] != reg[ex.rs2])
            {
                go_to(a, ex.label);
                pc++;
                cout << endl
                     << "Jumped to:" << pc + 1 << endl;
                cout << "Line:" << program[pc] << endl;
            }
            else if (ex.opcode == "blt" && reg[ex.rs1] < reg[ex.rs2])
            {
                go_to(a, ex.label);
                pc++;
                cout << endl
                     << "Jumped to:" << pc + 1 << endl;
                cout << "Line:" << program[pc] << endl;
            }
            else if (ex.opcode == "bge" && reg[ex.rs1] >= reg[ex.rs2])
            {
                go_to(a, ex.label);
                pc++;
                cout << endl
                     << "Jumped to:" << pc + 1 << endl;
                cout << "Line:" << program[pc] << endl;
            }
            else if (ex.opcode == "ble" && reg[ex.rs1] <= reg[ex.rs2])
            {
                go_to(a, ex.label);
                pc++;
                cout << endl
                     << "Jumped to:" << pc + 1 << endl;
                cout << "Line:" << program[pc] << endl;
            }
        }
        reset(id);
    }
    cout << "Latency:" << ex.latency << endl;
    if (ex.latency == 1)
    {
        if (ex.opcode == "addi")
        {
            cout << "Source Register:" << reg[ex.rs1] << " x" << ex.rs1 << endl;
            ex.ans += reg[ex.rs1];
        }
        if (ex.opcode == "add")
        {
            cout << "Source registers: " << reg[ex.rs1] << "  " << reg[ex.rs2] << endl;
            ex.ans = reg[ex.rs1] + reg[ex.rs2];
        }
        if (ex.opcode == "sub")
        {
            ex.ans = reg[ex.rs1] - reg[ex.rs2];
        }
        if (ex.opcode == "mul")
        {
            ex.ans = reg[ex.rs1] * reg[ex.rs2];
        }
        if (ex.opcode == "div")
        {
            ex.ans = reg[ex.rs1] / reg[ex.rs2];
        }
        if (ex.opcode == "mv")
        {
            ex.ans = reg[ex.rs1];
        }
    }
    ex.latency--;
}
void Core::id_rf(int memory[], ll &top, int i)
{
    reset(id);
    if (!if_reg.parts.empty())
    {
        id.opcode = if_reg.parts[0];
        cout << "Opcode:" << id.opcode << endl;
        id.pc = if_reg.pc;
    }
    if (id.opcode == ".data")
    {
        // pc++;
        segment = ".data";
        execute(memory, top, i);
        return;
    }
    id.latency = m[id.opcode].latency;
    if (m[id.opcode].type == "jmp")
    {
        if (id.opcode == "j")
        {
            id.label = if_reg.parts[1];
        }
    }
    if (m[id.opcode].type == "mem1")
    {
        // reset(id);
        vector<string> source;
        string s;
        stringstream ss(if_reg.parts[2]);
        while (getline(ss, s, '('))
        {
            source.push_back(s);
        }
        id.offset = stoi(source[0]);
        id.rs1 = regf(if_reg.parts[1]);
        id.rs2 = regf(source[1].substr(0, source[1].size() - 1));
        cout << id.rs1 << " " << id.rs2 << endl;
    }
    if (m[id.opcode].type == "mem")
    {
        if (id.opcode == "la")
        {
            id.label = if_reg.parts[2];
            id.rd1 = regf(if_reg.parts[1]);
            cout << id.rd1 << " " << id.label << endl;
        }
        if (id.opcode == "lw")
        {
            id.rd1 = regf(if_reg.parts[1]);
            if (variables[if_reg.parts[2]].data_type == ".word")
            {
                id.label = if_reg.parts[2];
                // cout << "Hi" << endl;
            }
            else
            {
                vector<string> source;
                string s;
                stringstream ss(if_reg.parts[2]);
                while (getline(ss, s, '('))
                {
                    source.push_back(s);
                }
                id.offset = stoi(source[0]);
                id.rs1 = regf(source[1].substr(0, source[1].size() - 1));
            }
        }
    }
    if (m[id.opcode].type == "ari")
    {
        if (id.opcode == "addi")
        {
            id.ans = stoi(if_reg.parts[3]);
            id.rs1 = regf(if_reg.parts[2]);
            id.rd1 = regf(if_reg.parts[1]);
        }
        else if (id.opcode == "li")
        {
            id.ans = stoi(if_reg.parts[2]);
            id.rd1 = regf(if_reg.parts[1]);
        }
        else if (id.opcode == "mv")
        {
            id.rd1 = regf(if_reg.parts[1]);
            id.rs1 = regf(if_reg.parts[2]);
        }
        else
        {
            id.rs1 = regf(if_reg.parts[2]);
            id.rs2 = regf(if_reg.parts[3]);
            id.rd1 = regf(if_reg.parts[1]);
        }
    }
    if (m[id.opcode].type == "br")
    {
        id.rs1 = regf(if_reg.parts[1]);
        id.rs2 = regf(if_reg.parts[2]);
        id.label = if_reg.parts[3];
    }
    // if (m[id.opcode].type != "br")
    history.push_back(id);
    if_reg.parts.clear();
}
void Core::ins_fetch()
{
    // vector<string> parts;
    string s;
    if (pc >= program.size())
        return;
    // std::cout << "Program counter:" << pc + 1 << endl;
    for (int i = 0; i < program[pc].size(); i++)
    {
        if (program[pc][i] == ',')
            program[pc][i] = ' ';
    }
    stringstream ss(program[pc]);
    while (getline(ss, s, ' '))
    {
        // s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        if (s[s.size() - 1] == ':' && if_reg.parts.size() == 0)
        {
            if (labels[s.substr(0, s.size() - 1)] == 0)
            {
                labels[s.substr(0, s.size() - 1)] = pc + 1;
                std::cout << "The Label \"" << s << "\" is in Line no. " << labels[s.substr(0, s.size() - 1)] << endl;
            }
        }
        else if (s.size() != 0 && s[0] == '#')
            break;
        else if (s != "\0")
        {
            // cout << s << endl;
            if_reg.parts.push_back(s);
        }
    }
    if_reg.pc = pc;
    pc++;
    if (if_reg.parts.size() == 0)
    {
        cout << "Program Counter(Line Empty)" << pc + 1 << endl;
        if_reg.parts.clear();
        ins_fetch();
    }
}
void Core::stall(vector<int> temp)
{

    if (temp.size() != 0)
    {
        for (int i = 0; i < temp.size(); i++)
        {
            for (int j = 0; j < history.size(); j++)
            {
                if (history[j].pc == temp[i])
                {
                    cout << "History Being Erased:" << endl;
                    cout << program[temp[i]] << endl;
                    cout << "History Size:" << history.size() << endl;
                    history.erase(history.begin() + j);
                    break;
                }
            }
        }
    }
    // history.erase(history.begin());
    // if (temp2)
    //     history.erase(history.begin());
}
void Core::stagewise_execute(int memory[], ll &top, int i)
{
    // std::cout << "Size:" << if_reg.parts.size() << endl;
    vector<int> temp;
    int temp2 = 0;
    if (history.size() > 4)
    {
        history.erase(history.begin());
    }
    std::cout << "-----New Clock Cycle-----" << endl;
    cout << "Program Counter:" << pc + 1 << endl;
    cout << "Id:" << id.opcode << " Ex:" << ex.opcode << " Ex-Latency:" << ex.latency << " Mem:" << mem.opcode << endl;
    if (mem.opcode.size() != 0)
    {
        temp.push_back(mem.pc);
        std::cout << "WB" << endl;
        cout << program[mem.pc] << endl;
        write_back();
    }
    // std::cout << "HI" << endl;
    if (ex.opcode.size() != 0)
    {
        if (mem.opcode.size() != 0)
        {
            stall(temp);
            cout << "Hi..Hello" << endl;
            return;
        }
        if (ex.latency == 0)
        {
            cout << "Hi Madhav..." << endl;
            meme(memory, top, i);
            std::cout << "MEM" << endl;
            cout << program[mem.pc] << endl;
            if (m[mem.opcode].type == "mem1")
                temp2 = 1;
            if (mem.opcode == "j")
            {
                if (mem.pc + 2 == pc)
                {
                    cout << "HI>>" << endl;
                    reset(id);
                    stall(temp);
                    pc++;
                    return;
                }
            }
        }
        // if (m[mem.opcode].type == "br")
        // {
        //     stall(temp);
        //     return;
        // }
    }
    // std::cout << "HI1" << endl;
    if (id.opcode.size() != 0 || ex.latency != 0)
    {
        if (ex.opcode.size() != 0)
        {
            if (check_stall(ex))
            {
                cout << "Stall   Hi...." << endl;
                stall(temp);
                return;
            }
        }
        else if (check_stall(id))
        {
            cout << endl
                 << "Stall HI" << endl;
            stall(temp);
            return;
        }
        if (ex.opcode.size() == 0)
            ex.latency = m[ex.opcode].latency;
        if (ex.opcode.size() == 0 || (ex.opcode.size() != 0 && ex.latency > 0))
        {
            exe();
            std::cout << "EX" << endl;
            cout << program[ex.pc] << endl;
            if (m[ex.opcode].type == "br" && m[ex.opcode].latency - 1 == ex.latency)
            {
                if (ex.pc + 1 != pc - 1)
                {
                    cout << "--FLushing Pipeline--" << ex.pc + 1 << " " << pc + 1 << endl;
                    if_reg.parts.clear();
                    stall(temp);
                    return;
                }
            }
        }
        else if (ex.opcode.size() != 0)
        {
            stall(temp);
            return;
        }
    }
    // std::cout << "HI2" << endl;
    // std::cout << "Size:" << if_reg.parts.size() << endl;
    if (if_reg.parts.size() != 0)
    {
        // std::cout << "HI" << endl;
        if (id.opcode.size() != 0)
        {
            stall(temp);
            return;
        }
        if (ex.opcode == "j" && pc == ex.pc)
        {
            stall(temp);
            return;
        }

        id_rf(memory, top, i);
        std::cout << "ID" << endl;
        // if(m[id.opcode].type=="br")
        // {
        //     stall(temp);
        //     return;
        // }
    }
    if (pc < program.size())
    {
        ins_fetch();
        if (if_reg.parts.size() != 0 && if_reg.parts[0] == ".data")
        {
            // pc++;
            cout << "HI Madhav" << endl;
            segment = ".data";
            execute(memory, top, i);
            // if_reg.parts.clear();
            ins_fetch();
        }
        std::cout << "Size:" << if_reg.parts.size() << endl;
        // std::cout << "Program Counter:" << pc << endl;
        std::cout << "IF" << endl;
        cout << program[if_reg.pc] << endl;
    }
    stall(temp);
}
void Core::execute(int memory[], ll &top, int i)
{
    vector<string> parts;
    string s;
    if (pc >= program.size())
        return;
    // std::cout << "Program counter:" << pc + 1 << endl;
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
                // std::cout << "The Label \"" << s << "\" is in Line no. " << labels[s.substr(0, s.size() - 1)] << endl;
            }
        }
        else if (s != "\0")
            parts.push_back(s);
    }
    // for (auto i : parts)
    // {
    //     std::cout << i << endl;
    // }
    // std::cout << endl;
    string opcode = "";
    if (!parts.empty())
        opcode = parts[0];
    if (opcode == ".text")
    {
        segment = ".text";
        pc++;
        std::cout << "--------------------------------Memory---------------------------------" << endl;
        for (int i = 0; i < 40; i++)
        {
            std::cout << memory[i] << " ";
        }
        std::cout << endl;
        cout << ".Text begins form here" << endl;
        if_reg.parts.clear();
        return;
    }
    if (opcode == ".data")
    {
        pc++;
        segment = ".data";
        execute(memory, top, i);
        return;
    }
    else if (segment == ".data")
    {
        // for (int i = 0; i < parts.size(); i++)
        // {
        //     cout << parts[i] << endl;
        // }
        // cout << "Hello madhav" << parts[0][parts[0].size() - 1] << endl;
        if (!parts.empty() && parts[0][parts[0].size() - 1] == ':')
        {
            int n = parts.size();
            ll m = top;
            Variable_p a;
            a.address = (int)(memory + top);
            parts[0] = parts[0].substr(0, parts[0].size() - 1);
            a.data_type = parts[1];
            if (parts[1] == ".word")
            {
                for (int i = top; i < m + n - 2; i++)
                {
                    memory[i] = stoi(parts[i - m + 2]);
                    cout << memory[i] << " ";
                    // cout << "top:" << top << endl;
                    top++;
                }
                // cout << endl;
                a.value = stoi(parts[2]);
                variables[parts[0]] = a;
                // cout << *((int *)a.address) << " " << a.address << " " << a.size << " " << a.data_type << endl;
                // cout << "Hi" << endl;
                a.size = 4;
            }
            else if (parts[1] == ".string")
            {
                for (int i = 3; i < parts.size(); i++)
                {
                    if (parts[i][0] == '#')
                        break;
                    parts[2] += " " + parts[i];
                    // cout << parts[2] << endl;
                }
                parts[2] = parts[2].substr(1, parts[2].size() - 2);
                // cout << "String:" << parts[2] << endl;
                parts[2] += "\0";
                // parts[2] = parts[2].substr(1, parts[2].size() - 2);
                int count = top * 4 + (ll)memory;
                char t = '\n';
                // cout << t;
                for (int i = top * 4 + (ll)memory; i < top * 4 + (ll)memory + parts[2].size(); i++)
                {
                    // cout << parts[2][i - top * 4 - (ll)memory] << " ";
                    if (parts[2][i - top * 4 - (ll)memory] == '\\')
                    {
                        t = '\\';
                        // cout << "Hello:"<< (int)('\\') << endl;
                        continue;
                    }
                    if (t == '\\')
                    {
                        if (parts[2][i - top * 4 - (ll)memory] == 'n')
                            parts[2][i - top * 4 - (ll)memory] = '\n';
                        // cout << "Appeared:" << parts[2][i - top * 4 - (ll)memory]<<(int)parts[2][i - top * 4 - (ll)memory] << endl;
                        t = ' ';
                    }
                    *((char *)count) = (int)(parts[2][i - top * 4 - (ll)memory]);
                    count++;
                }
                // cout << "------------" << endl;
                a.address = (int)(memory + top);
                a.data_type = parts[1];
                variables[parts[0]] = a;
                top += ceil(parts[2].size() / (double)4) + 1;
            }
        }
        pc++;
        execute(memory, top, i);
        return;
    }
    else if (opcode == "mv")
    {
        int &rd1 = reg[regf(parts[1])];
        int rs1 = reg[regf(parts[2])];
        rd1 = rs1;
        // cout << reg[stoi(parts[1].substr(1, parts[1].size()))] << endl;
    }
    else if (opcode == "la")
    {
        // cout << "Program Counter:" << pc + 1 << endl;
        // int &rd1 = reg[stoi(parts[1].substr(1, parts[1].size()))];
        int &rd1 = reg[regf(parts[1])];
        string rs1 = parts[2];
        rd1 = variables[rs1].address;
        // cout << variables[rs1].data_type;
        // cout << "load address: " << rd1 << endl;
    }
    else if (opcode == "add" || opcode == "addi")
    {
        int rs1 = reg[regf(parts[2])];
        int rs2;
        if (opcode == "add")
            rs2 = reg[regf(parts[3])];
        else
            rs2 = stoi(parts[3]);
        int &rd1 = reg[regf(parts[1])];
        rd1 = rs1 + rs2;
        // cout << "Addition in progress" << endl;
    }
    else if (opcode == "sub")
    {
        int rs1 = reg[regf(parts[2])];
        int rs2 = reg[regf(parts[3])];
        int &rd1 = reg[regf(parts[1])];
        rd1 = rs1 - rs2;
    }
    else if (opcode == "mul")
    {
        int rs1 = reg[regf(parts[2])];
        int rs2 = reg[regf(parts[3])];
        int &rd1 = reg[regf(parts[1])];
        rd1 = rs1 * rs2;
    }
    else if (opcode == "div")
    {
        int rs1 = reg[regf(parts[2])];
        int rs2 = reg[regf(parts[3])];
        int &rd1 = reg[regf(parts[1])];
        rd1 = rs1 / rs2;
    }
    else if (opcode == "li")
    {
        // cout << parts[2] << endl;
        int rs1 = stoi(parts[2]);
        int &rd1 = reg[regf(parts[1])];
        rd1 = rs1;
    }
    else if (opcode == "lw")
    {
        // cout << "Program counter:" << pc + 1 << endl;
        vector<string> source;
        string s;
        stringstream ss(parts[2]);
        int &rd1 = reg[regf(parts[1])];
        if (variables[parts[2]].data_type == ".word")
        {
            rd1 = variables[parts[2]].value;
            // cout << "Hi" << endl;
        }
        else
        {
            while (getline(ss, s, '('))
            {
                source.push_back(s);
            }
            int offset = stoi(source[0]);
            int location = reg[regf(source[1].substr(0, source[1].size() - 1))];
            // cout << offset << " " << location << endl;
            // cout << "Source:"<<regf(source[1].substr(0, source[1].size() - 1)) << endl;
            // cout << "Location:" << location << endl;
            int rs1 = *((int *)(location + offset));
            // cout << "HI" << endl;
            rd1 = rs1;
            // cout << "HI" << endl;
        }
        // cout << "Load Word:" << rd1 << endl;
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
        int location = regf(source[1].substr(0, source[1].size() - 1));
        // cout << offset << " " << location << endl;
        location = (reg[location] - (int)memory) / 4;
        // cout << "location:" << location + offset / 4 << endl;
        int &rd1 = memory[location + offset / 4];
        int rs1 = reg[regf(parts[1])];
        // cout << rs1 << endl;
        rd1 = rs1;
    }
    else if (opcode == "bne")
    {
        int rs1 = reg[regf(parts[1])];
        int rs2 = reg[regf(parts[2])];
        // cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 != rs2)
        {
            string label = parts[3];
            go_to(parts, label);
        }
    }
    else if (opcode == "beq")
    {
        int rs1 = reg[regf(parts[1])];
        int rs2 = reg[regf(parts[2])];
        // cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 == rs2)
        {
            string label = parts[3];
            go_to(parts, label);
        }
    }
    else if (opcode == "bge")
    {
        int rs1 = reg[regf(parts[1])];
        int rs2 = reg[regf(parts[2])];
        // cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 >= rs2)
        {
            string label = parts[3];
            go_to(parts, label);
        }
    }
    else if (opcode == "ble")
    {
        int rs1 = reg[regf(parts[1])];
        int rs2 = reg[regf(parts[2])];
        // cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 <= rs2)
        {
            string label = parts[3];
            go_to(parts, label);
        }
    }
    else if (opcode == "blt")
    {
        int rs1 = reg[regf(parts[1])];
        int rs2 = reg[regf(parts[2])];
        // cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 < rs2)
        {
            string label = parts[3];
            go_to(parts, label);
        }
    }
    else if (opcode == "bgt")
    {
        int rs1 = reg[regf(parts[1])];
        int rs2 = reg[regf(parts[2])];
        // cout << "rs1:" << rs1 << " rs2:" << rs2 << endl;
        if (rs1 > rs2)
        {
            string label = parts[3];
            go_to(parts, label);
        }
    }
    else if (opcode == "jal")
    {
        rec.push(pc + 1);
        reg[regf(parts[1])] = pc + 1;
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
        // cout << "Program Counter:" << pc + 1 << endl;
        string label = parts[1];
        go_to(parts, label);
    }
    else if (opcode == "ecall")
    {
        // cout <<"Program Counter:"<< pc << endl;
        if (reg[17] == 1)
        {
            cout << reg[10];
        }
        if (reg[17] == 4)
        {
            // cout << "Program counter:" << pc << endl;
            int p = reg[10];
            while ((char)*((char *)p) != '\0')
            {
                cout << (char)*((char *)p);
                // cout << "Program counter:" << pc+1 << endl;
                p++;
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