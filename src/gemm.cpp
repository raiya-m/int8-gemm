#include "gemm.h"
#include <stdexcept> 

std::vector<std::vector<float>> multiply_float_matrices(
    const std::vector<std::vector<float>>& A,
    const std::vector<std::vector<float>>& B
) {
    int A_rows = A.size();
    int A_cols = A[0].size(); 

    int B_rows = B.size();
    int B_cols = B[0].size();

    if (A_cols != B_rows) {
        throw std::invalid_argument("matrix dimensions do not match :(");
    }

    std::vector<std::vector<float>> C(
        A_rows,
        std::vector<float>(B_cols, 0.0f)
    );

    for(int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            float sum = 0.0f; 

            for (int k = 0; k < A_cols; k++) {
                sum = sum + A[i][k] * B[k][j];
            }

            C[i][j] = sum; 
        }
    }

    return C;
}