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
        if (line[line.size() - 1] == ':')
        {
            getline(file, line);
            line = trim(line);
            sim.cores[0].program[sim.cores[0].program.size() - 1] += " " + line;
        }
        cout << sim.cores[0].program.size() << ":" << sim.cores[0].program[sim.cores[0].program.size() - 1] << endl;
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
    }
    sim.run();
    string s = "";
    file2.close();
    return 0;
}