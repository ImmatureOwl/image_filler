#define CLOVE_SUITE_NAME FillerTest
#include "clove-unit.h"
#include "filler.h"

CLOVE_TEST(FillOnePixelImageWithSuccess) 
{   
    uint8_t source[3] = {255, 0, 0};
    int width = 1;
    int height = 1;
    int channels = 3;

    int pixel_x = 0;
    int pixel_y = 0;
    filler_color_t green = {0, 255, 0};

    uint8_t* filled = filler_execute(source, width, height, channels, pixel_x, pixel_y, green);

    CLOVE_INT_EQ(0, filled[0]);
    CLOVE_INT_EQ(255, filled[1]);
    CLOVE_INT_EQ(0, filled[2]);
}

CLOVE_TEST(FillOnePixelImageWithFailurePixelOutOfRange) 
{   
    uint8_t source[3] = {255, 0, 0};
    int width = 1;
    int height = 1;
    int channels = 3;

    filler_color_t green = {0, 255, 0};
    CLOVE_NULL(filler_execute(source, width, height, channels, -1, 0, green))
    CLOVE_NULL(filler_execute(source, width, height, channels,  1, 0, green))
    CLOVE_NULL(filler_execute(source, width, height, channels,  0,-1, green))
    CLOVE_NULL(filler_execute(source, width, height, channels,  0, 1, green))
}

CLOVE_TEST(FillTwoPixelImage_WithTwoPixelsFilled)
{
    uint8_t source[6] = {255,0,0,  255,0,0};
    int width = 2;
    int height = 1;
    int channels = 3;

    int pixel_x = 1;
    int pixel_y = 0;
    filler_color_t green = {0, 255, 0};

    uint8_t* filled = filler_execute(source, width, height, channels, pixel_x, pixel_y, green);
    CLOVE_INT_EQ(  0, filled[0]);
    CLOVE_INT_EQ(255, filled[1]);
    CLOVE_INT_EQ(  0, filled[2]);
    CLOVE_INT_EQ(  0, filled[3]);
    CLOVE_INT_EQ(255, filled[4]);
    CLOVE_INT_EQ(  0, filled[5]);
}

CLOVE_TEST(FillNinePixelImage_WithOnlyFivePixelsFilled)
{
    uint8_t source[27] = 
    {   
        0,0,255,  255,0,0,  0,0,255, 
        255,0,0,  255,0,0,  255,0,0, 
        0,0,255,  255,0,0,  0,0,255
    };
    int width = 3;
    int height = 3;
    int channels = 3;

    int pixel_x = 1;
    int pixel_y = 1;
    filler_color_t green = {0, 255, 0};

    uint8_t* filled = filler_execute(source, width, height, channels, pixel_x, pixel_y, green);
    
    //Row1
    CLOVE_INT_EQ(  0, filled[0]);
    CLOVE_INT_EQ(  0, filled[1]);
    CLOVE_INT_EQ(255, filled[2]);

    CLOVE_INT_EQ(  0, filled[3]);
    CLOVE_INT_EQ(255, filled[4]);
    CLOVE_INT_EQ(  0, filled[5]);

    CLOVE_INT_EQ(  0, filled[6]);
    CLOVE_INT_EQ(  0, filled[7]);
    CLOVE_INT_EQ(255, filled[8]);

    //Row2
    CLOVE_INT_EQ(  0, filled[9]);
    CLOVE_INT_EQ(255, filled[10]);
    CLOVE_INT_EQ(  0, filled[11]);

    CLOVE_INT_EQ(  0, filled[12]);
    CLOVE_INT_EQ(255, filled[13]);
    CLOVE_INT_EQ(  0, filled[14]);

    CLOVE_INT_EQ(  0, filled[15]);
    CLOVE_INT_EQ(255, filled[16]);
    CLOVE_INT_EQ(  0, filled[17]);

    //Row3
    CLOVE_INT_EQ(  0, filled[18]);
    CLOVE_INT_EQ(  0, filled[19]);
    CLOVE_INT_EQ(255, filled[20]);

    CLOVE_INT_EQ(  0, filled[21]);
    CLOVE_INT_EQ(255, filled[22]);
    CLOVE_INT_EQ(  0, filled[23]);

    CLOVE_INT_EQ(  0, filled[24]);
    CLOVE_INT_EQ(  0, filled[25]);
    CLOVE_INT_EQ(255, filled[26]);
}