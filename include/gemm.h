#pragma once 

#include "matrix.h"
#include <cstdint> //exact size integer types

// take two float matrices and return 2d float matrix
std::vector<std::vector<float>> multiply_float_matrices(
    const std::vector<std::vector<float>>& A,
    const std::vector<std::vector<float>>& B
);

// take two int8 matrices and return an int32 matrix
std::vector<std::vector<int32_t>> multiply_int8_matrices(
    const std::vector<std::vector<int8_t>>& A,
    const std::vector<std::vector<int8_t>>& B
);