#include "gemm.h"
#include <stdexcept> 
#include <algorithm> 

// standard float gemm used for the correctness ref

Matrix<float> multiply_float_matrices(
    const Matrix<float>& A,
    const Matrix<float>& B
) {
    if (A.cols != B.rows) {
        throw std::invalid_argument("matrix dimensions do not match :(");
    }

    Matrix<float> C(A.rows, B.cols);

    for(int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            float sum = 0.0f; // floatify the double 

            for (int k = 0; k < A.cols; k++) {
                sum = sum + A(i, k) * B(k, j);
            }

            C(i, j) = sum; 
        }
    }

    return C;
}

// basic int8 gemm: int8 input * int8 weight -> int32 accumulator

Matrix<int32_t> gemm_int8_basic (
    const Matrix<int8_t>& A,
    const Matrix<int8_t>& B
) {
    if (A.cols != B.rows) {
        throw std::invalid_argument("matrix dimensions do not match :(");
    }

    Matrix<int32_t> C(A.rows, B.cols);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            int32_t acc = 0;

            for (int k = 0; k < A.cols; k++) {
                acc = acc + static_cast<int32_t>(A(i, k)) * static_cast<int32_t>(B(k, j));
            }
            C(i, j) = acc;
        }
    }

    return C; 
}

// tiled gemm. process small blocks so data stays in cache longer.

Matrix<int32_t> gemm_int8_tiled(
    const Matrix<int8_t>& A,
    const Matrix<int8_t>& B,
    int tile_size
) {
    if (A.cols != B.rows) {
        throw std::invalid_argument("matrix dimensions do not match :(");
    }

    Matrix<int32_t> C(A.rows, B.cols);

    for (int ii = 0; ii < A.rows; ii += tile_size) {
        for (int jj = 0; jj < B.cols; jj += tile_size) {
            for (int kk = 0; kk < A.cols; kk += tile_size) {
                
                int i_end = std::min(ii + tile_size, A.rows);
                int j_end = std::min(jj + tile_size, B.cols);
                int k_end = std::min(kk + tile_size, A.cols);

                for (int i = ii; i < i_end; i++) {
                    for (int j = jj; j < j_end; j++) {
                        int32_t acc = C(i, j);
                        for (int k = kk; k < k_end; k++) {
                            acc += static_cast<int32_t>(A(i, k)) * 
                            static_cast<int32_t>(B(i, j));
                        }

                        C(i, j) = acc;
                    }
                }
            }
        }
    }
    return C; 
}

// pack B by columns. normal B access in gemm is b(k, j) which walks down a column. cache unfriendly because we have row-major contiguous storage.
// pack columns contiguously instead!

std::vector<int8_t> pack_B_by_columns(
    const Matrix<int8_t>& B
) {
    std::vector<int8_t> packed(B.rows * B.cols);

    for (int j = 0; j < B.cols; j++) {
        for (int k = 0; k < B.rows; k++) {
            packed[j * B.rows + k] = B(k, j);
        }
    }
    return packed;
}

// gemm via packed B. 

Matrix<int32_t> gemm_int8_packed_B (
    const Matrix<int8_t>& A, 
    const std::vector<int8_t>& packed_B,
    int B_rows,
    int B_cols
) {
    if (A.cols != B_rows) {
        throw std::invalid_argument("matrix dimensions do not match :("); 
    }

    Matrix<int32_t> C(A.rows, B_cols); 

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            int32_t acc = 0;

            for (int k = 0; k < A.cols; k++) {
                acc += static_cast<int32_t>(A(i, k)) * 
                static_cast<int32_t>(packed_B[j * B_rows + k]); 
            }
            C(i, j) = acc;
        }
    }
    return C;
}