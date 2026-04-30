#ifndef MAXHEAP_VALUE_H
#define MAXHEAP_VALUE_H

#include <iostream>
#include <string>

class maxheap_value
{
public:
    maxheap_value() : priority_(0), s_("") {}

    maxheap_value(int priority, const std::string & s)
        : priority_(priority), s_(s)
    {}

    int get_priority() const         { return priority_; }
    const std::string & get_s() const{ return s_; }

    bool operator>(const maxheap_value & other) const
    {
        return priority_ > other.priority_;
    }

    bool operator<(const maxheap_value & other) const
    {
        return priority_ < other.priority_;
    }

    bool operator==(const maxheap_value & other) const
    {
        return priority_ == other.priority_ && s_ == other.s_;
    }

private:
    int priority_;
    std::string s_;
};

std::ostream & operator<<(std::ostream & cout, const maxheap_value & x)
{
    cout << '<' << x.get_priority() << ", " << x.get_s() << '>';
    return cout;
}

#endif
