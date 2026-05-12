#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "encryption.h"

/*===================================================================================================
 * read_pgm - Reads a grayscale PGM to memory
 * - filename: path to input file
 * - width: pointer to store image width
 * - height: pointer to store image height
 *
 * - returns 1D array of pixel values
 * - pixel is stored in memory as unsigned char (0 - 255 grayscale)
 * - read_pgm inputs:
 * - const char*filename - a string containing a filename. const means it won't change
 * - int*w points to the width
 * - int*h points to the height 
====================================================================================================*/
unsigned char* read_pgm(const char* filename, int* width, int* height)
{
    char pgm[3];          /*Stores the PGM type, P2 and P5*/
    int binary;             /*if binary = 1, it is P5. If binary = 0, it is P2*/
    int max_pixel;             /*Stores max pixel value of 255*/
    char line[256];         /*Stores one line at a time*/
    int got_imgdim = 0;       /*for finding image width and height*/
    int got_maxpix = 0;     /*for finding maximum pixel value*/
    size_t pixel_count;            /*Stores number of pixels*/
    unsigned char *pixel_array;    /*Points to where image pixels are stored*/
    size_t pixel_index;               /*used as a counter. size_t is an unsigned interger type it cannot store negative numbers*/ 


/*===================================================================================================
 * - FILE*fb - file pointer to access file
 * - fopen(...) - opens file
 * - "rb" - reads binary
====================================================================================================*/
    FILE *fb = fopen(filename, "rb");

/*===================================================================================================
 * - if (!fb) means if the file pointer is NULL, which means failed to open
 * - stderr - means print to error output 
 * - return NULL - if failed return nothing. NULL means no valid image.
====================================================================================================*/
    if (!fb){
        fprintf(stderr, "Error! Could not open file: '%s' \n", filename);  /*Could change fpringf output*/
        return NULL;
    }

/*==================================================================================================
 * Checks if file is a PGM file and prints error message if it is true. 
===================================================================================================*/
    if (!fgets(pgm, sizeof(pgm), fb) || (strncmp(pgm, "P2", 2) !=0 && 
       strncmp(pgm, "P5", 2) != 0)) {
       fprintf(stderr, "Error! File not in a valid PGM format \n");
       fclose(fb);
       return NULL;
    }

/*===================================================================================================
 * Checks if file binary P5, or not P2. 
====================================================================================================*/
    binary = (pgm[1] == '5');

/*===================================================================================================
 * Loops to read the lines until width, height and pixel value have been found
====================================================================================================*/
while (!got_imgdim && fgets(line, sizeof(line), fb)) {
    if (line[0] == '#') continue;
    if (sscanf(line, "%d %d", width, height) == 2)
        got_imgdim = 1;
}
    
while(got_imgdim && !got_maxpix && fgets(line, sizeof(line), fb)) {
    if (line[0] == '#') continue;
    if (sscanf(line, "%d", &max_pixel) == 1)
        got_maxpix =1;
}

/*===================================================================================================
 * Checks to see if the values found are valid.
====================================================================================================*/
if (*width <= 0 || *height <= 0 || max_pixel <=0 || max_pixel > 255) {
    fprintf(stderr, "Error! Unsupported maxiumum pixel value %d\n", max_pixel);
    fclose(fb);
    return NULL;
}

/*===================================================================================================
 * Checks to see if the width, height and pixel value have been not been found.
====================================================================================================*/
if (!got_imgdim || !got_maxpix) {
    fprintf(stderr, "Error! Missing width, height, or pixel information\n");
    fclose(fb);
    return NULL;
}

/*===================================================================================================
 * Finds the number of pixels in the image.
====================================================================================================*/
pixel_count = (size_t)(*width)*(size_t)(*height);

/*===================================================================================================
 * Allocates memory to store image pixels and checks if it failed.
====================================================================================================*/
pixel_array = (unsigned char*)malloc(pixel_count);
if (pixel_array == NULL) {
    fprintf(stderr, "Error! Memory allocation failed\n");
    fclose(fb);
    return NULL;
}

/*===================================================================================================
 * Reads pixel information if the file is binary, P5.
====================================================================================================*/
if(binary) {
    if(fread(pixel_array, 1, pixel_count, fb) != pixel_count) {
    fprintf(stderr, "Error! Image data upload appears incomplete\n");
    free(pixel_array);
    fclose(fb);
    return NULL;
    }

/*===================================================================================================
 * Reads pixel information if the file is text numbers, P2.
====================================================================================================*/
} else {
size_t pixel_index = 0;
    while (pixel_index < pixel_count){
        int v;
        if(fscanf(fb, "%d", &v) !=1){
            fprintf(stderr,"Error! Image data upload failed near pixel %lu\n",
                   (unsigned long)pixel_index);
            free(pixel_array);
            fclose(fb);
            return NULL;
        }
    pixel_array[pixel_index] = (unsigned char)v;
    } 
}

fclose(fb);
return pixel_array;
}

/*===================================================================================================
 * write_pgm - Writes a grayscale image to a PGM file
 * 
 * - filename: path to output file
 * - image: pointer to 1D pixel array
 * - width: image width
 * - height: image height
 * - returns int of characters it wrote
 * - function write_pgm saves the inputs file name, the actual picture pixels, width and height
 * - int write_pgm - returns a number. 0 success and -1 error
 * - unsigned char - means a one-bye number that can only be positive. char can be used as a tiny interger.
====================================================================================================*/
int write_pgm(const char* filename, unsigned char* pixel_array, int* width, int* height)
{
    FILE* fp;
    size_t num_pix;

    if(pixel_array == NULL || width == NULL || height == NULL || *width <= 0 || *height <= 0) { 
        fprintf(stderr, "Error! Invalid image information provided\n");  
        return -1;
    }

    fp = fopen(filename, "wb"); 
    if (!fp) {     /*if(!fp) - if fp failed to open*/
        fprintf(stderr, "Error! Cannot open '%s' for writing\n", filename); 
        return -1; /*return -1 - return stops the function. -1 is a number to signal an error.*/

}

/*===================================================================================================
 * fprintf(fp, "P5\n%d %d\n 255\n", *width, *height); - before saving the picture, information is
 * provided about it. In the following format:
 * P5
 * (width height)
 * 255
====================================================================================================*/
    fprintf(fp, "P5\n%d %d\n255\n", *width, *height);


/*===================================================================================================
 * - size_t pixel_count - tells how many pixels there are in the picture
 * - fwrite() - where image is the pixel values, writes 1 byte at a time, num_pix is the number of pixels and fb is the file.
 * - if() - != num_pix because it is check if they wrote all the image. 
====================================================================================================*/
    num_pix = (size_t)(*width) * (size_t)(*height); /*Might have to define a structure for size_t*/
    if (fwrite(pixel_array, 1, num_pix, fp) != num_pix) {
        fprintf(stderr, "Error! X-Ray image saved unsucessfully.\n"); 
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

void print_pixels(const char* label, unsigned char* data, int n)
{
    printf("%s: ", label);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main()
{
    printf("Welcome to the medical scan compression and encryption software!\n");

    int input;
    int running = 0;

    while (running == 0)
    {
        printf("What would you like to do?\n1. Read PGM\n2. Write PGM\n3. Compress\n4. Decompress\n5. Encrypt\n6. Decrypt\n7. Exit\n");
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                /* Requires implementation */
            
                /* Read PGM */
                int w, h;
                char filename[] = "dataset/0.pgm";

                unsigned char* img = read_pgm(filename, &w, &h);

                /* Check first 0 pixels */
                print_pixels("Original first 20: ", img, 20);

                int size = w * h;

                printf("Original size: %d\n", size);
                break;
            case 2:
                /* Requires implementation */
                /* write_pgm(); */
                break;
            case 3:
                /* Compress */
                unsigned char* compressed = malloc(size * 2);
                int compressed_size = compress(img, size, compressed);

                print_pixels("Compressed first 20: ", compressed, 20);
                printf("Compressed size: %d\n", compressed_size);
                break;
            case 4:
                /* Requires implementation */
                /* decompress(); */
                break;
            case 5:
                /* Encrypt */
                unsigned char key = key_gen();
                printf("key: %hhu\n", key);
                XOR_cipher_encrypt(compressed, compressed_size, key);

                print_pixels("Encrypted first 20: ", compressed, 20);
                break;
            case 6:
                XOR_cipher_decrypt(compressed, compressed_size);

                print_pixels("Decrypted first 20: ", compressed, 20);
                break;
            case 7:
                printf("Thank you for using our service! Have a good day!\n");
                running = 1;
                break;
            default:
                printf("Please input a number 1-7");
        }
    }

    


}