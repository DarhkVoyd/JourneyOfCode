#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // The two loops selects a pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Takes average of a color and passes it to each color
            image[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // The two loops selects a pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Saving Original Pixels
            RGBTRIPLE temp;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;

            // Transforming First Half of the Image
            image[i][j].rgbtBlue = image[i][(width - 1 - j)].rgbtBlue;
            image[i][j].rgbtGreen = image[i][(width - 1 - j)].rgbtGreen;
            image[i][j].rgbtRed = image[i][(width - 1 - j)].rgbtRed;

            // Transforming Second Half of the Image
            image[i][(width - 1 - j)].rgbtBlue = temp.rgbtBlue;
            image[i][(width - 1 - j)].rgbtGreen = temp.rgbtGreen;
            image[i][(width - 1 - j)].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialsation of variables required
    RGBTRIPLE temp_image[height][width];
    int sumBlue = 0;
    int sumGreen = 0;
    int sumRed = 0;
    int a = 0;
    int b = 0;
    int pixelCount = 0;

    //Selection of each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            a = 0;
            b = 0;
            pixelCount = 0;

            // Sumation of 3x3 Grid Pixels & Pixels Counted
            while (a < 3)
            {
                b = 0;
                while (b < 3)
                {
                    if ((i - 1 + a) < 0 || (j - 1 + b) < 0 || (i - 1 + a) >= height || (j - 1 + b) >= width)
                    {
                        sumBlue = sumBlue + 0;
                        sumGreen = sumGreen + 0;
                        sumRed = sumRed + 0;
                        b++;
                    }
                    else
                    {
                        sumBlue = sumBlue + image[i - 1 + a][j - 1 + b].rgbtBlue;
                        sumGreen = sumGreen + image[i - 1 + a][j - 1 + b].rgbtGreen;
                        sumRed = sumRed + image[i - 1 + a][j - 1 + b].rgbtRed;
                        b++;
                        pixelCount++;
                    }
                }
                a++;
            }

            // Calculating New Pixel Colors and storing in a temporary image
            temp_image[i][j].rgbtBlue = round((float)sumBlue / pixelCount);
            temp_image[i][j].rgbtGreen = round((float)sumGreen / pixelCount);
            temp_image[i][j].rgbtRed = round((float)sumRed / pixelCount);
        }
    }

    // Copying Temp Image to Original Image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Defining required kernels
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Initialisation of required variables
    RGBTRIPLE temp_image[height][width];
    float GxRed = 0, GyRed = 0;
    float GxGreen = 0, GyGreen = 0;
    float GxBlue = 0, GyBlue = 0;
    int a = 0, b = 0;

    // Selection of each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxRed = 0;
            GyRed = 0;
            GxGreen = 0;
            GyGreen = 0;
            GxBlue = 0;
            GyBlue = 0;
            a = 0;
            b = 0;

            // Calculation of 3x3 Grid weighted mean
            while (a < 3)
            {
                b = 0;
                while (b < 3)
                {
                    if ((i - 1 + a) < 0 || (j - 1 + b) < 0 || (i - 1 + a) >= height || (j - 1 + b) >= width)
                    {
                        GxRed = GxRed + 0;
                        GyRed = GyRed + 0;
                        GxGreen = GxGreen + 0;
                        GyGreen = GyGreen + 0;
                        GxBlue = GxBlue + 0;
                        GyBlue = GyBlue + 0;
                        b++;
                    }
                    else
                    {
                        GxRed = GxRed + (image[(i - 1 + a)][(j - 1 + b)].rgbtRed * Gx[a][b]);
                        GyRed = GyRed + (image[(i - 1 + a)][(j - 1 + b)].rgbtRed * Gy[a][b]);
                        GxGreen = GxGreen + (image[(i - 1 + a)][(j - 1 + b)].rgbtGreen * Gx[a][b]);
                        GyGreen = GyGreen + (image[(i - 1 + a)][(j - 1 + b)].rgbtGreen * Gy[a][b]);
                        GxBlue = GxBlue + (image[(i - 1 + a)][(j - 1 + b)].rgbtBlue * Gx[a][b]);
                        GyBlue = GyBlue + (image[(i - 1 + a)][(j - 1 + b)].rgbtBlue * Gy[a][b]);
                        b++;
                    }
                }
                a++;
            }

            // Calculating New Color Pixels
            GxRed = sqrt((GxRed * GxRed) + (GyRed * GyRed));
            GxGreen = sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen));
            GxBlue = sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue));
            if (GxRed > 255)
            {
                GxRed = 255;
            }
            if (GxGreen > 255)
            {
                GxGreen = 255;
            }
            if (GxBlue > 255)
            {
                GxBlue = 255;
            }

            // Storing in a Temp Image
            temp_image[i][j].rgbtRed = round(GxRed);
            temp_image[i][j].rgbtGreen = round(GxGreen);
            temp_image[i][j].rgbtBlue = round(GxBlue);
        }
    }

    // Copying the Temp Image to Original Image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
        }
    }
    return;
}
