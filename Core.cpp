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
void Core::rev_HisDelete(int temp)
{
    for (int i = history.size() - 1; i >= 0; i--)
    {
        if (temp == history[i].pc)
        {
            history.erase(history.begin() + i);
        }
    }
}
bool Core::check_stall(Registers rd)
{
    // cout << "PC to be removed:" << rd.pc << endl;
    // cout << "History Size:" << history.size() << endl;
    for (int i = 0; i < history.size(); i++)
    {
        if (rd.pc == history[i].pc)
        {
            copy(history[i], rd);
            return false;
        }
        else if ((rd.rs1 != -1 && rd.rs1 == history[i].rd1) || (rd.rs2 != -1 && rd.rs2 == history[i].rd1))
        {
            // cout << history[i].pc << ":" << program[history[i].pc] << endl;
            return true;
        }
    }
    return false;
}
bool Core::check_hazard(Registers a, Registers b)
{
    if (a.rd1 == -1)
        return false;
    if (a.rd1 == b.rd1)
        return true;
    if (a.rd1 == b.rs1)
        return true;
    if (a.rd1 == b.rs2)
        return true;
    return false;
}
void Core::write_back(int ind)
{
    if (ind)
    {
        if (m[mem.opcode].type == "ari")
        {
            int &rd = reg[mem.rd1];
            rd = mem.ans;
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
    }
    reset(mem);
}
void Core::meme(int memory[], int top, int ind, Cache &cache)
{
    if (ind)
    {
        copy(mem, ex);
        if (mem.opcode == "j")
        {
            vector<string> a;
            go_to(a, ex.label);
            pc++;
            if (mem.pc + 1 != pc && mem.pc + 2 != pc)
            {
                rev_HisDelete(id.pc);
                reset(id);
                if_reg.parts.clear();
            }
            if (mem.pc + 1 == pc)
            {
                rev_HisDelete(id.pc);
                reset(id);
                if_reg.parts.clear();
            }
        }
        if (mem.opcode == "sw")
        {
            int location = mem.rs2;
            location = (reg[location] - (int)memory) / 4;
            int &rd1 = memory[location + mem.offset / 4];
            rd1 = reg[mem.rs1];
        }
        if (mem.opcode == "la")
            mem.ans = variables[mem.label].address;
        reset(ex);
    }
    else
    {
        if (mem.opcode.size() == 0)
        {
            copy(mem, ex);
            if (mem.opcode == "lw")
            {
                int addr;
                if (mem.rs1 != -1)
                    addr = (int)(reg[mem.rs1] + mem.offset);
                else
                    addr = variables[mem.label].address;
                int p = (addr >> (int)log2(cache.blockSize));
                int x = log2(cache.nSets);
                x = (1 << x) - 1;
                x = x & p;
                Tag tag;
                tag.address = addr;
                list<Tag>::iterator ptr = cache.set[x].end();
                for (auto i = cache.set[x].begin(); i != cache.set[x].end(); i++)
                {
                    if ((*i).address == addr && (*i).core == -1)
                    {
                        ptr = i;
                    }
                }
                if (ptr != cache.set[x].end())
                {
                    mem.latency = 1;
                    cache.set[x].erase(ptr);
                }
                else if (cache.set[x].size() == cache.assoc)
                {
                    mem.latency = cache.missLatency;
                    cache.set[x].pop_front();
                }
                else
                {
                    mem.latency = cache.missLatency;
                }
                cache.set[x].push_back(tag);
                cout << "Pushed into cache" << endl;
            }
            else
                mem.latency = 1;
            if (mem.opcode == "j")
            {
                vector<string> a;
                go_to(a, ex.label);
                pc++;
                cout << "PC mem" << pc << endl;
                if (mem.pc + 1 != pc && mem.pc + 2 != pc)
                {
                    rev_HisDelete(id.pc);
                    reset(id);
                    if_reg.parts.clear();
                }
                if (mem.pc + 1 == pc)
                {
                    rev_HisDelete(id.pc);
                    reset(id);
                    if_reg.parts.clear();
                }
            }
            reset(ex);
        }
        if (mem.latency == 1)
        {
            if (mem.opcode == "sw")
            {
                int location = mem.rs2;
                location = (reg[location] - (int)memory) / 4;
                int &rd1 = memory[location + mem.offset / 4];
                rd1 = reg[mem.rs1];
            }
            if (mem.opcode == "la")
            {
                mem.ans = variables[mem.label].address;
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
        if (mem.latency > 0)
            mem.latency--;
        // if (mem.latency == 0)
    }
}
void Core::exe(int ind)
{
    if (ind)
    {
        if (ex.opcode.size() == 0)
        {
            copy(ex, id);
            if (m[ex.opcode].type == "br")
            {
                vector<string> a;
                if (ex.opcode == "beq" && reg[ex.rs1] == reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "bgt" && reg[ex.rs1] > reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "bne" && reg[ex.rs1] != reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "blt" && reg[ex.rs1] < reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "bge" && reg[ex.rs1] >= reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "ble" && reg[ex.rs1] <= reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
            }
            reset(id);
        }
        if (ex.latency == 1)
        {
            if (ex.opcode == "addi")
            {
                ex.ans += reg[ex.rs1];
            }
            if (ex.opcode == "add")
            {
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
    }
    else
    {
        if (ex.opcode.size() == 0)
        {
            copy(ex, id);
            if (m[ex.opcode].type == "br")
            {
                vector<string> a;
                if (ex.opcode == "beq" && reg[ex.rs1] == reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "bgt" && reg[ex.rs1] > reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "bne" && reg[ex.rs1] != reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "blt" && reg[ex.rs1] < reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "bge" && reg[ex.rs1] >= reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
                else if (ex.opcode == "ble" && reg[ex.rs1] <= reg[ex.rs2])
                {
                    go_to(a, ex.label);
                    pc++;
                }
            }
            reset(id);
        }
        if (ex.latency == 1)
        {
            if (ex.opcode == "addi")
            {
                ex.ans += reg[ex.rs1];
            }
            if (ex.opcode == "add")
            {
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
            if (m[ex.opcode].type == "ari")
            {
                int &rd = reg[ex.rd1];
                rd = ex.ans;
            }
            if (ex.opcode == "la")
            {
                ex.ans = variables[ex.label].address;
            }
            if (m[ex.opcode].type == "mem")
            {
                if (ex.opcode == "la")
                {
                    int &rd = reg[ex.rd1];
                    rd = ex.ans;
                }
            }
        }
    }
    if (ex.latency > 0)
        ex.latency--;
}
void Core::id_rf(int memory[], ll &top, int ind)
{
    reset(id);
    if (!if_reg.parts.empty())
    {
        id.opcode = if_reg.parts[0];
        id.pc = if_reg.pc;
    }
    if (id.opcode == ".data")
    {
        segment = ".data";
        execute(memory, top, ind);
        return;
    }
    id.latency = m[id.opcode].latency;
    // cout << "Latency of " << id.opcode << ": " << id.latency << endl;
    if (m[id.opcode].type == "jmp")
    {
        if (id.opcode == "j")
        {
            id.label = if_reg.parts[1];
        }
    }
    if (m[id.opcode].type == "mem1")
    {
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
    }
    if (m[id.opcode].type == "mem")
    {
        if (id.opcode == "la")
        {
            id.label = if_reg.parts[2];
            id.rd1 = regf(if_reg.parts[1]);
        }
        if (id.opcode == "lw")
        {
            id.rd1 = regf(if_reg.parts[1]);
            if (variables[if_reg.parts[2]].data_type == ".word")
            {
                id.label = if_reg.parts[2];
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
    history.push_back(id);
    if_reg.parts.clear();
}
void Core::ins_fetch()
{
    string s;
    if (pc >= program.size())
        return;
    for (int i = 0; i < program[pc].size(); i++)
    {
        if (program[pc][i] == ',')
            program[pc][i] = ' ';
    }
    stringstream ss(program[pc]);
    while (getline(ss, s, ' '))
    {
        if (s[s.size() - 1] == ':' && if_reg.parts.size() == 0)
        {
            if (labels[s.substr(0, s.size() - 1)] == 0)
            {
                labels[s.substr(0, s.size() - 1)] = pc + 1;
            }
        }
        else if (s.size() != 0 && s[0] == '#')
            break;
        else if (s != "\0")
        {
            if_reg.parts.push_back(s);
        }
    }
    if_reg.pc = pc;
    pc++;
    if (if_reg.parts.size() == 0)
    {
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
                    cout << "History Deleted:" << endl;
                    cout << program[history[j].pc] << endl;
                    history.erase(history.begin() + j);
                    break;
                }
            }
        }
    }
}
void Core::stagewise_execute(int memory[], ll &top, int ind, Cache &cache, int cn)
{
    clock++;
    // cout << pc << endl;
    cout << "----------New Cycle----------" << endl;
    if (ind)
    {
        vector<int> temp;
        int temp2 = 0;
        if (history.size() > 4)
        {
            history.erase(history.begin());
        }
        if (mem.opcode.size() != 0)
        {
            temp.push_back(mem.pc);
            n_ins++;
            write_back(ind);
            cout << "WB" << endl;
        }
        if (ex.opcode.size() != 0)
        {
            if (mem.opcode.size() != 0)
            {
                stall(temp);
                return;
            }
            if (ex.latency == 0)
            {
                meme(memory, top, ind, cache);
                cout << "MEM Latency:" << mem.latency << endl;
                if (m[mem.opcode].type == "mem1")
                    temp2 = 1;
                if (mem.opcode == "j")
                {
                    if (mem.pc + 2 == pc)
                    {
                        rev_HisDelete(id.pc);
                        reset(id);
                        stall(temp);
                        pc++;
                        return;
                    }
                }
            }
        }
        if (mem.latency == 0 && (id.opcode.size() != 0 || ex.latency != 0))
        {
            if (ex.opcode.size() != 0)
            {
                if (check_stall(ex))
                {
                    stall(temp);
                    return;
                }
            }
            else
            {
                if (check_stall(id))
                {
                    stall(temp);
                    return;
                }
            }
            if (ex.opcode.size() == 0)
                ex.latency = m[ex.opcode].latency;
            if (ex.opcode.size() == 0 || (ex.opcode.size() != 0 && ex.latency > 0))
            {
                exe(ind);
                cout << "EX" << endl;
                if (m[ex.opcode].type == "br" && m[ex.opcode].latency - 1 == ex.latency)
                {
                    if (ex.pc + 1 != pc - 1)
                    {
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
        if (if_reg.parts.size() != 0 && if_reg.latency == 0)
        {
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

            id_rf(memory, top, ind);
            cout << "ID" << endl;
        }
        if (pc < program.size())
        {
            if (if_reg.parts.size() != 0)
            {
                ins_fetch();
            }
            int x = log2(cache.nSets);
            x = (1 << x) - 1;
            x = x & pc;
            Tag tag;
            tag.address = pc;
            tag.core = cn;
            list<Tag>::iterator ptr = cache.set[x].end();
            for (auto i = cache.set[x].begin(); i != cache.set[x].end(); i++)
            {
                if ((*i).address == pc && (*i).core == cn)
                {
                    ptr = i;
                }
            }
            if (ptr != cache.set[x].end())
            {
                if_reg.latency = 1;
                cache.set[x].erase(ptr);
            }
            else if (cache.set[x].size() == cache.assoc)
            {
                if_reg.latency = cache.missLatency;
                cache.set[x].pop_front();
            }
            else
            {
                if_reg.latency = cache.missLatency;
            }
            cache.set[x].push_back(tag);
            cout << "Pushed pc into cache" << endl;
            if (if_reg.latency == 1)
            {
                if (if_reg.parts.size() != 0 && if_reg.parts[0] == ".data")
                {
                    segment = ".data";
                    execute(memory, top, ind);
                    ins_fetch();
                    cout << "IF" << endl;
                }
            }
            if (if_reg.latency)
                if_reg.latency--;
        }
        stall(temp);
    }
    else
    {
        vector<int> temp;
        int temp2 = 0;
        if (history.size() > 4)
        {
            history.erase(history.begin());
        }
        if (mem.opcode.size() != 0)
        {
            if (mem.latency == 0)
            {
                cout << "WB" << endl;
                // cout << program[mem.pc] << endl;
                write_back(ind);
                n_ins++;
            }
        }
        if (ex.opcode.size() != 0 || mem.latency != 0)
        {
            // if (mem.opcode.size() != 0)
            // {
            //     stall(temp);
            //     return;
            // }
            if (ex.latency == 0 || mem.latency != 0)
            {
                // cout << program[ex.pc] << endl;
                meme(memory, top, ind, cache);
                cout << "MEM Latency:" << mem.latency << endl;
                if (mem.opcode == "lw")
                    temp.push_back(mem.pc);
                if (m[mem.opcode].type == "mem1")
                    temp2 = 1;
                if (mem.opcode == "j")
                {
                    if (mem.pc + 2 == pc)
                    {
                        rev_HisDelete(id.pc);
                        reset(id);
                        stall(temp);
                        pc++;
                        return;
                    }
                }
            }
        }
        if (id.opcode.size() != 0 || ex.latency != 0)
        {
            if (ex.opcode.size() != 0)
            {
                // cout << "Stall" << endl;
                if (check_stall(ex))
                {
                    stall(temp);
                    return;
                }
                if (check_hazard(ex, mem))
                {
                    cout << "***WAR/WAW***" << endl;
                    stall(temp);
                    return;
                }
            }
            else
            {
                if (check_stall(id))
                {
                    stall(temp);
                    return;
                }
                if (check_hazard(id, mem))
                {
                    cout << "***WAR/WAW***" << endl;
                    stall(temp);
                    return;
                }
            }
            if (ex.opcode.size() == 0)
                ex.latency = m[ex.opcode].latency;
            if (ex.opcode.size() == 0 || (ex.opcode.size() != 0 && ex.latency > 0))
            {
                cout << "EX" << endl;
                // cout << program[id.pc] << endl;
                exe(ind);
                // cout << "Latency:" << ex.latency << endl;
                if (ex.latency == 0)
                {
                    if (m[ex.opcode].type == "ari" || ex.opcode == "la")
                    {
                        temp.push_back(ex.pc);
                    }
                }
                if (m[ex.opcode].type == "br" && m[ex.opcode].latency - 1 == ex.latency)
                {
                    if (ex.pc + 1 != pc - 1)
                    {
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
        if (if_reg.parts.size() != 0 && if_reg.latency == 0)
        {
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
            cout << "ID" << endl;
            // cout << program[if_reg.pc] << endl;
            id_rf(memory, top, ind);
        }
        if (pc < program.size())
        {
            if (if_reg.parts.size() == 0)
            {
                ins_fetch();
                if (pc == program.size())
                {
                    pc = pc - 1;
                }
                int x = log2(cache.nSets);
                x = (1 << x) - 1;
                x = x & (pc / (cache.blockSize / 4));
                list<Tag>::iterator ptr = cache.set[x].end();
                for (auto i = cache.set[x].begin(); i != cache.set[x].end(); i++)
                {
                    if ((*i).address == pc && (*i).core == cn)
                    {
                        ptr = i;
                    }
                }
                if (ptr != cache.set[x].end())
                {
                    if_reg.latency = 1;
                    cache.set[x].erase(ptr);
                }
                else if (cache.set[x].size() == cache.assoc)
                {
                    if_reg.latency = cache.missLatency;
                    cache.set[x].pop_front();
                }
                else
                {
                    if_reg.latency = cache.missLatency;
                }
                Tag tag;
                tag.address = pc;
                tag.core = cn;
                cache.set[x].push_back(tag);
                cout << "Pushed pc into cache" << endl;
            }
            if (if_reg.latency == 1)
            {
                if (pc == program.size() - 1)
                    ins_fetch();
                if (if_reg.parts.size() != 0 && if_reg.parts[0] == ".data")
                {
                    segment = ".data";
                    execute(memory, top, ind);
                    ins_fetch();
                    cout << "IF" << endl;
                }
            }
            cout << "IF Latency:" << if_reg.latency << endl;
            cout << "IF :" << program[if_reg.pc] << endl;
            if (if_reg.latency)
                if_reg.latency--;
        }
        stall(temp);
    }
}
void Core::execute(int memory[], ll &top, int i)
{
    vector<string> parts;
    string s;
    if (pc >= program.size())
        return;
    for (int i = 0; i < program[pc].size(); i++)
    {
        if (program[pc][i] == ',')
            program[pc][i] = ' ';
    }
    stringstream ss(program[pc]);
    while (getline(ss, s, ' '))
    {
        if (s[s.size() - 1] == ':' && parts.size() == 0 && segment == ".text")
        {
            if (labels[s.substr(0, s.size() - 1)] == 0)
            {
                labels[s.substr(0, s.size() - 1)] = pc + 1;
            }
        }
        else if (s != "\0")
            parts.push_back(s);
    }
    string opcode = "";
    if (!parts.empty())
        opcode = parts[0];
    if (opcode == ".text")
    {
        segment = ".text";
        pc++;
        for (int i = 0; i < 40; i++)
        {
        }
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
        // cout << parts[i] << endl;
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
                    top++;
                }
                a.value = stoi(parts[2]);
                variables[parts[0]] = a;
                a.size = 4;
            }
            else if (parts[1] == ".string")
            {
                for (int i = 3; i < parts.size(); i++)
                {
                    if (parts[i][0] == '#')
                        break;
                    parts[2] += " " + parts[i];
                }
                parts[2] = parts[2].substr(1, parts[2].size() - 2);
                parts[2] += "\0";
                int count = top * 4 + (ll)memory;
                char t = '\n';
                for (int i = top * 4 + (ll)memory; i < top * 4 + (ll)memory + parts[2].size(); i++)
                {
                    if (parts[2][i - top * 4 - (ll)memory] == '\\')
                    {
                        t = '\\';
                        continue;
                    }
                    if (t == '\\')
                    {
                        if (parts[2][i - top * 4 - (ll)memory] == 'n')
                            parts[2][i - top * 4 - (ll)memory] = '\n';
                        t = ' ';
                    }
                    *((char *)count) = (int)(parts[2][i - top * 4 - (ll)memory]);
                    count++;
                }
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
    pc += 1;
}