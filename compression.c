#include <stddef.h>

int compress(unsigned char* input, int input_size, unsigned char* output, int output_size){
    int out_index = 0;
    int i = 0;

    if (input == NULL || output == NULL || input_size <= 0 || output_size <= 1) {
        return -1;
    }

    /* iterates through input data */
    while (i < input_size) {
        int remaining_out = output_size - out_index;
        if (remaining_out < 2) {
            break; /* not enough room for another value/run pair */
        }

        unsigned char current = input[i];
        int run_length = 1;
        int max_run = input_size - i;
        if (max_run > 255) {
            max_run = 255;
        }

        /* continues counting consecutive identical pixels */
        while (run_length < max_run && input[i + run_length] == current) {
            run_length++;
        }

        /* store run-length encoded data */
        output[out_index++] = current;
        output[out_index++] = (unsigned char)run_length;
        i += run_length;
    }

    return out_index;
}

int decompress(unsigned char* input, int input_size, unsigned char* output, int output_size) {
    int out_index = 0;
    int i = 0;
    int j;

    if (input == NULL || output == NULL || input_size <= 0 || output_size <= 0) {
        return -1;
    }

    /* iterates through compressed data */
    while (i + 1 < input_size && out_index < output_size) {
        unsigned char value = input[i++];
        int run_length = input[i++];

        if (run_length <= 0) {
            return -1; /* malformed compressed data */
        }
         

        if (run_length > output_size - out_index) {
            return -1; /* output buffer too small or compressed data malformed */
        }

        for (j = 0; j < run_length; j++) {
            output[out_index++] = value; /* expands run-length encoded data */
        }
    }

    if (i != input_size) {
        return -1; /* leftover bytes means malformed compressed data */
    }

    return out_index;
}
/*
int main()
{
  
    unsigned char data[] = {0, 0, 0, 255, 255, 128, 128, 128, 128};
    int data_size = sizeof(data) / sizeof(data[0]);
    unsigned char compressed[20];
    unsigned char decompressed[20];

    int compressed_size = compress(data, data_size, compressed, sizeof(compressed));
    int decompressed_size = decompress(compressed, compressed_size, decompressed, sizeof(decompressed));

    printf("Original size: %d\n", data_size);
    printf("Compressed size: %d\n", compressed_size);
    printf("Decompressed size: %d\n", decompressed_size);

    return 0;
} */
