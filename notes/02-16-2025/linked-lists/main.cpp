#include <iostream>

class SLNode
{
public:
    SLNode(int key, SLNode * next = NULL)
        : key_(key), next_(next)
    {}
    int key_;
    SLNode * next_;
private:
    
};

std::ostream & operator<<(std::ostream & cout, const SLNode & n)
{
    cout << "<SLNode " << &n
         << " key:" << n.key_ << ", "
         << "next:" << n.next_
         << '>';
    return cout;
}

class SLList
{
public:
    SLList()
        : phead_(NULL)
    {}
    void insert_head(int key)
    {
        phead_ = new SLNode(key, phead_);
    }
    void delete_head()
    {
        if (phead_ == NULL)
        {
            // throw exception
        }
        else
        {
            SLNode * p = phead_;
            phead_ = phead_->next_;
            delete p;
        }
    }   
    void insert_tail(int key)
        {
            if (phead_ == NULL)
            {
                phead_ = new SLNode(key, phead_);
            }
            else
            {
                SLNode * p = phead_;
                while(p->next_ != NULL)
                {
                    p = p->next_;
                }
                p->next_ = new SLNode(key, NULL);
            }
        }
    void delete_tail()
    {
        if (phead_ == NULL)
        {
            // throw exception
        }
        else if (phead_->next_ == NULL)
        {
            delete phead_;
            phead_ = NULL;
        }
        else
        {
            SLNode * p = phead_;
            while(p->next_->next_ != NULL)
            {
                p = p->next_;
            }
            delete p->next_;
            p->next_ = NULL;
        }
    }
    
    SLNode * phead_;
};

std::ostream & operator<<(std::ostream & cout, const SLList & n)
{
    cout << "<SLList " << &n << '\n';
    SLNode * p = n.phead_;
    while (p != NULL)
    {
            std::cout << "    " << (*p) << '\n';
            p = p->next_;
    }
    cout << '>';
    
    return cout;
}

int main()
{
    // create nodes on heap
    SLNode * n5 = new SLNode(5); 
    SLNode * n3 = new SLNode(3); n5->next_ = n3;
    SLNode * n1 = new SLNode(1); n3->next_ = n1;
    SLNode * n7 = new SLNode(7); n1->next_ = n7;

    // SLList list
    // Be able to list.insert_head(42),
    // list.remove_head, list.insert_tail,
    // list.remove_tail.
    
    SLList list;

    // insert ability
    std::cout << "[INSERTION]" << '\n';
    std::cout << list << '\n';
    list.insert_head(0);
    std::cout << list << '\n';
    list.insert_head(1);
    std::cout << list << '\n';
    list.insert_head(3);
    std::cout << list << '\n';
    list.insert_head(5);
    std::cout << list << '\n';

    // delete ability
    std::cout << "[DELETION]" << '\n';
    list.delete_head();
    std::cout << list << '\n';
    list.delete_head();
    list.delete_head();
    std::cout << list << '\n';

    // insert tail
    list.insert_head(5);
    list.insert_head(7);
    list.insert_head(3);
    list.insert_head(9);
    std::cout << "[INSERT TAIL]" << '\n';
    std::cout << list << '\n';
    list.insert_tail(18);
    std::cout << list << '\n';

    // delete tail
    std::cout << "[DELETE TAIL]" << '\n';
    list.delete_tail();
    std::cout << list << '\n';

    return 0;
}
