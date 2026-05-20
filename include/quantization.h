#pragma once 
#include <cstdint> 

int8_t quantize_to_int8(float value, float scale);
float dequantize_from_int8(int8_t value, float scale);
float dequantize_accumulator(int32_t accumulator, float input_scale, float weight_scale);