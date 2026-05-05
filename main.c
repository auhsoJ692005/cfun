#include <stdio.h>
#include <stdlib.h>
#include "compression.h"
#include "encryption.h"

/*====================
* read_pgm (Elouise)
* ====================
* Reads a grayscale PGM to memory
* 
* filename: path to input file
* width: pointer to store image width
* height: pointer to store image height
*
* returns 1D array of pixel values
*/
unsigned char* read_pgm(const char* filename, int* width, int* height)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file\n");
        return NULL;
    }

    char format[3];
    fscanf(file, "%2s", format);

    /* Check for P5*/
    if (format[0] != 'P' || format[1] != '5')
    {
        printf("Not in P5 format\n");
        fclose(file);
        return NULL;
    }

    /* Skip comments*/
    int c;
    c = fgetc(file);
    while (c == '#')
    {
        while (fgetc(file) != '\n');
        c = fgetc(file);
    }
    ungetc(c, file);

    int max_val;
    fscanf(file, "%d %d", width, height);
    fscanf(file, "%d", &max_val);

    /* Remove whitespace */
    fgetc(file);

    /* Allocate memory for data */
    int size = (*width) * (*height);

    unsigned char* data = (unsigned char*) malloc(size);
    if(!data)
    {
        printf("Memory Allocation Failed\n");
        fclose(file);
        return NULL;
    }

    fread(data, sizeof(unsigned char), size, file);

    fclose(file);
    return data;
}

/*====================
* write_pgm (Elouise)
* ====================
* Writes a grayscale image to a PGM file
* 
* filename: path to output file
* data: pointer to 1D pixel array
* width: image width
* height: image height
*
* returns int of characters it wrote
*/
int write_pgm(const char* filename, unsigned char* data, int* width, int* height)
{
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
    /* Read in File */
    int w, h;
    char filename[] = "dataset/0.pgm";

    unsigned char* img = read_pgm(filename, &w, &h);

    /* Check first 0 pixels */
    print_pixels("Original first 20: ", img, 20);

    int size = w * h;

    /* Compress */
    unsigned char* compressed = malloc(size * 2);
    int compressed_size = compress(img, size, compressed);

    print_pixels("Compressed first 20: ", compressed, 20);

    /* Encrypt */
    unsigned char key = key_gen();
    printf("key: %hhu\n", key);
    XOR_cipher_encrypt(compressed, compressed_size, key);

    print_pixels("Encrypted first 20: ", compressed, 20);
}