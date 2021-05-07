#ifndef Matrix_hpp
#define Matrix_hpp

#include <vector>

class Matrix
{
private:
    std::vector<std::vector<double>> v;
    
public:
    int n;
    int m;
    Matrix(int n, int m);
    
    class row
    {
        Matrix &_a;
        int _i;
        
        public:
        row(Matrix &a, int i) : _a(a),_i(i) {}
        
        double& operator[](int j) {
            return _a.v[_i][j];
        }
     };
    
    row operator[](int i) {
        return row(*this, i);
    }
 };

#endif