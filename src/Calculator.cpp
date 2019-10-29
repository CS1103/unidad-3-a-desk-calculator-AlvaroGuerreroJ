#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

#include "Calculator.hpp"

#include "prettyprint.hpp"

Calculator::Calculator(Calculator const& other)
    : symbol_table(other.symbol_table)
{
}

Calculator& Calculator::operator=(const Calculator &other)
{
    symbol_table = other.symbol_table;
    return *this;
}

std::vector<std::map<std::string, std::function<Calculator::calc_option(Calculator&, std::string)>>> const Calculator::unary_ops = {
    {
        // TODO: Maybe factor this out.
        {"-",
         [](Calculator& calc, std::string a) {
             return calc_option(std::to_string(-calc.get_value(a)));
         }
        },
        {"~",
         [](Calculator& calc, std::string a) {
             return calc_option(std::to_string(~calc.get_value(a)));
            }
        },
        {"+",
         [](Calculator& calc, std::string a) {
             return calc_option(std::to_string(+calc.get_value(a)));
            }
        }
    }
};

std::vector<std::map<std::string, std::function<Calculator::calc_option(Calculator &, std::string, std::string)>>> const Calculator::binary_ops = {
    {
        {"**",
         [](Calculator &calc, std::string const a, std::string const b) {
             return calc_option(std::to_string(calc_type(std::pow(calc.get_value(a), calc.get_value(b)))));
         }
        }
    },
    {
        {"*",
         [](Calculator &calc, std::string const a, std::string const b) {
             return calc_option(std::to_string(calc.get_value(a) * calc.get_value(b)));
         }
        },
        {"/",
         [](Calculator &calc, std::string const a, std::string const b) {
             return calc_option(std::to_string(calc.get_value(a) / calc.get_value(b)));
         }
        },
        {"%",
         [](Calculator &calc, std::string const a, std::string const b) {
             return calc_option(std::to_string(calc.get_value(a) % calc.get_value(b)));
         }
        }
    },
    {
        {"+",
         [](Calculator &calc, std::string a, std::string b) {
             return calc_option(std::to_string(calc.get_value(a) + calc.get_value(b)));
         }
        },
        {"-",
         [](Calculator &calc, std::string a, std::string b) {
             return calc_option(std::to_string(calc.get_value(a) - calc.get_value(b)));
         }
        }
    },
    {
        {"=",
         [](Calculator &calc, std::string a, std::string b) {
             if (!is_symbol(a))
             {
                 throw Calculator::calculator_error(a + " is not a valid symbol"
                                                      " name. symbols can only contain "
                                                      "alphabetic characters.");
             }
             calc.symbol_table[a] = calc.get_value(b);
             return calc_option();
         }
        }
    }
};

std::string strip(std::string stripping, std::string to_strip)
{
    std::unordered_set<char> strip_set(to_strip.begin(), to_strip.end());

    std::string ret;
    std::copy_if(stripping.begin(), stripping.end(), back_inserter(ret),
            [&strip_set](char s) {
                return strip_set.count(s) == 0;
            });
    return ret;
}

Calculator::calc_option Calculator::execute(std::string command)
{
    std::list<std::string> parts = tokenize(command);

    // TODO: Implement parenthesis (recognize deepest parenthesis, then execute
    //       what's inside first, repeat).

    Calculator new_state(*this);
    calc_option ret;

    try
    {
        // First check if any unary operation is present. Unary operations have
        // higuer priority than binary ones.
        for (auto const& priorities : unary_ops)
        {
            if (parts.size() < 2)
            {
                break;
            }

            // All of our unary operations take the argument to the right of
            // them.
            for (auto it = std::prev(parts.end());; it--)
            {
                // We must make sure that the argument to the left (if any) is
                // not a symbol or literal.
                if (priorities.find(*it) != priorities.end() &&
                    (it == parts.begin() || is_operator(*std::prev(it))))
                {
                    calc_option result = priorities.at(*it)(new_state, *std::next(it));
                    it = parts.erase(it, std::next(it, 2));
                    if (result.has_value())
                    {
                        it = parts.insert(it, result.value());
                    }
                    else
                    {
                        // Operations that don't return value must be the last
                        // ones.
                        if (!parts.empty())
                        {
                            throw calculator_error("Invalid command." );
                        }
                        ret = calc_option();
                        goto exit_execution;
                    }
                }

                if (it == parts.begin())
                {
                    break;
                }
            }
        }


        for (auto const& priorities : binary_ops)
        {
            if (parts.size() < 3)
            {
                break;
            }

            // Binary operations take two arguments around them.
            for (auto it = std::next(parts.begin());
                std::distance(parts.begin(), it) >= 1 &&
                std::distance(it, parts.end()) >= 2;
                it++)
            {
                if (priorities.find(*it) != priorities.end())
                {
                    calc_option result = priorities.at(*it)(new_state, *std::prev(it), *std::next(it));
                    it = parts.erase(std::prev(it), std::next(it, 2));
                    if (result.has_value())
                    {
                        it = parts.insert(it, result.value());
                    }
                    else
                    {
                        // Operations that don't return value must be the last
                        // ones.
                        if (!parts.empty())
                        {
                            throw calculator_error("Invalid command." );
                        }
                        ret = calc_option();
                        goto exit_execution;
                    }
                }
            }
        }

        if (parts.size() != 1)
        {
            throw calculator_error("Something went wrong.");
        }

        std::string result = parts.front();
        if (is_symbol(result))
        {
            if (symbol_table.count(result) != 0)
            {
                ret = calc_option(std::to_string(symbol_table.at(result)));
            }
            else
            {
                throw calculator_error(" is not defined" );
            }

        }
        else if (is_literal(result))
        {
            ret = calc_option(result);
        }
        else
        {
            throw calculator_error(result + " is not a symbol or literal.");
        }
    }
    catch (calculator_error const& ce)
    {
        std::cerr << ce.what() << std::endl;
        return calc_option();
    }

    exit_execution:
    *this = new_state;
    return ret;
}

std::list<std::string> Calculator::tokenize(std::string s)
{
    std::list<std::string> ret;

    auto it = s.begin();
    while (it != s.end())
    {
        if (isspace(*it))
        {
            it = std::find_if_not(it, s.end(),
                                  [](char c) {
                                      return isspace(c);
                                  });
        }
        else if (std::isalpha(*it))
        {
            auto temp = std::find_if_not(it, s.end(),
                                         [](char c) {
                                             return std::isalnum(c);
                                         });
            ret.push_back(std::string(it, temp));
            it = temp;
        }
        else if (std::ispunct(*it))
        {
            auto temp = std::find_if_not(it, s.end(),
                                         [](char c) {
                                             return std::ispunct(c);
                                         });
            ret.push_back(std::string(it, temp));
            it = temp;
        }
        else if (std::isdigit(*it))
        {
            auto temp = std::find_if_not(it, s.end(),
                                         [](char c) {
                                             return std::isdigit(c);
                                         });
            ret.push_back(std::string(it, temp));
            it = temp;
        }
    }

    return ret;
}

bool Calculator::is_symbol(std::string s)
{
    std::regex symbol("[a-zA-Z]\\w*");
    return std::regex_match(s, symbol);
}

bool Calculator::is_literal(std::string s)
{
    std::regex literal("-?\\d+");
    return std::regex_match(s, literal);
}

bool Calculator::is_operator(std::string s)
{
    static auto const& unary_ops = Calculator::unary_ops;
    static auto const& binary_ops = Calculator::binary_ops;
    static std::unordered_set<std::string> operator_tokens = [](){
        std::unordered_set<std::string> ret;
        for (auto const& priority_level : unary_ops)
        {
            for (auto const& op : priority_level)
            {
                ret.insert(op.first);
            }
        }
        for (auto const& priority_level : binary_ops)
        {
            for (auto const& op : priority_level)
            {
                ret.insert(op.first);
            }
        }
        return ret;
    }();

    return operator_tokens.count(s) != 0;
}

Calculator::calc_type Calculator::get_value(std::string s) const
{
    if (is_symbol(s))
    {
        try
        {
            return symbol_table.at(s);
        }
        catch (std::out_of_range const&)
        {
            throw Calculator::calculator_error(s + " is not defined.");
        }
    }
    else if (is_literal(s))
    {
        Calculator::calc_type ret;
        std::istringstream in(s);
        in >> ret;
        return ret;
    }
    else
    {
        throw Calculator::calculator_error(s + " is not a literal or symbol");
    }
}
