#include "filler.h"

#include "stb_image.h"
#include "stb_image_write.h"
#include <stdbool.h>
#include "stack.h"

void filler_image(const char* source_path, const char* dest_path, int x, int y, filler_color_t color) 
{
    int width, height, channels;
    unsigned char* data = stbi_load(source_path, &width, &height, &channels, 0);

    unsigned char* data_result = filler_execute(data, width, height, channels, x, y, color);

    if (data_result != NULL) 
    {
        stbi_write_png(dest_path, width, height, channels, data, 0);
    } 

    stbi_image_free(data);
}


static void filler_algo_recurive(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t final_color, filler_color_t sampled_color) 
{
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;

    int current_pixel = (y * width + x) * channels;

    filler_color_t* pixel_color = (filler_color_t*)(&source_data[current_pixel]); 
    if (pixel_color->r != sampled_color.r) return;
    if (pixel_color->g != sampled_color.g) return;
    if (pixel_color->b != sampled_color.b) return;

    pixel_color->r = final_color.r;
    pixel_color->g = final_color.g;
    pixel_color->b = final_color.b;

    filler_algo_recurive(source_data, width, height, channels, x-1, y+0, final_color, sampled_color);
    filler_algo_recurive(source_data, width, height, channels, x+1, y+0, final_color, sampled_color);
    filler_algo_recurive(source_data, width, height, channels, x+0, y-1, final_color, sampled_color);
    filler_algo_recurive(source_data, width, height, channels, x+0, y+1, final_color, sampled_color);
}

static bool filler_pixel_is_visitable(bool* pixel_cache, int width, int height, int x, int y) 
{
    if (x < 0 || x >= width) return false;
    if (y < 0 || y >= height) return false;

    int pixel_index =  y * width + x;
    return  pixel_cache[pixel_index] == false;
}


static void filler_algo_recurive_dyn(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t final_color, filler_color_t sampled_color, bool* pixel_cache) 
{
    int pixel_index =  y * width + x;
    pixel_cache[pixel_index] = true;

    int current_pixel = pixel_index * channels;
    filler_color_t* pixel_color = (filler_color_t*)(&source_data[current_pixel]); 
    if (pixel_color->r != sampled_color.r) return;
    if (pixel_color->g != sampled_color.g) return;
    if (pixel_color->b != sampled_color.b) return;

    pixel_color->r = final_color.r;
    pixel_color->g = final_color.g;
    pixel_color->b = final_color.b;

    if (filler_pixel_is_visitable(pixel_cache, width, height, x-1, y+0))
        filler_algo_recurive_dyn(source_data, width, height, channels, x-1, y+0, final_color, sampled_color, pixel_cache);
    if (filler_pixel_is_visitable(pixel_cache, width, height, x+1, y+0))
        filler_algo_recurive_dyn(source_data, width, height, channels, x+1, y+0, final_color, sampled_color, pixel_cache);
    if (filler_pixel_is_visitable(pixel_cache, width, height, x+0, y-1))
        filler_algo_recurive_dyn(source_data, width, height, channels, x+0, y-1, final_color, sampled_color, pixel_cache);
    if (filler_pixel_is_visitable(pixel_cache, width, height, x+0, y+1))
        filler_algo_recurive_dyn(source_data, width, height, channels, x+0, y+1, final_color, sampled_color, pixel_cache);
}

static void filler_algo_iterative(uint8_t* source_data, int width, int height, int channels,
    filler_color_t final_color, filler_color_t sampled_color, bool* pixel_cache, filler_stacki_t* pixel_stack) 
{
    while (!filler_stacki_is_empty(pixel_stack))
    {
        int pixel_index =  filler_stacki_pop(pixel_stack);

        int current_pixel = pixel_index * channels;
        filler_color_t* pixel_color = (filler_color_t*)(&source_data[current_pixel]); 
        if (pixel_color->r != sampled_color.r) continue;
        if (pixel_color->g != sampled_color.g) continue;
        if (pixel_color->b != sampled_color.b) continue;

        pixel_color->r = final_color.r;
        pixel_color->g = final_color.g;
        pixel_color->b = final_color.b;

        int x = pixel_index % width;
        int y = pixel_index / width;

        if (filler_pixel_is_visitable(pixel_cache, width, height, x-1, y+0)) 
        {
            int next_index = (x-1) + (y+0) * width;
            filler_stacki_push(pixel_stack, next_index);
            pixel_cache[next_index] = true;
        }
        if (filler_pixel_is_visitable(pixel_cache, width, height, x+1, y+0))
        {
            int next_index = (x+1) + (y+0) * width;
            filler_stacki_push(pixel_stack, next_index);
            pixel_cache[next_index] = true;
        }
        if (filler_pixel_is_visitable(pixel_cache, width, height, x+0, y-1))
        {
            int next_index = (x+0) + (y-1) * width;
            filler_stacki_push(pixel_stack, next_index);
            pixel_cache[next_index] = true;
        }
        if (filler_pixel_is_visitable(pixel_cache, width, height, x+0, y+1))
        {
            int next_index = (x+0) + (y+1) * width;
            filler_stacki_push(pixel_stack, next_index);
            pixel_cache[next_index] = true;
        }
        
    }
}

uint8_t* filler_execute(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t final_color) 
{
    if (x < 0 || x >= width) return NULL;
    if (y < 0 || y >= height) return NULL;

    int current_pixel = (y * width + x) * channels;

    filler_color_t sampled_color;
    sampled_color.r = source_data[current_pixel + 0];
    sampled_color.g = source_data[current_pixel + 1];
    sampled_color.b = source_data[current_pixel + 2];

    bool* pixel_cache = (bool*)calloc(width*height, sizeof(bool));
    filler_stacki_t* pixel_stack = filler_stacki_new(width*height);

    int pixel_index = (y * width + x);
    filler_stacki_push(pixel_stack, pixel_index);
    pixel_cache[pixel_index] = true;

    filler_algo_iterative(source_data, width, height, channels, final_color, sampled_color, pixel_cache, pixel_stack);

    free(pixel_cache);
    filler_stacki_free(pixel_stack);
    return source_data;
}