#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

#include "Calculator.hpp"

int main()
{
    Calculator calc;

    char const* command;
    rl_bind_key('\t', rl_insert);
    while ((command = readline(">>> ")) != nullptr)
    {
        auto temp = calc.execute(command);
        if (temp.has_value())
        {
            std::cout << temp.value() << std::endl;
        }
        if (*command)
        {
            add_history(command);
        }
        std::free((void*) command);
    }
}
