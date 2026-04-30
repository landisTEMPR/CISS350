/***************************
 *
 *  Author : Brysen Landis
 *
 *  File : a13q01.cpp
 *
 * *************************/


#include <iostream>
#include <vector>
#include <list>
#include <string>

unsigned int hash(const std::string & s)
{
    unsigned int h = 0;
    unsigned int power = 1;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        h += (unsigned int)(s[i]) * power;
        power *= 10;
    }
    return h;
}

class HTRow
{
public:
    HTRow(const std::string & key, double value)
        : key_(key), value_(value)
    {}

    const std::string & key() const   { return key_; }
    double value() const              { return value_; }
    double & value()                  { return value_; }

private:
    std::string key_;
    double value_;
};

class KeyError
{};

class HT
{
public:
    HT(int size = 10, double threshold = 0.75)
        : table_(size), num_get_collisions_(0), num_gets_(0),
          threshold_(threshold)
    {}

    void set(std::string key, double value)
    {
        int idx = hash(key) % table_.size();
        for (std::list< HTRow >::iterator it = table_[idx].begin();
             it != table_[idx].end(); ++it)
        {
            if (it->key() == key)
            {
                it->value() = value;
                return;
            }
        }
        table_[idx].push_back(HTRow(key, value));
    }

    double get(const std::string & key)
    {
        int idx = hash(key) % table_.size();
        ++num_gets_;
        for (std::list< HTRow >::iterator it = table_[idx].begin();
             it != table_[idx].end(); ++it)
        {
            if (it->key() == key)
                return it->value();
            ++num_get_collisions_;
        }
        throw KeyError();
    }

    void remove(const std::string & key)
    {
        int idx = hash(key) % table_.size();
        for (std::list< HTRow >::iterator it = table_[idx].begin();
             it != table_[idx].end(); ++it)
        {
            if (it->key() == key)
            {
                table_[idx].erase(it);
                return;
            }
        }
        throw KeyError();
    }

    void clear()
    {
        for (int i = 0; i < (int)table_.size(); ++i)
            table_[i].clear();
        num_gets_ = 0;
        num_get_collisions_ = 0;
    }

    std::vector< std::string > keys() const
    {
        std::vector< std::string > result;
        for (int i = 0; i < (int)table_.size(); ++i)
            for (std::list< HTRow >::const_iterator it = table_[i].begin();
                 it != table_[i].end(); ++it)
                result.push_back(it->key());
        return result;
    }

    void resize(int size)
    {
        std::vector< std::list< HTRow > > old = table_;
        table_.assign(size, std::list< HTRow >());
        num_gets_ = 0;
        num_get_collisions_ = 0;
        for (int i = 0; i < (int)old.size(); ++i)
            for (std::list< HTRow >::iterator it = old[i].begin();
                 it != old[i].end(); ++it)
                set(it->key(), it->value());
    }

    void check_resize()
    {
        if (num_gets_ > 0 &&
            (double)num_get_collisions_ / num_gets_ > threshold_)
            resize((int)table_.size() * 2);
    }

    int bucket_count() const { return (int)table_.size(); }

    friend std::ostream & operator<<(std::ostream & cout, const HT & d);

private:
    std::vector< std::list< HTRow > > table_;
    int num_get_collisions_;
    int num_gets_;
    double threshold_;
};

std::ostream & operator<<(std::ostream & cout, const HT & d)
{
    cout << '{';
    bool first = true;
    for (int i = 0; i < (int)d.table_.size(); ++i)
    {
        for (std::list< HTRow >::const_iterator it = d.table_[i].begin();
             it != d.table_[i].end(); ++it)
        {
            if (!first) cout << ", ";
            cout << it->key() << ':' << it->value();
            first = false;
        }
    }
    cout << '}';
    return cout;
}

int main()
{
    HT d0;
    HT d1(20);

    d0.set("John", 5.2);
    std::cout << d0 << std::endl;       // {John:5.2}

    d0.set("Jane", 3.1);
    d0.set("Bob",  9.9);
    std::cout << d0 << std::endl;       // {John:5.2, Jane:3.1, Bob:9.9}

    d0.set("John", 7.7);               // update existing
    std::cout << d0 << std::endl;       // John updated to 7.7

    std::cout << "get Jane: " << d0.get("Jane") << std::endl;  // 3.1

    try
    {
        d0.get("nobody");
    }
    catch (KeyError &)
    {
        std::cout << "KeyError caught on missing get\n";
    }

    d0.remove("Bob");
    std::cout << d0 << std::endl;       // Bob removed

    try
    {
        d0.remove("Bob");
    }
    catch (KeyError &)
    {
        std::cout << "KeyError caught on missing remove\n";
    }

    std::vector< std::string > k = d0.keys();
    std::cout << "keys: ";
    for (int i = 0; i < (int)k.size(); ++i)
        std::cout << k[i] << ' ';
    std::cout << '\n';

    d0.clear();
    std::cout << "after clear: " << d0 << '\n';  // {}

    std::cout << "resize test:\n";
    HT d2(3);
    d2.set("a", 1); d2.set("b", 2); d2.set("c", 3);
    d2.set("d", 4); d2.set("e", 5);
    std::cout << "before resize buckets=" << d2.bucket_count() << " " << d2 << '\n';
    d2.resize(10);
    std::cout << "after resize buckets=" << d2.bucket_count() << " " << d2 << '\n';

    return 0;
}
