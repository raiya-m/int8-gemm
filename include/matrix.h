#pragma once 

#include <vector>
#include <stdexcept> 

template <typename T> 

class Matrix {
public: 
    int rows;
    int cols; 
    std::vector<T> data; 

    Matrix(int rows, int cols)
        : rows(rows), cols(cols), data(rows * cols) {}

    // writable access 

    T& operator() (int row, int col) {
        return data[row * cols + col];
    }

    // read-only access for const matrices 
    const T& operator() (int row, int col) const {
        return data[row * cols + col];
    }
};