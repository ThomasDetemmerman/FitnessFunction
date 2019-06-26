#include <iostream>  
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void fitnessA(const std::vector<std::string> r, int &fitness, const std::vector<std::string> options, std::string &log)
{
    for (std::vector<std::string>::const_iterator it = r.begin(); it != (r.end() - 1); ++it)
        if (std::find(options.begin(), options.end(), *it) != options.end())
        {
            std::vector<std::string>::const_iterator ti = it;

            if (std::find(options.begin(), options.end(), *(++ti)) != options.end())
            {

                fitness--;
                log += "to city trips next to each other \n";
            }
        }
}
void fitnessE(const std::vector<std::string> r, int &fitness, const std::vector<std::string> n, std::string &log)
{
    std::vector<std::string>::const_iterator it = std::find(r.begin(), r.end(), "Quad-tour");
    if (std::find(n.begin(), n.end(), *(++it)) == n.end())
    {

        fitness--;
        log += "there is no nature trip trip after quad \n";
    }
}

void fitnessB(const std::vector<std::string> r, int &fitness, std::string &log)
{

    if (r.front() != "ixia")
    {
        fitness -= 1000;
        log += "ixia is not first activity \n";
    }
}
void fitnessD(const std::vector<std::string> r, int &fitness, std::string &log)
{

    if (r[1] != "rhodos-stad")
    {
        fitness -= 100;
        log += "rhodos is not the second activity, found" + r[1] + "\n";
    }
}
void fitnessC(const std::vector<std::string> r, int &fitness, std::string &log)
{
    if (r[0] == "symi" || r[2] == "symi")
    { //dinsdag of donderdag
        fitness -= 150;
        log += "symi cannot be first or third activity \n";
    }
}

int main()
{

    std::vector<std::string> city_v{"ixia", "rhodos-stad", "symi", "lindos"};
    std::vector<std::string> nature_v{"7-springs", "butterfly-Vally"};
    std::vector<std::string> other_v{"Quad-tour"};

    std::vector<std::string> results;

    results.reserve(city_v.size() + nature_v.size() + other_v.size());
    results.insert(results.end(), city_v.begin(), city_v.end());
    results.insert(results.end(), other_v.begin(), other_v.end());
    results.insert(results.end(), nature_v.begin(), nature_v.end());
    std::sort(results.begin(), results.end());
    ofstream myfile;
    myfile.open("example.txt");
    int i = 1;
    do
    {
        i++;
        int fitness = 0;
        std::string log;
        fitnessB(results, fitness, log);
        fitnessA(results, fitness, city_v, log);
        fitnessA(results, fitness, nature_v, log);
        fitnessA(results, fitness, other_v, log);
        fitnessC(results, fitness, log);
        fitnessD(results, fitness, log);
        fitnessE(results, fitness, nature_v, log);
        if (fitness >= -1)
        {

            myfile << fitness;

            myfile
                << "\t";
            for (std::vector<std::string>::const_iterator it = results.begin(); it != results.end(); ++it)
            {
                myfile << " " << *it;
            }
            myfile << std::endl
                   << std::endl;
        }

    } while (std::next_permutation(results.begin(), results.end()));
    myfile.close();
    return 0;
}
