#ifndef Vector_hpp
#define Vector_hpp

#include <vector>

class Vector {
public:
    std::vector<double> v;
    int n;
    
    Vector();
    Vector(int size);
    Vector(double values);
    Vector(std::vector<double> values);
    
    double& operator[](int index);
};

#endif