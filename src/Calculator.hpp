#ifndef GUARD_CALCULATOR_CPP
#define GUARD_CALCULATOR_CPP

#include <functional>
#include <list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Calculator
{
private:
    using calc_type = long;
    using calc_option = std::optional<std::string>;

private:
    // All unary operators have more precedence than the binary_ones
    static std::vector<std::map<std::string, std::function<calc_option(Calculator&, calc_option)>>> unary_ops;
    static std::vector<std::map<std::string, std::function<calc_option(Calculator&, calc_option, calc_option)>>> binary_ops;

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
};

#endif
