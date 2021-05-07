#ifndef Network_hpp
#define Network_hpp

#include "Matrix.hpp"
#include "Vector.hpp"
#include <vector>

struct LayerT {
    Vector x; // вход слоя
    Vector z; // активированный выход слоя
    Vector df; // производная функция активации слоя
    
    LayerT(Vector x, Vector z, Vector df) {
        this->x = x;
        this->z = z;
        this->df = df;
    }
};

class Network {
private:
    std::vector<Matrix> weights; // матрицы весов слоя
    std::vector<Vector> deltas; // дельты ошибки на каждом слое
    
    int layersN;

    // значения на каждом слое
    std::vector<LayerT> L;
    
public:
    Network(std::vector<int> sizes);

    Vector Forward(Vector input);
    
    void Backward(Vector output, double &error);
    void UpdateWeights(double alpha);
    
    void Train(std::vector<Vector> X, std::vector<Vector> Y, double aplha, double eps, int epochs);
};

#endif
