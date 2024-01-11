#include "helpers.h"

#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int avg = round(((float)image[i][j].rgbtBlue + image[i][j].rgbtRed +
                             image[i][j].rgbtGreen) /
                            3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sepiaRed = round(.393 * image[i][j].rgbtRed +
                                 .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed +
                                   .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed +
                                  .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255) {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0, k = width - 1, n = width / 2; j < n; j++) {
            int temp_b = image[i][j].rgbtBlue;
            int temp_r = image[i][j].rgbtRed;
            int temp_g = image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][k - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][k - j].rgbtRed;

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

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int red = 0, green = 0, blue = 0, count = 0;

            for (int row = i - 1; row < i + 2; row++) {
              for (int col = j - 1; col < j + 2; col++){
                if (row >=0 && row <  height && col >= 0 && col < width){
                  red += copy_img[row][col].rgbtRed;
                  green += copy_img[row][col].rgbtGreen;
                  blue += copy_img[row][col].rgbtBlue;
                  count++;
                }
              }
            }
            image[i][j].rgbtRed = round((float)red / count);
            image[i][j].rgbtGreen = round((float)green / count);
            image[i][j].rgbtBlue = round((float)blue / count);
        }
    }

    return;
}
