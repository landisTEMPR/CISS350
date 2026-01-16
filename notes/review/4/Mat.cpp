#include <iostream>
#include "Mat.h"

Mat::Mat(int nrows, int ncols)
    : nrows_(nrows), ncols_(ncols),
      p_(new int[nrows * ncols])
{
}

std::ostream & operator<<(std::ostream & cout, const Mat & m)
{
    for (int r = 0; r < m.nrows_; ++r)
    {
        for (int c = 0; c < m.ncols_; ++c)
        {
            std::cout << m.p_[r * m.ncols_ + c] << ", ";
        }
        std::cout << '\n';
    }
    return cout;
}
