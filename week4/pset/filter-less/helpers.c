#include "helpers.h"
#include <math.h>
#include <string.h>

int min(int a, int b) {
    return (a > b) ? b : a;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            int avg = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            int originalRed = image[h][w].rgbtRed;
            int originalGreen = image[h][w].rgbtGreen;
            int originalBlue = image[h][w].rgbtBlue;
            image[h][w].rgbtRed = min(round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue), 255);
            image[h][w].rgbtGreen = min(round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue), 255);
            image[h][w].rgbtBlue = min(round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue), 255);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width / 2; w++) {
            int originalRed = image[h][w].rgbtRed;
            int originalGreen = image[h][w].rgbtGreen;
            int originalBlue = image[h][w].rgbtBlue;

            image[h][w].rgbtRed = image[h][width - w - 1].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - w - 1].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width - w - 1].rgbtBlue;

            image[h][width - w - 1].rgbtRed = originalRed;
            image[h][width - w - 1].rgbtGreen = originalGreen;
            image[h][width - w - 1].rgbtBlue = originalBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE imageCopy[height][width];

    // Loop through each row and column
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            imageCopy[i][j] = image[i][j]; // Copy each element
        }
    }

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            float pixelCount = 0;
            int pixelSumRed = 0;
            int pixelSumGreen = 0;
            int pixelSumBlue = 0;
            for (int i = h - 1; i <= h + 1 && i < height; i++) {
                for (int j = w - 1; j <= w + 1 && j < width; j++) {
                    if (i >= 0 && j >= 0) {
                        pixelSumRed += imageCopy[i][j].rgbtRed;
                        pixelSumGreen += imageCopy[i][j].rgbtGreen;
                        pixelSumBlue += imageCopy[i][j].rgbtBlue;
                        pixelCount += 1;
                    }
                }
            }

            int pixelAverageRed = round(pixelSumRed / pixelCount);
            int pixelAverageGreen = round(pixelSumGreen / pixelCount);
            int pixelAverageBlue = round(pixelSumBlue / pixelCount);

            image[h][w].rgbtRed = pixelAverageRed;
            image[h][w].rgbtGreen = pixelAverageGreen;
            image[h][w].rgbtBlue = pixelAverageBlue;
        }
    }
}
