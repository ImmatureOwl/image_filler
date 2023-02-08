#define CLOVE_SUITE_NAME FillerImageTest
#include "clove-unit.h"
#include "filler.h"
#include <string.h>
#include <stdlib.h>

#include "stb_image.h"

char* concat_path(const char* path1, const char* path2) 
{
    int dest_size = strlen(path1) + strlen(path2) + 1;
    char* dest = (char*)malloc(dest_size);
    dest[0] = '\0';
    strcat_s(dest, dest_size, path1);
    strcat_s(dest, dest_size, path2);
    return dest;
}

CLOVE_TEST(FillOnePixelImageWithSuccess) 
{   
    const char* base_test_path = CLOVE_EXEC_BASE_PATH();
    const char* source_path = concat_path(base_test_path, "\\resources\\red_1x1.png");
    const char* dest_path = concat_path(base_test_path,   "\\resources\\red_1x1_filled_green.png");
    
    filler_color_t green = {0, 255, 0};
    
    filler_image(source_path, dest_path, 0, 0, green);

    //read dest_path
    int width, height, channels;
    unsigned char* data = stbi_load(dest_path, &width, &height, &channels, 0);
    //check is green
    CLOVE_INT_EQ(1, width);
    CLOVE_INT_EQ(1, height);
    CLOVE_INT_EQ(3, channels);
    CLOVE_INT_EQ(  0, data[0]);
    CLOVE_INT_EQ(255, data[1]);
    CLOVE_INT_EQ(  0, data[2]);
}

CLOVE_TEST(FillImage_640x480) 
{   
    const char* base_test_path = CLOVE_EXEC_BASE_PATH();
    const char* source_path = concat_path(base_test_path, "\\resources\\red_640x480.png");
    const char* dest_path = concat_path(base_test_path,   "\\resources\\red_640x480_filled_green.png");
    const char* expe_path = concat_path(base_test_path,   "\\resources\\green_640x480.png");
    
    filler_color_t green = {0, 255, 0};
    filler_image(source_path, dest_path, 0, 0, green);

    //read dest_path
    int width, height, channels;
    unsigned char* data = stbi_load(dest_path, &width, &height, &channels, 0);
    CLOVE_NOT_NULL(data);

    //check is green
    CLOVE_INT_EQ(640, width);
    CLOVE_INT_EQ(480, height);
    CLOVE_INT_EQ(3, channels);

    unsigned char* expe_data = stbi_load(expe_path, &width, &height, &channels, 0);
    CLOVE_NOT_NULL(expe_data);
    
    int size = 640*480*3;
    CLOVE_INT_EQ(0, memcmp(expe_data, data, size));
}

CLOVE_TEST(FillImage_64x64) 
{   
    const char* base_test_path = CLOVE_EXEC_BASE_PATH();
    const char* source_path = concat_path(base_test_path, "\\resources\\red_64x64.png");
    const char* dest_path = concat_path(base_test_path,   "\\resources\\red_64x64_filled_green.png");
    const char* expe_path = concat_path(base_test_path,   "\\resources\\green_64x64.png");
    
    filler_color_t green = {0, 255, 0};
    filler_image(source_path, dest_path, 0, 0, green);

    //read dest_path
    int width, height, channels;
    unsigned char* data = stbi_load(dest_path, &width, &height, &channels, 0);
    CLOVE_NOT_NULL(data);

    //check is green
    CLOVE_INT_EQ(64, width);
    CLOVE_INT_EQ(64, height);
    CLOVE_INT_EQ(3, channels);

    unsigned char* expe_data = stbi_load(expe_path, &width, &height, &channels, 0);
    CLOVE_NOT_NULL(expe_data);
    
    int size = 64*64*3;
    CLOVE_INT_EQ(0, memcmp(expe_data, data, size));
}

CLOVE_TEST(FillImage_3x3) 
{   
    const char* base_test_path = CLOVE_EXEC_BASE_PATH();
    const char* source_path = concat_path(base_test_path, "\\resources\\red_cross_3x3.png");
    const char* dest_path = concat_path(base_test_path,   "\\resources\\red_cross_3x3_filled_green.png");
    const char* expe_path = concat_path(base_test_path,   "\\resources\\green_cross_3x3.png");
    
    filler_color_t green = {0, 255, 0};
    filler_image(source_path, dest_path, 1, 1, green);

    //read dest_path
    int width, height, channels;
    unsigned char* data = stbi_load(dest_path, &width, &height, &channels, 0);
    CLOVE_NOT_NULL(data);

    //check is green
    CLOVE_INT_EQ(3, width);
    CLOVE_INT_EQ(3, height);
    CLOVE_INT_EQ(3, channels);

    unsigned char* expe_data = stbi_load(expe_path, &width, &height, &channels, 0);
    CLOVE_NOT_NULL(expe_data);
    
    int size = 3*3*3;
    CLOVE_INT_EQ(0, memcmp(expe_data, data, size));
}