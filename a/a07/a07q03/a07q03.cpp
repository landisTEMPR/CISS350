// Author : Brysen Landis
// File : a07q03.cpp
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

bool is_int(const std::string & s)
{
    if (s.empty()) return false;
    int start = (s[0] == '-') ? 1 : 0;
    if (start == 1 && (int)s.size() == 1) return false;
    for (int i = start; i < (int)s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

int main()
{
    std::string line;
    std::getline(std::cin, line);

    try
    {
        std::istringstream ss(line);
        std::stack< int > stk;
        std::string tok;

        while (ss >> tok)
        {
            if (is_int(tok))
            {
                stk.push(std::stoi(tok));
            }
            else if (tok == "+" || tok == "-" || tok == "*" || tok == "/")
            {
                // need at least two operands
                if (stk.size() < 2) throw std::runtime_error("ERROR");

                int right = stk.top(); stk.pop();
                int left  = stk.top(); stk.pop();
                int result;

                if      (tok == "+") result = left + right;
                else if (tok == "-") result = left - right;
                else if (tok == "*") result = left * right;
                else                 result = left / right;

                stk.push(result);
            }
            else
            {
                throw std::runtime_error("ERROR");
            }
        }

        // valid expression leaves exactly one value on the stack
        if (stk.size() != 1) throw std::runtime_error("ERROR");
        std::cout << stk.top() << '\n';
    }
    catch (...)
    {
        std::cout << "ERROR\n";
    }

    return 0;
}
