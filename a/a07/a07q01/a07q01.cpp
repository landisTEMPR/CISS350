// Name : Brysen Landis
// File : a07q01.cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Token
{
public:
    virtual void print(std::ostream & cout) const = 0;
    virtual ~Token() {}
};

class IntTok : public Token
{
public:
    int value;
    IntTok(int v) : value(v) {}
    void print(std::ostream & cout) const { cout << "IntTok(" << value << ")"; }
};

class PlusTok : public Token
{
public:
    void print(std::ostream & cout) const { cout << "PlusTok"; }
};

class MinusTok : public Token
{
public:
    void print(std::ostream & cout) const { cout << "MinusTok"; }
};

class MultTok : public Token
{
public:
    void print(std::ostream & cout) const { cout << "MultTok"; }
};

class DivTok : public Token
{
public:
    void print(std::ostream & cout) const { cout << "DivTok"; }
};

class LParenTok : public Token
{
public:
    void print(std::ostream & cout) const { cout << "LParenTok"; }
};

class RParenTok : public Token
{
public:
    void print(std::ostream & cout) const { cout << "RParenTok"; }
};

std::ostream & operator<<(std::ostream & cout, const Token & t)
{
    t.print(cout);
    return cout;
}

std::ostream & operator<<(std::ostream & cout,
                           const std::vector< Token * > & toks)
{
    cout << '[';
    for (int i = 0; i < (int)toks.size(); ++i)
    {
        if (i > 0) cout << ", ";
        toks[i]->print(cout);
    }
    cout << ']';
    return cout;
}

std::vector< Token * > lex(const std::string & s)
{
    std::vector< Token * > toks;
    int i = 0;
    int n = (int)s.size();

    while (i < n)
    {
        char c = s[i];

        if (isspace(c))        { ++i; continue; }
        else if (c == '+')     { toks.push_back(new PlusTok());   ++i; }
        else if (c == '*')     { toks.push_back(new MultTok());   ++i; }
        else if (c == '/')     { toks.push_back(new DivTok());    ++i; }
        else if (c == '(')     { toks.push_back(new LParenTok()); ++i; }
        else if (c == ')')     { toks.push_back(new RParenTok()); ++i; }
        else if (c == '-')
        {
          
            toks.push_back(new MinusTok());
            ++i;
            // if the minus is glued to a number like "-47", emit the number too
            if (i < n && isdigit(s[i]))
            {
                int start = i;
                while (i < n && isdigit(s[i])) ++i;
                int val = std::stoi(s.substr(start, i - start));
                toks.push_back(new IntTok(val));
            }
        }
        else if (isdigit(c))
        {
            int start = i;
            while (i < n && isdigit(s[i])) ++i;
            int val = std::stoi(s.substr(start, i - start));
            toks.push_back(new IntTok(val));
        }
        else
        {
            ++i; // skip unknown characters
        }
    }
    return toks;
}

void free_tokens(std::vector< Token * > & toks)
{
    for (auto p : toks) delete p;
    toks.clear();
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::vector< Token * > toks = lex(line);
    std::cout << toks << '\n';
    free_tokens(toks);
    return 0;
}
