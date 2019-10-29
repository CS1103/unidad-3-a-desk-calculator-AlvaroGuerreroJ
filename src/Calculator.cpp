#include <algorithm>
#include <cctype>
#include <cmath>
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

#include <iostream>
#include "prettyprint.hpp"

std::vector<std::string> Calculator::reserved_words = {};

std::vector<std::map<std::string, std::function<Calculator::calc_option(Calculator&, std::string)>>> const Calculator::unary_ops = {
    {
        {"-",
         [](Calculator& calc, std::string a) {
             calc_type temp;
             if (is_symbol(a))
             {
                 temp = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> temp;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }
             return calc_option(std::to_string(-temp));
         }
        },
        {"~",
         [](Calculator& calc, std::string a) {
             calc_type temp;
             if (is_symbol(a))
             {
                 temp = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> temp;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }
             return calc_option(std::to_string(~temp));
            }
        },
        {"+",
         [](Calculator& calc, std::string a) {
             calc_type temp;
             if (is_symbol(a))
             {
                 temp = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> temp;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }
             return calc_option(std::to_string(temp));
            }
        }
    }
};

std::vector<std::map<std::string, std::function<Calculator::calc_option(Calculator &, std::string, std::string)>>> const Calculator::binary_ops = {
    {
        {"**",
         [](Calculator &calc, std::string a, std::string b) {
             calc_type a_val;
             if (is_symbol(a))
             {
                 a_val = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> a_val;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(b);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not a literal or symbol.");
             }

             return calc_option(std::to_string(Calculator::calc_type(std::pow(a_val, b_val))));
         }
        }
    },
    {
        {"*",
         [](Calculator &calc, std::string a, std::string b) {
             calc_type a_val;
             if (is_symbol(a))
             {
                 a_val = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> a_val;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(b);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not a literal or symbol.");
             }

             return calc_option(std::to_string(a_val * b_val));
         }
        },
        {"/",
         [](Calculator &calc, std::string a, std::string b) {
             calc_type a_val;
             if (is_symbol(a))
             {
                 a_val = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> a_val;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(b);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not b literal or symbol.");
             }

             return calc_option(std::to_string(a_val / b_val));
         }
        },
        {"%",
         [](Calculator &calc, std::string a, std::string b) {
             calc_type a_val;
             if (is_symbol(a))
             {
                 a_val = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> a_val;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(b);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not b literal or symbol.");
             }

             return calc_option(std::to_string(a_val % b_val));
         }
        }
    },
    {
        {"+",
         [](Calculator &calc, std::string a, std::string b) {
             calc_type a_val;
             if (is_symbol(a))
             {
                 a_val = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> a_val;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(b);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not b literal or symbol.");
             }

             return calc_option(std::to_string(a_val + b_val));
         }
        },
        {"-",
         [](Calculator &calc, std::string a, std::string b) {
             calc_type a_val;
             if (is_symbol(a))
             {
                 a_val = calc.symbol_table.at(a);
             }
             else if (is_literal(a))
             {
                 std::istringstream in(a);
                 in >> a_val;
             }
             else
             {
                 throw std::runtime_error(a + " is not a literal or symbol.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(b);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not b literal or symbol.");
             }

             return calc_option(std::to_string(a_val - b_val));
         }
        }
    },
    {
        {"=",
         [](Calculator &calc, std::string a, std::string b) {
             if (!is_symbol(a))
             {
                 throw std::runtime_error(a + " is not a valid symbol"
                                                      " name. symbols can only contain "
                                                      "alphabetic characters.");
             }

             calc_type b_val;
             if (is_symbol(b))
             {
                 b_val = calc.symbol_table.at(a);
             }
             else if (is_literal(b))
             {
                 std::istringstream in(b);
                 in >> b_val;
             }
             else
             {
                 throw std::runtime_error(b + " is not a literal or symbol.");
             }

             calc.symbol_table[a] = b_val;

             return calc_option(std::to_string(b_val));
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

    std::cout << "Parts at the beginning: " << parts << std::endl;

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
                calc_option result = priorities.at(*it)(*this, *std::next(it));
                it = parts.erase(it, std::next(it, 2));
                if (result.has_value())
                {
                    it = parts.insert(it, result.value());
                }
                else
                {
                    throw "Not implemented yet";
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
                calc_option result = priorities.at(*it)(*this, *std::prev(it), *std::next(it));
                it = parts.erase(std::prev(it), std::next(it, 2));
                if (result.has_value())
                {
                    it = parts.insert(it, result.value());
                }
                else
                {
                    throw "Not implemented yet";
                }
            }
        }
    }

    std::cout << "Parts at the end: " << parts << std::endl;

    std::string result = parts.front();
    if (is_symbol(result))
    {
        if (symbol_table.count(result) != 0)
        {
            return calc_option(std::to_string(symbol_table.at(result)));
        }
        else
        {
            std::cerr << result << " is not defined" << std::endl;
            return calc_option();   
        }
        
    }
    else if (is_literal(result))
    {
        return calc_option(result);
    }
    else
    {
        std::cerr << "Something went wrong." << std::endl;
        return calc_option();
    }
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
