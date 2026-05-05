int compress(unsigned char* input, int input_size, unsigned char* output)
{
    int i = 0;
    int out_index = 0;

    while (i < input_size)
    {
        unsigned char current = input[i];
        int count = 0;

        /* Keep counting */
        while (i + count < input_size && input[i + count] == current)
        {
            count++;
        }

        /* Store output */
        output[out_index++] = (unsigned char)count;
        output[out_index++] = current;

        i += count;
    }

    return out_index;
}
int decompress(unsigned char* input, int input_size, unsigned char* output)
{
    return 0;
}

/*
int main()
{
    return 0;
}
*/