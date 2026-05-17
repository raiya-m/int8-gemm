#pragma once 

#include "matrix.h"
#include <cstdint> 

Matrix<float> gemm_float_reference(
    const Matrix<float>& A,
    const Matrix<float>& B
);

Matrix<int32_t> gemm_int8_basic(
    const Matrix<int8_t>& A,
    const Matrix<int8_t>& B
);
