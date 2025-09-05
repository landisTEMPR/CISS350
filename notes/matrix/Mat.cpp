#include <iostream>
#include "Mat.h"


Mat::Mat(int nrows, int ncols)
    : nrows_(nrows), ncols_(ncols), p_(new double[nrows * ncols])
{}


Mat::Mat(const Mat & m)
    :nrows_(m.nrows_), ncols_(m.ncols_),
     p_(new double[m.nrows_ * m.ncols_])
{
    for (int i = 0; i < nrows_ * ncols_; ++i)
    {
        p_[i] = m.p_[i];
    }
}

Mat::~Mat()
{
    delete[] p_;
}


const Mat & Mat::operator=(const Mat & m)
{
    if (this != &m)
    {
        nrows_ = m.rows_;
        ncols_ = m.ncols;
        delete[] p_;
        p_ = new double[nrows_ * ncols_];
        for (int i = 0; i < nrows_ * ncols_; ++i)
        {
            p_[i] = m.p_[i];
        }
    }
    return (*this);
}


int Mat::nrows() const
{
    return nrows_;
}


int Mat::ncols() const
{
    return ncols_;
}


double Mat::operator()(int r, int c) const
{
    return *(p_ + r * ncols_ + c);
}


double & Mat::operator()(int r, int c)
{
    return *(p_ + r * ncols_ + c);
}


std::ostream & operator<<(std::ostream & cout, const Mat & m)
{
    for (int r = 0; r < m.nrows(); ++r)
    {
        for (int c = 0; c < m.ncols(); ++c)
        {
            std::cout << m(r, c) << ' ';// m.operator()(r,c)
        }
        std::cout << '\n';
    }
    return cout;
}
