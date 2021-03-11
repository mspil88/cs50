#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main(int argc, char *argv[])
{



    typedef uint8_t BYTE;

    if(argc != 2) {
        printf("Usage: %s\n", argv[0]);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("ERROR: File not found\n");
    }

    int size = 512;

    BYTE buffer[size];

    int count = 0;

    char filename[8];

    int found = 0;

    FILE *img;

    int _remainder = 0;
    while(fread(&buffer, size, 1, file) == 1) {

        //identify JPEG file
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            //increment count of JPEGs and create filename
            count++;
            sprintf(filename, "%03i.jpg", count-1);

            //if we haven't found a JPEG yet then we have now (first JPEG)
            if(!found) {
                found = 1
                ;
            }

            // else close down the file
            else{
               fclose(img);
            }

            //open file to write to and then copy over what's in the buffer
            img = fopen(filename, "w");
            fwrite(&buffer, size, 1, img);}


         else {
             //Already found a JPEG therefore continue writing (i.e. the next 512 bytes)
            if(found) {
                fwrite(&buffer, size, 1, img);
            } else {
                continue;
            }
        }}
    fclose(img);
    fclose(file);
    }

