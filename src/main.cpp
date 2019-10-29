#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Calculator.hpp"

using std::cerr;
using std::cin;
using std::cout;

int main()
{
    std::string command;
    Calculator calc;

    while (getline(cin, command))
    {
        auto temp = calc.execute(command);
        if (temp.has_value())
        {
            cout << temp.value() << std::endl;
        }
    }
}
