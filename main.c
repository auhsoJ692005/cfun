#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int w, h;
    char filename[] = "dataset/0.pgm";

    unsigned char* img = read_pgm(filename, &w, &h);

    /* Check first 0 pixels */
    printf("First 20 pixels of PGM: ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", img[i]);
    }
    printf("\n");
}