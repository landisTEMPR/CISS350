// File : vector.h
// Author : Brysen Landis
#ifndef VECTOR_H
#define VECTOR_H


template < typename T >
class vector
{
  public:
    class iterator;
    class const_iterator;
    class iterator
    {
      public:
      iterator(T * const p)
          : p_(p)
        {}
        
        iterator & operator++()
        {
            p_++;
            return *this;
        }
        
        const iterator operator++(int)
        {
            iterator old(p_);
            p_++;
            return old;
        }

        iterator & operator--()
        {
            p_--;
            return *this;
        }

        const iterator operator--(int)
        {
            iterator old(p_);
            p_--;
            return old;
        }

        iterator & operator+=(int n)
        {
            p_ += n;
            return *this;
        }

        iterator & operator-=(int n)
        {
            p_ -= n;
            return *this;
        }
        
        const T & operator*() const
        {
            return *p_;
        }
        
        T & operator*()
        {
            return *p_;
        }
        
        // This is used by const_iterator(const iterator &)
        
        T * p() const
        {
            return p_;
        }

        bool operator==(const iterator & other) const
        {
            return p_ == other.p_;
        }

        bool operator!=(const iterator & other) const
        {
            return p_ != other.p_;
        }
        
      private:
        T * p_;
    };

    
    class const_iterator
    {
      public:
        const_iterator(T * p)
            : p_(p)
        {}
        
        const_iterator(const iterator & p)
          : p_(p.p())
        {}
        
        const_iterator & operator++()
        {
            p_++;
            return *this;
        }
        
        const const_iterator operator++(int)
        {
            const_iterator old(p_);
            p_++;
            return old;
        }

        const_iterator & operator--()
        {
            p_--;
            return *this;
        }

        const const_iterator operator--(int)
        {
            const_iterator old(p_);
            p_--;
            return old;
        }
        
        const T & operator*() const
        {
            return *p_;

        }

        bool operator==(const const_iterator & other) const
        {
            return p_ == other.p_;
        }

        bool operator!=(const const_iterator & other) const
        {
            return p_ != other.p_;
        }
        
      private:
        T * p_;
    };

    
  vector(int size, T val)
      : capacity_(size), size_(size), p_(new T[size])
    {
        for (int i = 0; i < size; ++i)
        {
            p_[i] = val;
        }
    }
    
    ~vector()
    {
        delete[] p_;
    }

    vector(const vector & other)
        : capacity_(other.capacity_), size_(other.size_),
        p_(new T[other.capacity_])
    {
        for (int i = 0; i < size_; ++i)
        {
            p_[i] = other.p_[i];
        }
    }
    
    vector & operator=(const vector & other)
    {
        if (this != &other)
        {
            delete[] p_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            p_ = new T[capacity_];
            for (int i = 0; i < size_; ++i)
            {
                p_[i] = other.p_[i];
            }
        }
        return *this;
    }
     
    iterator begin()
    {
        return iterator(p_);
    }
    
    const_iterator begin() const
    {
        return const_iterator(p_);
    }
    
    iterator end()
    {
        return iterator(p_ + size_);
    }
    
    const_iterator end() const
    {
        return const_iterator(p_ + size_);
    }
    
    const T & operator[](int i) const
    {
        return p_[i];
    }
    
    T & operator[](int i)
    {
        return p_[i];
    }

    int size() const { return size_; }
    
  private:
    int capacity_;
    int size_;
    T * p_;
};


#endif
