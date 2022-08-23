#ifndef _MATRIX_
#define _MATRIX_

class Tmatrix
{
private:
     int x_res;
     int y_res;
     int **matrix; 

public:

    Tmatrix(int x_res = 64, int y_res = 64);

    ~Tmatrix();

    void print();
    void fill_rand();
    void setPixel(int, int, int);
};

#endif