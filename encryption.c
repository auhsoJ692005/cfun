#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void XOR_cipher(unsigned char* data, int size, unsigned char key)
{
    int i;
    for (i = 0; i < size; i++)
    {
        data[i] ^= key;   /* XOR with the single-byte key */
    }
}

static void print_decimal(const unsigned char *data, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%u ", data[i]);   /* %u treats unsigned char as small integer */
    }
    printf("\n");
}

static unsigned char key_gen()
{
    srand(time(NULL));
    return (rand() % (256));
}

int main()
{
    unsigned char message[] = {0, 100, 200, 150, 25, 33};
    int size = sizeof(message) / sizeof(message[0]);
    unsigned char key = key_gen();

    printf("Original (decimal): ");
    print_decimal(message, size);

    printf("Key: %hhu\n", key);

    XOR_cipher(message, size, key);
    printf("Encrypted (decimal): ");
    print_decimal(message, size);

    XOR_cipher(message, size, key);
    printf("Decrypted (decimal): ");
    print_decimal(message, size);

    return 0;
}