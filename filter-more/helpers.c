#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int greyscale = round(((float)image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = greyscale;
            image[i][j].rgbtGreen = greyscale;
            image[i][j].rgbtRed = greyscale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int swap;

    for (int i = 0, k = width - 1; i < height; i++, k = width - 1)
    {
        for (int j = 0; j < width / 2 ; j++, --k)
        {
            swap = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = swap;
            swap = image[i][k].rgbtRed;
            image[i][k].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = swap;
            swap = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = swap;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **new_image = (RGBTRIPLE **) malloc(sizeof(RGBTRIPLE *) * height);
    for (int i = 0; i < height; i++)
    {
        new_image[i] = ((RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width));
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, avr = 0, avr_red = 0, avr_green = 0, avr_blue = 0; j < width ;
             j++, avr = 0, avr_red = 0, avr_green = 0, avr_blue = 0)
        {
            avr_red += image[i][j].rgbtRed;
            avr_green += image[i][j].rgbtGreen;
            avr_blue += image[i][j].rgbtBlue;
            avr++;

            if (i - 1 >= 0)
            {
                avr_red += image[i - 1][j].rgbtRed;
                avr_green += image[i - 1][j].rgbtGreen;
                avr_blue += image[i - 1][j].rgbtBlue;
                avr++;
                if (j  - 1 >= 0)
                {
                    avr_red += image[i - 1][j  - 1].rgbtRed;
                    avr_green += image[i - 1][j  - 1].rgbtGreen;
                    avr_blue += image[i - 1][j  - 1].rgbtBlue;
                    avr++;
                }
                if (j  + 1 < width)
                {
                    avr_red += image[i - 1][j  + 1].rgbtRed;
                    avr_green += image[i - 1][j  + 1].rgbtGreen;
                    avr_blue += image[i - 1][j  + 1].rgbtBlue;
                    avr++;
                }
            }
            if (i + 1 < height)
            {
                avr_red += image[i + 1][j].rgbtRed;
                avr_green += image[i + 1][j].rgbtGreen;
                avr_blue += image[i + 1][j].rgbtBlue;
                avr++;
                if (j  - 1 >= 0)
                {
                    avr_red += image[i + 1][j  - 1].rgbtRed;
                    avr_green += image[i + 1][j  - 1].rgbtGreen;
                    avr_blue += image[i + 1][j  - 1].rgbtBlue;
                    avr++;
                }
                if (j  + 1 < width)
                {
                    avr_red += image[i + 1][j  + 1].rgbtRed;
                    avr_green += image[i + 1][j  + 1].rgbtGreen;
                    avr_blue += image[i + 1][j  + 1].rgbtBlue;
                    avr++;
                }

            }
            if (j  + 1 < width)
            {
                avr_red += image[i][j  + 1].rgbtRed;
                avr_green += image[i][j  + 1].rgbtGreen;
                avr_blue += image[i][j  + 1].rgbtBlue;
                avr++;
            }
            if (j  - 1 >= 0)
            {
                avr_red += image[i][j  - 1].rgbtRed;
                avr_green += image[i][j  - 1].rgbtGreen;
                avr_blue += image[i][j  - 1].rgbtBlue;
                avr++;
            }
            new_image[i][j].rgbtRed = round((float)avr_red / avr);
            new_image[i][j].rgbtGreen = round((float)avr_green / avr);
            new_image[i][j].rgbtBlue = round((float)avr_blue / avr);
        }
    }

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width ; j++)
        {
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
        }
    }
    free(new_image);
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **new_image = (RGBTRIPLE **) malloc(sizeof(RGBTRIPLE *) * height);
    for (int i = 0; i < height; i++)
    {
        new_image[i] = ((RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width));
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0;
            int Gx_blue = 0;
            int Gx_green = 0;
            int Gy_red = 0;
            int Gy_blue = 0;
            int Gy_green = 0;
            int Red = 0;
            int Blue = 0;
            int Green = 0;

            if (i - 1 >= 0)
            {
                Gy_red += image[i - 1][j].rgbtRed * -2;
                Gy_blue += image[i - 1][j].rgbtBlue * -2;
                Gy_green += image[i - 1][j].rgbtGreen * -2;

                if (j - 1 >= 0)
                {
                    Gx_red += image[i - 1][j - 1].rgbtRed * -1;
                    Gx_blue += image[i - 1][j - 1].rgbtBlue * -1;
                    Gx_green += image[i - 1][j - 1].rgbtGreen * -1;

                    Gy_red += image[i - 1][j - 1].rgbtRed * -1;
                    Gy_blue += image[i - 1][j - 1].rgbtBlue * -1;
                    Gy_green += image[i - 1][j - 1].rgbtGreen * -1;
                }
                if (j + 1 < width)
                {
                    Gx_red += image[i - 1][j + 1].rgbtRed * 1;
                    Gx_blue += image[i - 1][j + 1].rgbtBlue * 1;
                    Gx_green += image[i - 1][j + 1].rgbtGreen * 1;

                    Gy_red += image[i - 1][j + 1].rgbtRed * -1;
                    Gy_blue += image[i - 1][j + 1].rgbtBlue * -1;
                    Gy_green += image[i - 1][j + 1].rgbtGreen * -1;

                }

            }
            if (i + 1 < height)
            {

                Gy_red += image[i + 1][j].rgbtRed * 2;
                Gy_blue += image[i + 1][j].rgbtBlue * 2;
                Gy_green += image[i + 1][j].rgbtGreen * 2;
                if (j - 1 >= 0)
                {
                    Gx_red += image[i + 1][j - 1].rgbtRed * -1;
                    Gx_blue += image[i + 1][j - 1].rgbtBlue * -1;
                    Gx_green += image[i + 1][j - 1].rgbtGreen * -1;

                    Gy_red += image[i + 1][j - 1].rgbtRed * 1;
                    Gy_blue += image[i + 1][j - 1].rgbtBlue * 1;
                    Gy_green += image[i + 1][j - 1].rgbtGreen * 1;

                }
                if (j + 1 < width)
                {
                    Gx_red += image[i + 1][j + 1].rgbtRed * 1;
                    Gx_blue += image[i + 1][j + 1].rgbtBlue * 1;
                    Gx_green += image[i + 1][j + 1].rgbtGreen * 1;

                    Gy_red += image[i + 1][j + 1].rgbtRed * 1;
                    Gy_blue += image[i + 1][j + 1].rgbtBlue * 1;
                    Gy_green += image[i + 1][j + 1].rgbtGreen * 1;

                }
            }
            if (j + 1 < width)
            {
                Gx_red += image[i][j + 1].rgbtRed * 2;
                Gx_blue += image[i][j + 1].rgbtBlue * 2;
                Gx_green += image[i][j + 1].rgbtGreen * 2;
            }
            if (j - 1 >= 0)
            {
                Gx_red += image[i][j - 1].rgbtRed * -2;
                Gx_blue += image[i][j - 1].rgbtBlue * -2;
                Gx_green += image[i][j - 1].rgbtGreen * -2;
            }
            if (round(sqrt(pow((double)(Gx_red), 2) + pow((double)(Gy_red), 2))) > 255)
            {
                Red = 255;
            }
            else
            {
                Red = round(sqrt(pow((double)(Gx_red), 2) + pow((double)(Gy_red), 2)));
            }
            if (round(sqrt(pow((double)(Gx_green), 2) + pow((double)(Gy_green), 2))) > 255)
            {
                Green = 255;
            }
            else
            {
                Green = round(sqrt(pow((double)(Gx_green), 2) + pow((double)(Gy_green), 2)));
            }
            if (round(sqrt(pow((double)(Gx_blue), 2) + pow((double)(Gy_blue), 2))) > 255)
            {
                Blue = 255;
            }
            else
            {
                Blue = round(sqrt(pow((double)(Gx_blue), 2) + pow((double)(Gy_blue), 2)));
            }

            new_image[i][j].rgbtRed = Red;
            new_image[i][j].rgbtGreen = Green;
            new_image[i][j].rgbtBlue = Blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
        }
    }
    free(new_image);
    return;
}