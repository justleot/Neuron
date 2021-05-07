#include "Vector.hpp"

Vector::Vector() {}

Vector::Vector(int size) {
    this->n = size;
    this->v = std::vector<double>(size);
}

Vector::Vector(double values) {
    this->n = 1;
    this->v = std::vector<double>(this->n);
    
    this->v[0] = values;
}

Vector::Vector(std::vector<double> values) {
    this->n = (int)values.size();
    this->v = std::vector<double>(this->n);
    
    for (size_t i = 0; i < this->n; i++) {
        this->v[i] = values[i];
    }
}

double& Vector::operator[](int index) {
    return this->v[index];
}