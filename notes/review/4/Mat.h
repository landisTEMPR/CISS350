#ifndef MAT_H
#define MAT_H

class Mat
{
  public:
    Mat(int nrows, int ncols);
    // private:
    int nrows_;
    int ncols_;
    int * p_;
};

std::ostream & operator<<(std::ostream &, const Mat &);

#endif
