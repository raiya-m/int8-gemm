#pragma once 

#include "matrix.h"
#include <cstdint> //exact size integer types

Matrix<float> gemm_float_reference(
    const Matrix<float>& A,
    const Matrix<float>& B
);

Matrix<int32_t> gemm_int8_basic(
    const std::vector<std::vector<int8_t>>& A,
    const std::vector<std::vector<int8_t>>& B
);

Matrix<int32_t> gemm_int8_tiled(
    const Matrix<int8_t>& A,
    const Matrix<int8_t>& B,
    int tile_size
);

// packs B such that B(k, j) becomes contiguous as packed_B[j * K + k]. lovely!

std::vector<int8_t> pack_B_by_columns(
    const Matrix<int8_t>& B
);

Matrix<int32_t> gemm_int8_packed_B(
    const Matrix<int8_t>& A,
    const std::vector<int8_t>& packed_B,
    int B_rows,
    int B_cols
);