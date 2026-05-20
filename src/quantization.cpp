#include "quantization.h"
#include <cmath> 
#include <algorithm> 

// draft version: 
// int8_t quantize_to_int8(float value, float scale) {
//     int8_t quantized_result = std::round(value/scale);
//     return quantized_result;
// }

// we can't do this because we left it overflow/wrap which is dangerous. thus, we need to saturate/clamp the value. 
// ex. -131 is too small for int8, so we just store the closest representable int8 value -> best representable answer in int8. 

int8_t quantize_to_int8(float value, float scale) {
    float scaled = value / scale;
    int32_t rounded = std::round(scaled); // explicitly just make it 32 bits before we squeeze it into 8 bit rep

    if (rounded > 127) {
        rounded = 127; 
    }

    if (rounded < -128) {
        rounded = -128;
    }

    // convert @ compile time 

    int8_t rounded_int8 = static_cast<int8_t>(rounded);
    return rounded_int8;
}