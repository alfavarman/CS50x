#include "helpers.h"
#include <math.h>

// get average of RGB for given pixel
int get_average_rgb(RGBTRIPLE pixel)
{
    return round((float)(pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen) / 3);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int row, col, average;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            average = get_average_rgb(image[row][col]);
            // set RGB with average value
            image[row][col] = (RGBTRIPLE)
            {
                average, average, average
            };

        }
    }
    image[row][col] = (RGBTRIPLE)
    {
        average, average, average
    };
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int row, col;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width / 2; col++)
        {
            RGBTRIPLE tmp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = tmp;

        }
    }
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // if we start bluring pix on orginal pic the function wont count correct values.
    RGBTRIPLE copy[height][width];

    int row, col;
    // for each row
    for (row = 0; row < height; row++)
    {
        // for each col
        for (col = 0; col < width; col++)
        {

            int red = 0, blue = 0, green = 0, pix_counter = 0;
            // for neighbouring pixels (range -1, +1)
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    int related_row = row + y;
                    int relatd_col = col + x;
                    // if pixel is NOT out of pixs boundaries
                    if (related_row >= 0 && related_row < height && relatd_col >= 0 && relatd_col < width)
                    {
                        blue += image[related_row][relatd_col].rgbtBlue;
                        red += image[related_row][relatd_col].rgbtRed;
                        green += image[related_row][relatd_col].rgbtGreen;
                        pix_counter++;
                    }
                }
            }
            // blurr
            copy[row][col] = (RGBTRIPLE)
            {
                (int)(round((float)blue / pix_counter)), (int)(round((float)green / pix_counter)), (int)(round((float)red / pix_counter))
            };

        }
    }
    // copy values from copy to image
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            image[row][col] = copy[row][col];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // if we start bluring pix on orginal pic the function wont count correct values.
    RGBTRIPLE copy[height][width];

    int row, col;
    // for each row
    for (row = 0; row < height; row++)
    {
        int red, blue, green;// for each col
        for (col = 0; col < width; col++)
        {
            float redx = 0, bluex = 0, greenx = 0;
            float redy = 0, bluey = 0, greeny = 0;
            float arrx[3][3] = {{-1.0, 0.0, 1.0}, {-2.0, 0.0, 2.0}, {-1.0, 0.0, 1.0}};
            float arry[3][3] = {{-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0}};
            float gx;
            float gy;

            // for neighbouring pixels (range -1, +1)
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {

                    int related_row = row + y;
                    int related_col = col + x;
                    // if pixel is NOT out of pixs boundaries
                    if (related_row >= 0 && related_row < height && related_col >= 0 && related_col < width)
                    {
                        gx = arrx[x + 1][y + 1];
                        gy = arry[x + 1][y + 1];

                        bluex += image[related_row][related_col].rgbtBlue * gx;
                        redx += image[related_row][related_col].rgbtRed * gx;
                        greenx += image[related_row][related_col].rgbtGreen * gx;

                        bluey += image[related_row][related_col].rgbtBlue * gy;
                        redy += image[related_row][related_col].rgbtRed * gy;
                        greeny += image[related_row][related_col].rgbtGreen * gy;
                    }
                }
            }

            red = round(sqrt((redy * redy) + (redx * redx)));
            blue = round(sqrt((bluey * bluey) + (bluex * bluex)));
            green = round(sqrt((greeny * greeny) + (greenx * greenx)));

            if (red > 255)
            {
                red = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            copy[row][col] = (RGBTRIPLE)
            {
                (int) blue, (int) green, (int) red
            };
        }

    }
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            image[row][col] = copy[row][col];
        }
    }
}

