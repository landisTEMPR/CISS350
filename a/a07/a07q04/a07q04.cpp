// Author : Brysen Landis
// File : a07q04.cpp
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

int precedence(const std::string & op)
{
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

bool is_op(const std::string & s)
{
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool is_int(const std::string & s)
{
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

// apply top operator to top two values
void apply(std::stack< int > & vals, std::stack< std::string > & ops)
{
    if (vals.size() < 2 || ops.empty()) throw std::runtime_error("ERROR");
    int right = vals.top(); vals.pop();
    int left  = vals.top(); vals.pop();
    std::string op = ops.top(); ops.pop();
    int result;
    if      (op == "+") result = left + right;
    else if (op == "-") result = left - right;
    else if (op == "*") result = left * right;
    else                result = left / right;
    vals.push(result);
}

int main()
{
    std::string line;
    std::getline(std::cin, line);

    try
    {
        std::istringstream ss(line);
        std::stack< int >         vals;
        std::stack< std::string > ops;
        std::string tok;

        while (ss >> tok)
        {
            if (is_int(tok))
            {
                vals.push(std::stoi(tok));
            }
            else if (is_op(tok))
            {
                // pop higher-or-equal precedence ops before pushing this one
                while (!ops.empty() && ops.top() != "(" &&
                       precedence(ops.top()) >= precedence(tok))
                {
                    apply(vals, ops);
                }
                ops.push(tok);
            }
            else if (tok == "(")
            {
                ops.push(tok);
            }
            else if (tok == ")")
            {
                // drain until matching '('
                bool found = false;
                while (!ops.empty())
                {
                    if (ops.top() == "(") { ops.pop(); found = true; break; }
                    apply(vals, ops);
                }
                if (!found) throw std::runtime_error("ERROR");
            }
            else
            {
                throw std::runtime_error("ERROR");
            }
        }

        // drain remaining operators
        while (!ops.empty())
        {
            if (ops.top() == "(") throw std::runtime_error("ERROR");
            apply(vals, ops);
        }

        if (vals.size() != 1) throw std::runtime_error("ERROR");
        std::cout << vals.top() << '\n';
    }
    catch (...)
    {
        std::cout << "ERROR\n";
    }

    return 0;
}
