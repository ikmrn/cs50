#include "helpers.h"

#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    // Traverse through every pixel in the image grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Calculate average and round it to the nearest integer.
            int avg = round(((float)image[i][j].rgbtBlue + image[i][j].rgbtRed +
                             image[i][j].rgbtGreen) /
                            3);
            // Assign red, green, blue to average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    // Traverse through every row
    for (int i = 0; i < height; i++) {
        // Traverse only first half of the columns
        for (int j = 0, k = width - 1, n = width / 2; j < n; j++) {
            // Store red, green, blue in temporary variables
            int temp_b = image[i][j].rgbtBlue;
            int temp_r = image[i][j].rgbtRed;
            int temp_g = image[i][j].rgbtGreen;

            // Assign values from the opposite side of the image to the current
            // side
            image[i][j].rgbtBlue = image[i][k - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][k - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][k - j].rgbtRed;

            // Assign temporary values to the columns on the other side of the
            // image
            image[i][k - j].rgbtBlue = temp_b;
            image[i][k - j].rgbtGreen = temp_g;
            image[i][k - j].rgbtRed = temp_r;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    // Copy the image
    RGBTRIPLE copy_img[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy_img[i][j] = image[i][j];
        }
    }

    // Traverse through every pixel in the image grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Create variables to store red, green, blue and count values
            int red = 0, green = 0, blue = 0, count = 0;
            // Iterate through every neighboring pixel
            for (int row = i - 1; row < i + 2; row++) {
                for (int col = j - 1; col < j + 2; col++) {
                    // Sum red, green, blue if they are in bounds of the image
                    if (row >= 0 && row < height && col >= 0 && col < width) {
                        red += copy_img[row][col].rgbtRed;
                        green += copy_img[row][col].rgbtGreen;
                        blue += copy_img[row][col].rgbtBlue;
                        count++;
                    }
                }
            }
            // Assign averages of new calculated values to the pixel
            image[i][j].rgbtRed = round((float)red / count);
            image[i][j].rgbtGreen = round((float)green / count);
            image[i][j].rgbtBlue = round((float)blue / count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy_img[height + 2][width + 2];
    RGBTRIPLE black = {0, 0, 0};

    // Copy the image with 1px black edges
    for (int i = 0, n = height + 2; i < n; i++) {
        for (int j = 0, m = width + 2; j < m; j++) {
            if (j == 0 || j == m - 1 || i == 0 || i == n - 1) {
                copy_img[i][j] = black;
            } else {
                copy_img[i][j] = image[i - 1][j - 1];
            }
        }
    }

    // Gx matrix
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Gy matrix
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Traverse through every pixel of the image grid
    for (int i = 1, n = height + 1; i < n; i++) {
        for (int j = 1, m = width + 1; j < m; j++) {
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;

            // Loop through adjacent pixels
            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    int row = i + x;
                    int col = j + y;

                    gx_red += copy_img[row][col].rgbtRed * Gx[x + 1][y + 1];
                    gx_green += copy_img[row][col].rgbtGreen * Gx[x + 1][y + 1];
                    gx_blue += copy_img[row][col].rgbtBlue * Gx[x + 1][y + 1];

                    gy_red += copy_img[row][col].rgbtRed * Gy[x + 1][y + 1];
                    gy_green += copy_img[row][col].rgbtGreen * Gy[x + 1][y + 1];
                    gy_blue += copy_img[row][col].rgbtBlue * Gy[x + 1][y + 1];
                }
            }
            image[i - 1][j - 1].rgbtRed =
                fmin(255, round(sqrt(pow(gx_red, 2) + pow(gy_red, 2))));
            image[i - 1][j - 1].rgbtGreen =
                fmin(255, round(sqrt(pow(gx_green, 2) + pow(gy_green, 2))));
            image[i - 1][j - 1].rgbtBlue =
                fmin(255, round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2))));
        }
    }

    return;
}
