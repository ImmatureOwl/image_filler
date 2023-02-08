#pragma once
#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} filler_color_t; 

/// @brief Run filler algorithm ...
/// @param source_data pixel buffer
/// @param width width of pixel buffer
/// @param height height of pixel buffer
/// @param channels number of channels of pixel buffer
/// @param x pixel x sample position
/// @param y pixel y sample position
/// @param color substitution color
/// @return a reference to the pixel buffer (passed as input) or eventually NULL if algorithm fails
uint8_t* filler_execute(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t color);

/// @brief Run filler on a specific image and save the result to a destionation path
/// @param source_path 
/// @param dest_path 
/// @param x pixel x sample position
/// @param y pixel y sample position
/// @param color substitution color
void filler_image(const char* source_path, const char* dest_path, int x, int y, filler_color_t color);