#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>

int main() 
{
    const char* file_name = "red16x16.png";
    int width, height, channels;

    unsigned char* data = stbi_load(file_name, &width, &height, &channels, 0);

    printf("width: %d, height: %d, channels: %d\n", width, height, channels);
    int size = width * height * channels;
    printf("size: %d\n", size);

    //stbi_image_free(data);

    stbi_write_png("newfile16x16", width, height, channels, data, 0);

    return 0;
}