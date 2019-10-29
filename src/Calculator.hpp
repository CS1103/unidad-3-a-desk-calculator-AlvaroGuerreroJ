#ifndef GUARD_CALCULATOR_CPP
#define GUARD_CALCULATOR_CPP

#include <functional>
#include <list>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Calculator
{
public:
    class calculator_error : public std::runtime_error
    {
public:
        calculator_error(char const* msg)
            : std::runtime_error(msg)
        {
        }

        calculator_error(std::string const& msg)
            : std::runtime_error(msg)
        {
        }

        char const* what() const throw()
        {
            return std::runtime_error::what();;
        }
    };

private:
    using calc_type = long;
    using calc_option = std::optional<std::string>;

private:
    // All unary operators have more precedence than the binary_ones
    static std::vector<std::map<std::string, std::function<calc_option(Calculator&, std::string)>>> const unary_ops;
    static std::vector<std::map<std::string, std::function<calc_option(Calculator&, std::string, std::string)>>> const binary_ops;

    static std::vector<std::string> reserved_words;

private:
    std::map<std::string, calc_type> symbol_table;

public:
    Calculator() = default;
    ~Calculator() = default;

    calc_option execute(std::string command);

private:
    static std::list<std::string> tokenize(std::string s);
    static std::string strip(std::string stripping, std::string to_strip);

    static bool is_symbol(std::string s);
    static bool is_literal(std::string s);
    static bool is_operator(std::string s);
};

#endif
