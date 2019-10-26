#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Calculator.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::divides;
using std::function;
using std::getline;
using std::map;
using std::minus;
using std::modulus;
using std::multiplies;
using std::plus;
using std::string;
using std::vector;

int main()
{
    string command;
    Calculator calc;

    while (getline(cin, command))
    {
        auto temp = calc.execute(command);
        if (temp.has_value())
        {
            cout << temp.value() << endl;
        }
    }
}
