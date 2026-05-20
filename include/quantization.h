#pragma once 
#include <cstdint> 


// pass in a float and we spit out an int8. q = round(x/scale)
int8_t quantize_to_int8(float value, float scale);

// take an int8 and return a float (approximate)
float dequantize_from_int8(int8_t value, float scale);

//interpret the int32 matrix multiplication result (we do acc * input_scale * weight_scale)
float dequantize_accumulator(int32_t accumulator, float input_scale, float weight_scale);