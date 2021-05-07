#include <iostream>
#include "Vector.hpp"
#include "Network.hpp"

int main()
{
    // массив входных обучающих векторов
    std::vector<Vector> X = {
        Vector({0, 0}),
        Vector({0, 1}),
        Vector({1, 0}),
        Vector({1, 1})};

    // массив выходных обучающих векторов
    std::vector<Vector> Y = {
        Vector(0.0),
        Vector(1.0),
        Vector(1.0),
        Vector(0.0),
    };

    auto network = Network({2, 3, 1});

    network.Train(X, Y, 0.5, 1e-7, 1e+5);

    for (int i = 0; i < 4; i++)
    {
        auto output = network.Forward(X[i]);
        printf("X: %1.0f %1.0f,  Y: %1.0f,  output: %f\n", X[i][0], X[i][1], Y[i][0], output[0]);
    }

    return 0;
}
