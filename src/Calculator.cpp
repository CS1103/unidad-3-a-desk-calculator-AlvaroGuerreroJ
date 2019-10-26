#include <algorithm>
#include <cctype>
#include <cmath>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#include "Calculator.hpp"
#include <iostream>

#include <prettyprint.hpp>

using std::all_of;
using std::copy_if;
using std::find;
using std::find_if;
using std::function;
using std::isalpha;
using std::isdigit;
using std::ispunct;
using std::istringstream;
using std::list;
using std::map;
using std::optional;
using std::pair;
using std::pow;
using std::string;
using std::to_string;
using std::unordered_set;
using std::vector;

vector<map<string, function<Calculator::calc_option(Calculator&, Calculator::calc_option)>>> Calculator::unary_ops = {
    {
        {"-", [](Calculator& calc, Calculator::calc_option a) {
                calc_type temp;
                if (is_symbol(a.value()))
                {
                    temp = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> temp;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }
                return calc_option(to_string(-temp));
            }
        },
        {"~", [](Calculator& calc, Calculator::calc_option a) {
                calc_type temp;
                if (is_symbol(a.value()))
                {
                    temp = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> temp;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }
                return calc_option(to_string(~temp));
            }
        }
    }
};

vector<map<string, function<Calculator::calc_option(Calculator&, Calculator::calc_option, Calculator::calc_option)>>> Calculator::binary_ops = {
    {
        {"**", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                calc_type a_val;
                if (is_symbol(a.value()))
                {
                    a_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> a_val;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(b.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not a literal or symbol.");
                }

                return calc_option(to_string(Calculator::calc_type(pow(a_val, b_val))));
            }
        }
    },
    {
        {"*", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                calc_type a_val;
                if (is_symbol(a.value()))
                {
                    a_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> a_val;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(b.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not a literal or symbol.");
                }

                return calc_option(to_string(a_val * b_val));
            }
        },
        {"/", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                calc_type a_val;
                if (is_symbol(a.value()))
                {
                    a_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> a_val;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(b.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not b literal or symbol.");
                }

                return calc_option(to_string(a_val / b_val));
            }
        },
        {"%", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                calc_type a_val;
                if (is_symbol(a.value()))
                {
                    a_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> a_val;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(b.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not b literal or symbol.");
                }

                return calc_option(to_string(a_val % b_val));
            }
        }
    },
    {
        {"+", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                calc_type a_val;
                if (is_symbol(a.value()))
                {
                    a_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> a_val;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(b.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not b literal or symbol.");
                }

                return calc_option(to_string(a_val + b_val));
            }
        },
        {"-", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                calc_type a_val;
                if (is_symbol(a.value()))
                {
                    a_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(a.value()))
                {
                    istringstream in(a.value());
                    in >> a_val;
                }
                else
                {
                    throw std::runtime_error(a.value() + "is not a literal or symbol.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(b.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not b literal or symbol.");
                }

                return calc_option(to_string(a_val - b_val));
            }
        }
    },
    {
        {"=", [](Calculator& calc, Calculator::calc_option a, Calculator::calc_option b) {
                if (!is_symbol(a.value()))
                {
                    throw std::runtime_error(a.value() + " is not a valid symbol"
                                            " name. symbols can only contain "
                                            "alphabetic characters.");
                }

                calc_type b_val;
                if (is_symbol(b.value()))
                {
                    b_val = calc.symbol_table.at(a.value());
                }
                else if (is_literal(b.value()))
                {
                    istringstream in(b.value());
                    in >> b_val;
                }
                else
                {
                    throw std::runtime_error(b.value() + "is not a literal or symbol.");
                }

                calc.symbol_table[a.value()] = b_val;

                return calc_option();
            }
        }
    }
};

string strip(string stripping, string to_strip)
{
    unordered_set<char> strip_set(to_strip.begin(), to_strip.end());

    string ret;
    copy_if(stripping.begin(), stripping.end(), back_inserter(ret),
            [&strip_set](char s) {
                return strip_set.count(s) == 0;
            });
    return ret;
}

Calculator::calc_option Calculator::execute(std::string command)
{
    auto parts = tokenize(command);

    // TODO: This could be optimized, though it looks like a pain
    while (parts.size() != 1)
    {
        // First check if any unary ops is present. Unary ops have higuer
        // priority than binary ones.
        for (auto const& precedence_level : unary_ops)
        {
            // Check one precedence level at the time
            list<pair<decltype(parts.begin()), >>
            for (auto const& op : precedence_level)
            {
                auto temp = find(parts.begin(), parts.end(), op.);
            }
        }
    }

    return calc_option(command);
}

list<string> Calculator::tokenize(string s)
{
    list<string> ret;

    auto it = s.begin();
    while (it != s.end())
    {
        if (isspace(*it))
        {
            auto temp = find_if(it, s.end(),
                                 [](char c) {
                                     return !isspace(c);
                                 });
            ret.push_back(string(it, temp));
            it = temp;
        }
        else if (isalpha(*it))
        {
            auto temp = find_if(it, s.end(),
                                 [](char c) {
                                     return !isalpha(c);
                                 });
            ret.push_back(string(it, temp));
            it = temp;
        }
        else if (ispunct(*it))
        {
            auto temp = find_if(it, s.end(),
                                 [](char c) {
                                     return !ispunct(c);
                                 });
            ret.push_back(string(it, temp));
            it = temp;
        }
        else if (isdigit(*it))
        {
            auto temp = find_if(it, s.end(),
                                 [](char c) {
                                     return !isdigit(c);
                                 });
            ret.push_back(string(it, temp));
            it = temp;
        }
    }

    return ret;
}

bool Calculator::is_symbol(std::string s)
{
    return all_of(s.begin(), s.end(),
                  [](char c) {
                      return isalpha(c);
                  });
}

bool Calculator::is_literal(std::string s)
{
    return all_of(s.begin(), s.end(),
                  [](char c) {
                      return isdigit(c);
                  });
}
