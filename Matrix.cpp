#include "Matrix.hpp"
#include <time.h>

Matrix::Matrix(int n, int m) {
    this->n = n;
    this->m = m;
    
    this->v = std::vector<std::vector <double> >(n);
    
    for (size_t i = 0; i < n; i++) {
        this->v[i] = std::vector<double>(m);

        for (size_t j = 0; j < m; j++) {
            v[i][j] = ((float) rand() / RAND_MAX) - 0.5;
        }
    }
}
