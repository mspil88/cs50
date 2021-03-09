#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over each row and each pixel, average RBG and assign the average value

    int avg;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++) {
            avg = ceil((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = avg, image[i][j].rgbtGreen = avg, image[i][j].rgbtBlue = avg;
        }
    }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {

            int sep_red = 0;
            int sep_green = 0;
            int sep_blue = 0;

            sep_red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sep_green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sep_blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if(sep_red > 255) {
                sep_red = 255;
            }
            if(sep_green > 255) {
                sep_green = 255;
            }
            if(sep_blue > 255) {
                sep_blue = 255;
            }

            image[i][j].rgbtRed = sep_red;
            image[i][j].rgbtGreen = sep_green;
            image[i][j].rgbtBlue = sep_blue;


        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++) {
            for(int k = j+1; k < width; k++) {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][k];
                image[i][k] = temp;
            }
        }
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //TODO: This is not working as intended, seems to slightly darken the image, needs fixing

    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            temp[i][j] = image[i][j];

            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            if(i == 0 && j == 0) {
                for(int r = 0; r <=1; r++) {
                    for(int c = 0; c <=1; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check1: ");
                        }
                    }
                }
            if(i == 0 && (j > 0 && j < width-1)) {
                for(int r = 0; r <=1; r++) {
                    for(int c = j-1; c <= j+1; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check2: ");
                        }
                    }
            }
            if(i > 0 && j == 0) {
                for(int r = i-1; r <= i+1; r++) {
                    for(int c = j; c <= j+1; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check3: ");
                        }
                    }
            }
            if(i > 0 && (j > 0 && j < width-1)) {
                for(int r = i-1; r <= i+1; r++) {
                    for(int c = j-1; c <= j+1; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check4: ");
                    }
                }
            }
            if(i == 0 && (j == width-1)) {
                for(int r = 0; r <=1; r++) {
                    for(int c = j-1; c <= j; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check5: ");
                        }
                    }
            }
            if(i > 0 && (j == width)) {
                for(int r = i-1; r <=i+1; r++) {
                    for(int c = j-1; c <= j; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check6: ");
                        }
                    }
            }
            if((i == height - 1) && (j == width-1)) {
                for(int r = i-1; r <=i; r++) {
                    for(int c = j-1; c <= j; c++) {
                        red += temp[r][c].rgbtRed;
                        green += temp[r][c].rgbtGreen;
                        blue += temp[r][c].rgbtBlue;
                        count +=1;
                        printf("check7: ");
                        }
                    }
            }


            if(red == 0 && green == 0 && blue == 0) {
                count = 1.0;
            }
            image[i][j].rgbtRed = round(red/(count*1.0));
            image[i][j].rgbtGreen = round(green/(count*1.0));
            image[i][j].rgbtBlue = round(blue/(count*1.0));
            printf("%i %i %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);

                }
            }

        return;
        }

