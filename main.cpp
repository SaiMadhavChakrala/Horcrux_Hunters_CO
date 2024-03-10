#include "header.hpp"
#include "Processor.cpp"
#include "Core.cpp"
#include <regex>
std::string ltrim(const std::string &s)
{
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string &s)
{
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string &s)
{
    return ltrim(rtrim(s));
}
int main()
{
    cout << "Enter 0 for Data Forwarding else 1:";
    int d;
    cin >> d;
    freopen("out.txt", "w", stdout);
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
        line = trim(line);
        if (line == "\0" || line[0] == '#' || line.size() == 0)
            continue;
        sim.cores[0].program.push_back(line);
        string p = "";
        stringstream ss(line);
        vector<string> array;
        while (getline(ss, p, ' '))
        {
            if (p.size() != 0 && p[0] == '#')
                break;
            if (array.size() == 2)
            {
                break;
            }
            else if (p != "\0")
            {
                array.push_back(p);
            }
        }
        if (!array.empty() && array[0] == "la")
        {
            while (getline(ss, p, ' '))
            {
                if (p.size() != 0 && p[0] == '#')
                    break;
                else if (p != "\0")
                {
                    array.push_back(p);
                }
            }
            p = "addi ";
            p += array[1] + " " + array[1] + "  0";
            sim.cores[0].program.push_back(p);
            // cout << p << endl;
        }
        if (line[line.size() - 1] == ':')
        {
            getline(file, line);
            line = trim(line);
            sim.cores[0].program[sim.cores[0].program.size() - 1] += " " + line;
        }
        // cout << sim.cores[0].program.size() << ":" << sim.cores[0].program[sim.cores[0].program.size() - 1] << endl;
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
        line2 = trim(line2);
        if (line2 == "\0" || line2[0] == '#' || line2.size() == 0)
            continue;
        sim.cores[1].program.push_back(line2);
        string p = "";
        stringstream ss(line2);
        vector<string> array;
        while (getline(ss, p, ' '))
        {
            if (p.size() != 0 && p[0] == '#')
                break;
            if (array.size() == 2)
            {
                break;
            }
            else if (p != "\0")
            {
                array.push_back(p);
            }
        }
        if (!array.empty() && array[0] == "la")
        {
            while (getline(ss, p, ' '))
            {
                if (p.size() != 0 && p[0] == '#')
                    break;
                else if (p != "\0")
                {
                    array.push_back(p);
                }
            }
            p = "addi ";
            p += array[1] + " " + array[1] + "  0";
            sim.cores[1].program.push_back(p);
            // cout << p << endl;
        }
        if (line2[line2.size() - 1] == ':')
        {
            getline(file2, line2);
            line2 = trim(line2);
            sim.cores[1].program[sim.cores[1].program.size() - 1] += " " + line2;
        }
        // cout << sim.cores[1].program.size() << ":" << sim.cores[1].program[sim.cores[1].program.size() - 1] << endl;
    }
    sim.cores[0].init();
    sim.cores[1].init();
    sim.run(d);
    string s = "";
    file2.close();
    return 0;
}
