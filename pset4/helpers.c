#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray = ((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = round(gray);
            image[i][j].rgbtGreen = round(gray);
            image[i][j].rgbtRed = round(gray);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, m = width / 2; j < m; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create separate matrices for each channel for blur filters
    int blue_blur[height][width];
    int green_blur[height][width];
    int red_blur[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            if ((i == 0) && (j == 0))
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                image[i][j + 1].rgbtBlue) / 4);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                                 image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 4);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                               image[i][j + 1].rgbtRed) / 4);
            }
            // bottom right corner
            else if ((i == (height - 1)) && (j == (width - 1)))
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                image[i][j - 1].rgbtBlue) / 4);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                                 image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 4);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                               image[i][j - 1].rgbtRed) / 4);
            }
            //top right corner
            else if ((i == 0) && (j == (width - 1)))
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                image[i][j - 1].rgbtBlue) / 4);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                 image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 4);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                               image[i][j - 1].rgbtRed) / 4);
            }
            // bottom left corner
            else if ((i == (height - 1)) && (j == 0))
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                image[i][j + 1].rgbtBlue) / 4);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                 image[i - 1][j].rgbtGreen + (float) image[i][j + 1].rgbtGreen) / 4);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                               image[i][j + 1].rgbtRed) / 4);
            }
            // top edge
            else if (i == 0)
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen
                                                 + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                 image[i][j - 1].rgbtGreen) / 6);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                               image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed) / 6);
            }
            // bottom edge
            else if (i == (height - 1))
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                                image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                                                 + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                 image[i][j - 1].rgbtGreen) / 6);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                               image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed) / 6);
            }
            // left edge
            else if (j == 0)
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                                                 + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                 image[i][j + 1].rgbtGreen) / 6);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                               image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed) / 6);
            }
            // right edge
            else if (j == (width - 1))
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                                image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue) / 6);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                                                 + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                 image[i][j - 1].rgbtGreen) / 6);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                               image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed) / 6);
            }
            // all pixels that aren't on the edge or corner
            else
            {
                blue_blur[i][j] = round((float)(image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                                image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                image[i][j + 1].rgbtBlue) / 9);
                green_blur[i][j] = round((float)(image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen
                                                 + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                                 image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                 image[i][j + 1].rgbtGreen) / 9);
                red_blur[i][j] = round((float)(image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                               image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                               image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed) / 9);
            }
        }
    }
    // update image channels using blur matrices
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blue_blur[i][j];
            image[i][j].rgbtGreen = green_blur[i][j];
            image[i][j].rgbtRed = red_blur[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create separate matrices for each channel for edge detection
    int blue_edge[height][width];
    int green_edge[height][width];
    int red_edge[height][width];

    // edge detection variables for each channel
    unsigned long bGx, bGy, gGx, gGy, rGx, rGy;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner
            if ((i == 0) && (j == 0))
            {
                bGx = (image[i + 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);
                bGy = (image[i + 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue);
                gGx = (image[i + 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen);
                gGy = (image[i + 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen);
                rGx = (image[i + 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);
                rGy = (image[i + 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed);
            }
            //bottom right corner
            else if ((i == (height - 1)) && (j == (width - 1)))
            {
                bGx = (- image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);
                bGy = (- image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
                gGx = (- image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);
                gGy = (- image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen);
                rGx = (- image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);
                rGy = (- image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed);
            }
            // top right corner
            else if ((i == 0) && (j == (width - 1)))
            {
                bGx = (- image[i + 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);
                bGy = (image[i + 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue);
                gGx = (- image[i + 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);
                gGy = (image[i + 1][j - 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen);
                rGx = (- image[i + 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);
                rGy = (image[i + 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed);
            }
            // bottom left corner
            else if ((i == (height - 1)) && (j == 0))
            {
                bGx = (image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);
                bGy = (- image[i - 1][j + 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
                gGx = (image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen);
                gGy = (- image[i - 1][j + 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen);
                rGx = (image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);
                rGy = (- image[i - 1][j + 1].rgbtRed - 2 * image[i - 1][j].rgbtRed);
            }
            // top edge
            else if (i == 0)
            {
                bGx = (image[i + 1][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);
                bGy = (image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue);
                gGx = (image[i + 1][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen +
                       2 * image[i][j + 1].rgbtGreen);
                gGy = (image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen);
                rGx = (image[i + 1][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);
                rGy = (image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed);
            }
            // bottom edge
            else if (i == (height - 1))
            {
                bGx = (image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);
                bGy = (- image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
                gGx = (image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen +
                       2 * image[i][j + 1].rgbtGreen);
                gGy = (- image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen);
                rGx = (image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);
                rGy = (- image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed);
            }
            // left edge
            else if (j == 0)
            {
                bGx = (image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);
                bGy = (image[i + 1][j + 1].rgbtBlue - image[i - 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
                gGx = (image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen);
                gGy = (image[i + 1][j + 1].rgbtGreen - image[i - 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen -
                       2 * image[i - 1][j].rgbtGreen);
                rGx = (image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);
                rGy = (image[i + 1][j + 1].rgbtRed - image[i - 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed);
            }
            // right edge
            else if (j == (width - 1))
            {
                bGx = (- image[i + 1][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);
                bGy = (image[i + 1][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
                gGx = (- image[i + 1][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);
                gGy = (image[i + 1][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen -
                       2 * image[i - 1][j].rgbtGreen);
                rGx = (- image[i + 1][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);
                rGy = (image[i + 1][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed);
            }
            // all pixels except corners and edges
            else
            {
                bGx = (image[i + 1][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue -
                       2 * image[i][j - 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);
                bGy = (image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue - image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue +
                       2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
                gGx = (image[i + 1][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen
                       - 2 * image[i][j - 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen);
                gGy = (image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen - image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen
                       + 2 * image[i + 1][j].rgbtGreen - 2 * image[i - 1][j].rgbtGreen);
                rGx = (image[i + 1][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed -
                       2 * image[i][j - 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);
                rGy = (image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed - image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed +
                       2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed);
            }

            // cap blue pixel intensity to 255
            if (round(sqrt((double)(bGx * bGx + bGy * bGy))) > 255)
            {
                blue_edge[i][j] = 255;
            }
            else
            {
                blue_edge[i][j] = round(sqrt((double)(bGx * bGx + bGy * bGy)));
            }
            // cap green pixel intensity to 255
            if (round(sqrt((double)(gGx * gGx + gGy * gGy))) > 255)
            {
                green_edge[i][j] = 255;
            }
            else
            {
                green_edge[i][j] = round(sqrt((double)(gGx * gGx + gGy * gGy)));
            }
            // cap red pixel intensity to 255
            if (round(sqrt((double)(rGx * rGx + rGy * rGy))) > 255)
            {
                red_edge[i][j] = 255;
            }
            else
            {
                red_edge[i][j] = round(sqrt((double)(rGx * rGx + rGy * rGy)));
            }
        }
    }
    // update image channels using edge matrics
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blue_edge[i][j];
            image[i][j].rgbtGreen = green_edge[i][j];
            image[i][j].rgbtRed = red_edge[i][j];
        }
    }
    return;
}
