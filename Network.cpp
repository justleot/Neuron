#include "Network.hpp"
#include <math.h>

Network::Network(std::vector<int> sizes) {
    this->layersN = (int) sizes.size() - 1;
    
    for (int k = 1; k < sizes.size(); k++) {
        this->weights.push_back(Matrix(0, 0));
        this->L.push_back(LayerT(0, 0, 0));
        this->deltas.push_back(Vector());
        
        // пишет в массив weights
        this->weights[k - 1] = Matrix(sizes[k], sizes[k-1]);
        
        // пишет в массив L
        this->L[k - 1] = LayerT(
            Vector(sizes[k - 1]),
            Vector(sizes[k]),
            Vector(sizes[k])
        );
        
        // пишем в массив deltas
        this->deltas[k - 1] = Vector(sizes[k]);
    }
}


Vector Network::Forward(Vector input) {
    for (int k=0; k < this->layersN; k++) {
        if (k == 0) {
            for (int i = 0; i < input.n; i++) {
                this->L[k].x[i] = input[i];
            }
        }
        
        else {
            for (int i = 0; i < this->L[k - 1].z.n; i++) {
                this->L[k].x[i] = this->L[k - 1].z[i];
            }
        }
        
        for (int i = 0; i < this->weights[k].n; i++) {
            double y = 0;
            
            for (int j = 0; j < this->weights[k].m; j++) {
                y += weights[k][i][j] * this->L[k].x[j];
            }

            this->L[k].z[i] = 1 / (1 + exp(-y));
            this->L[k].df[i] = this->L[k].z[i] * (1 - this->L[k].z[i]);
        }
    }
    
    
    return this->L[layersN - 1].z;
}


void Network::Backward(Vector output, double &error) {
    auto last = this->layersN - 1;
    
    // обнуляем
    error = 0;
    
    for (int i = 0; i < output.n; i++) {
        // находим разность значений векторов
        auto e = this->L[last].z[i] - output[i];
        
        // запоминаем дельту
        this->deltas[last][i] = e * this->L[last].df[i];
       
        // прибавляем к ошибке половину квадрата значения
        error += e * e / 2;
    }
    
    for (int k = last; k > 0; k--) {
        for (int i = 0; i < this->weights[k].m; i++) {
            this->deltas[k - 1][i] = 0;

            for (int j = 0; j < this->weights[k].n; j++) {
                this->deltas[k - 1][i] += this->weights[k][j][i] * this->deltas[k][j];
            }

            // умножаем получаемое значение на производную предыдущего слоя
            this->deltas[k - 1][i] *= L[k - 1].df[i];
        }
    }
}


/**
 * обновление весовых коэффициентов, alpha - скорость обучения
 */
void Network::UpdateWeights(double alpha) {
    for (int k = 0; k < this->layersN; k++) {
        for (int i = 0; i < this->weights[k].n; i++) {
            for (int j = 0; j < this->weights[k].m; j++) {
                weights[k][i][j] -= alpha * this->deltas[k][i] * this->L[k].x[j];
            }
        }
    }
}


void Network::Train(std::vector<Vector> X, std::vector<Vector> Y, double alpha, double eps, int epochs) {
    // номер эпохи
    int epoch = 1;
    
    // ошибка эпохи
    double error;
    
    do {
        error = 0.0; // обнуляем ошибку
        
        // проходимся по всем элементам обучающего множества
        for (int i = 0; i < X.size(); i++) {
            // прямое распространение сигнала
            this->Forward(X[i]);
            
            // обратное распространение ошибки
            this->Backward(Y[i], error);
            
            // обновление весовых коэффициентов
            this->UpdateWeights(alpha);
        }
        
        // выводим в консоль номер эпохи и величину ошибку
        // printf("epoch: %d, error: %f\n", epoch, error);
        
        // увеличиваем номер эпохи
        epoch++;
    } while (epoch <= epochs && error > eps);

}
