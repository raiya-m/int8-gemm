#include <cuda_runtime.h> 

#include <cstdint> 
#include <iostream> 
#include <vector> 

// macro checks if a cuda api call failed 

#define CUDA_CHECK(call)                                      \
    do {                                                      \
        cudaError_t err = call;                               \
        if (err != cudaSuccess) {                             \
            std::cerr << "cuda error: "                       \
                      << cudaGetErrorString(err)              \
                      << " at line " << __LINE__ << "\n";     \
            std::exit(1);                                     \
        }                                                     \
    } while (0)

