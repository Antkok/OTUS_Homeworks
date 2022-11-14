#include <iostream>
#include <cassert>
#include "lib.h"
#include "matrix.h"

void final_func()
{
    matrix<int, 0> Matrix;
    const int sz = 9;
    for (auto i = 0; i <= sz; ++i){
        Matrix[i][i] = i;
        Matrix[i][sz - i] = sz - i;
    }
    //print_matr(Matrix);
    for (auto i = 1; i < 8; ++i) {
        for (auto j = 1; j < 8; ++j) {
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/// \brief Some examples
int main()
{
    final_func();

    return 0;
}