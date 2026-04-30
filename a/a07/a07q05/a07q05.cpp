// Author : Brysen Landis
// File : a07q05.cpp
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

// ---------------------------------------------------------------------------
// Monomial: one term  coefficient * x^degree
// ---------------------------------------------------------------------------
struct Monomial
{
    int degree;
    int coefficient;
    Monomial(int d, int c) : degree(d), coefficient(c) {}
};

// ---------------------------------------------------------------------------
// Polynomial
// ---------------------------------------------------------------------------
class Polynomial
{
public:
    // default constructor: zero polynomial
    Polynomial() {}

    // construct from integer constant
    Polynomial(int c)
    {
        if (c != 0)
            p_.push_back(Monomial(0, c));
    }

    // construct from string like "3*x^2 + 7*x^12 - 9*x^100 + x^5 + 32"
    Polynomial(const std::string & s)
    {
        parse(s);
    }

    // copy constructor
    Polynomial(const Polynomial & other) : p_(other.p_) {}

    // assignment operator
    Polynomial & operator=(const Polynomial & other)
    {
        if (this != &other) p_ = other.p_;
        return *this;
    }

    // degree of polynomial (degree of highest-degree term)
    // returns -1 for the zero polynomial
    int deg() const
    {
        if (p_.empty()) return -1;
        // list is sorted ascending, so tail has highest degree
        return p_.back().degree;
    }

    bool is_zero() const { return p_.empty(); }

    // ---------------------------------------------------------------------------
    // Arithmetic operators
    // ---------------------------------------------------------------------------
    Polynomial & operator+=(const Polynomial & other)
    {
        for (const Monomial & m : other.p_)
            add_term(m.degree, m.coefficient);
        return *this;
    }

    Polynomial & operator-=(const Polynomial & other)
    {
        for (const Monomial & m : other.p_)
            add_term(m.degree, -m.coefficient);
        return *this;
    }

    Polynomial & operator*=(const Polynomial & other)
    {
        Polynomial result;
        for (const Monomial & a : p_)
            for (const Monomial & b : other.p_)
                result.add_term(a.degree + b.degree, a.coefficient * b.coefficient);
        *this = result;
        return *this;
    }

    Polynomial & operator+=(int c)  { add_term(0, c); return *this; }
    Polynomial & operator-=(int c)  { add_term(0, -c); return *this; }
    Polynomial & operator*=(int c)
    {
        if (c == 0) { p_.clear(); return *this; }
        for (Monomial & m : p_) m.coefficient *= c;
        return *this;
    }

    // binary operators built from compound-assignment
    friend Polynomial operator+(Polynomial a, const Polynomial & b) { a += b; return a; }
    friend Polynomial operator-(Polynomial a, const Polynomial & b) { a -= b; return a; }
    friend Polynomial operator*(Polynomial a, const Polynomial & b) { a *= b; return a; }

    friend Polynomial operator+(Polynomial a, int c) { a += c; return a; }
    friend Polynomial operator+(int c, Polynomial a) { a += c; return a; }
    friend Polynomial operator-(Polynomial a, int c) { a -= c; return a; }
    friend Polynomial operator-(int c, const Polynomial & a)
    {
        Polynomial result(c);
        result -= a;
        return result;
    }
    friend Polynomial operator*(Polynomial a, int c) { a *= c; return a; }
    friend Polynomial operator*(int c, Polynomial a) { a *= c; return a; }

    // ---------------------------------------------------------------------------
    // Comparison operators
    // ---------------------------------------------------------------------------
    bool operator==(const Polynomial & other) const
    {
        if (p_.size() != other.p_.size()) return false;
        auto it1 = p_.begin(), it2 = other.p_.begin();
        while (it1 != p_.end())
        {
            if (it1->degree != it2->degree ||
                it1->coefficient != it2->coefficient) return false;
            ++it1; ++it2;
        }
        return true;
    }

    bool operator!=(const Polynomial & other) const { return !(*this == other); }
    bool operator==(int c) const
    {
        Polynomial tmp(c);
        return *this == tmp;
    }
    bool operator!=(int c) const { return !(*this == c); }
    friend bool operator==(int c, const Polynomial & p) { return p == c; }
    friend bool operator!=(int c, const Polynomial & p) { return p != c; }

    // ---------------------------------------------------------------------------
    // Output: highest degree first
    // ---------------------------------------------------------------------------
    friend std::ostream & operator<<(std::ostream & cout, const Polynomial & poly)
    {
        if (poly.p_.empty()) { cout << "0"; return cout; }

        // iterate from tail (highest degree) to head (lowest degree)
        bool first = true;
        auto it = poly.p_.end();
        while (it != poly.p_.begin())
        {
            --it;
            int c = it->coefficient;
            int d = it->degree;

            if (first)
            {
                // print leading term with sign
                if (c < 0) cout << '-';
                print_term(cout, std::abs(c), d);
                first = false;
            }
            else
            {
                cout << (c > 0 ? " + " : " - ");
                print_term(cout, std::abs(c), d);
            }
        }
        return cout;
    }

    // deg() as a free function
    friend int deg(const Polynomial & p) { return p.deg(); }

private:
    // list sorted ascending by degree; no zero-coefficient terms stored
    std::list< Monomial > p_;

    // print a single term (coefficient already positive, caller handles sign)
    static void print_term(std::ostream & cout, int c, int d)
    {
        if (d == 0)
        {
            cout << c;
        }
        else if (d == 1)
        {
            if (c != 1) cout << c;
            cout << 'x';
        }
        else
        {
            if (c != 1) cout << c;
            cout << "x^" << d;
        }
    }

    // add coefficient c to the term of degree d (insert/merge/remove as needed)
    void add_term(int d, int c)
    {
        if (c == 0) return;
        // find insertion point keeping list sorted by degree ascending
        for (auto it = p_.begin(); it != p_.end(); ++it)
        {
            if (it->degree == d)
            {
                it->coefficient += c;
                if (it->coefficient == 0) p_.erase(it);
                return;
            }
            if (it->degree > d)
            {
                p_.insert(it, Monomial(d, c));
                return;
            }
        }
        p_.push_back(Monomial(d, c));
    }

  
    void parse(const std::string & s)
    {
        // tokenize into sign + monomial strings
        // strategy: scan char by char, splitting on + and -
        std::vector< std::pair<int,std::string> > parts; // (sign, term_string)
        int sign = 1;
        std::string cur;
        bool first = true;

        auto flush = [&]()
        {
            // trim whitespace
            size_t a = cur.find_first_not_of(" \t");
            size_t b = cur.find_last_not_of(" \t");
            if (a != std::string::npos)
                parts.push_back({sign, cur.substr(a, b - a + 1)});
            cur.clear();
        };

        for (int i = 0; i < (int)s.size(); ++i)
        {
            char c = s[i];
            if ((c == '+' || c == '-') && !first)
            {
                flush();
                sign = (c == '-') ? -1 : 1;
            }
            else if (c == '-' && first)
            {
                sign = -1;
            }
            else
            {
                cur += c;
                first = false;
            }
        }
        flush();

        for (auto & pr : parts)
        {
            int sg = pr.first;
            std::string t = pr.second;
            parse_monomial(sg, t);
        }
    }

    void parse_monomial(int sign, const std::string & t)
    {
        // remove spaces from token
        std::string tok;
        for (char c : t) if (c != ' ' && c != '\t') tok += c;
        if (tok.empty()) return;

        // forms: c*x^d, x^d, c*x, x, c
        int c = 1, d = 0;

        size_t star = tok.find('*');
        size_t xpos = tok.find('x');
        size_t caret = tok.find('^');

        if (xpos == std::string::npos)
        {
            // constant term: just c
            c = std::stoi(tok);
            d = 0;
        }
        else
        {
            // has x
            if (star != std::string::npos)
            {
                // c*x^d or c*x
                std::string cstr = tok.substr(0, star);
                c = cstr.empty() ? 1 : std::stoi(cstr);
            }
            else
            {
                c = 1;
            }

            if (caret != std::string::npos)
            {
                d = std::stoi(tok.substr(caret + 1));
            }
            else
            {
                d = 1;
            }
        }

        add_term(d, sign * c);
    }
};

// ---------------------------------------------------------------------------
// main: tests all required functionality
// ---------------------------------------------------------------------------
int main()
{
    std::cout << "=== Construction and printing ===\n";
    Polynomial p("3*x^2 + 7*x^12 - 9*x^100 + -2*x^32 + x^5 + 0*x^6 + 6*x^2 + 32 + 1*x^0");
    std::cout << p << '\n';

    std::cout << "\n=== Constant and copy constructors ===\n";
    Polynomial p0(42);
    std::cout << p0 << '\n'; // 42

    Polynomial p1(p);
    std::cout << p1 << '\n'; // same as p

    std::cout << "\n=== Equality ===\n";
    std::cout << (p0 == p)  << '\n'; // 0
    std::cout << (p1 != p)  << '\n'; // 0
    std::cout << (5 == p)   << '\n'; // 0
    std::cout << (p != 5)   << '\n'; // 1

    std::cout << "\n=== Degree ===\n";
    std::cout << deg(p) << '\n'; // 100

    std::cout << "\n=== Arithmetic with polynomial ===\n";
    Polynomial q("x^2 + x + 1");
    std::cout << "q = " << q << '\n';

    Polynomial pa(p);
    pa += q;
    std::cout << "p + q = " << pa << '\n';

    Polynomial ps(p);
    ps -= q;
    std::cout << "p - q = " << ps << '\n';

    Polynomial pm(p);
    pm *= Polynomial("x + 1");
    std::cout << "(p)*(x+1) = " << pm << '\n';

    std::cout << "\n=== Arithmetic with integer ===\n";
    Polynomial r("x^2 + 2*x + 1");
    r += 10;
    std::cout << "x^2+2x+1 + 10 = " << r << '\n'; // x^2+2x+11

    r -= 5;
    std::cout << "... - 5 = " << r << '\n'; // x^2+2x+6

    r *= 2;
    std::cout << "... * 2 = " << r << '\n'; // 2x^2+4x+12

    std::cout << "\n=== Binary operators ===\n";
    Polynomial a("x^2 + 1");
    Polynomial b("x + 2");
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "a + b = " << (a + b) << '\n';   // x^2+x+3
    std::cout << "a - b = " << (a - b) << '\n';   // x^2-x-1
    std::cout << "a * b = " << (a * b) << '\n';   // x^3+2x^2+x+2
    std::cout << "a + 5 = " << (a + 5) << '\n';   // x^2+6
    std::cout << "5 + a = " << (5 + a) << '\n';   // x^2+6
    std::cout << "a - 1 = " << (a - 1) << '\n';   // x^2
    std::cout << "3 - a = " << (3 - a) << '\n';   // -x^2+2
    std::cout << "a * 3 = " << (a * 3) << '\n';   // 3x^2+3
    std::cout << "3 * a = " << (3 * a) << '\n';   // 3x^2+3

    std::cout << "\n=== Zero polynomial ===\n";
    Polynomial zero;
    std::cout << zero << '\n';                     // 0
    std::cout << deg(zero) << '\n';                // -1

    return 0;
}
