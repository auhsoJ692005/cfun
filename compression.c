int compress(unsigned char* input, int input_size, unsigned char* output, int output_size){
    int out_index = 0;
    int i = 0;
    while (i < input_size && out_index < output_size - 1) {
        unsigned char current_value = input[i];
        int run_length = 1;
        while (i + run_length < input_size && input[i + run_length] == current_value && run_length < 255) {
            run_length++;
        }
        output[out_index++] = current_value;
        output[out_index++] = run_length;
        i += run_length;
    }
    return out_index;
}

int decompress(unsigned char* input, int input_size, unsigned char* output, int output_size) {
    int out_index = 0;
    int i = 0;
    while (i < input_size && out_index < output_size) {
        unsigned char value = input[i++];
        int run_length = input[i++];
        for (int j = 0; j < run_length; j++) {
            output[out_index++] = value;
        }
    }
    return out_index;
}

int main()
{
    printf("Compression and Decompression Test\n");
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
}