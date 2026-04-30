// Name : Brysen Landis
// File : a07q02.cpp
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <stdexcept>

// tokenize: split input line into a queue of string tokens
std::queue< std::string > tokenize(const std::string & line)
{
    std::queue< std::string > q;
    std::istringstream ss(line);
    std::string word;
    while (ss >> word) q.push(word);
    return q;
}

bool is_int(const std::string & s)
{
    if (s.empty()) return false;
    int start = (s[0] == '-') ? 1 : 0;
    if (start == 1 && s.size() == 1) return false;
    for (int i = start; i < (int)s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

// evaluate: recursively evaluates prefix expression from queue
int evaluate(std::queue< std::string > & q)
{
    if (q.empty()) throw std::runtime_error("ERROR");

    std::string tok = q.front();
    q.pop();

    if (is_int(tok))
        return std::stoi(tok);

    // operator: evaluate two operands recursively
    if (tok == "+" || tok == "-" || tok == "*" || tok == "/")
    {
        int left  = evaluate(q);
        int right = evaluate(q);
        if (tok == "+") return left + right;
        if (tok == "-") return left - right;
        if (tok == "*") return left * right;
        if (tok == "/") return left / right;
    }

    throw std::runtime_error("ERROR");
}

int main()
{
    std::string line;
    std::getline(std::cin, line);

    try
    {
        std::queue< std::string > q = tokenize(line);
        int result = evaluate(q);
        // after evaluation the queue must be empty for a valid expression
        if (!q.empty()) throw std::runtime_error("ERROR");
        std::cout << result << '\n';
    }
    catch (...)
    {
        std::cout << "ERROR\n";
    }

    return 0;
}
