#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void XOR_cipher_crypt(unsigned char* data, int size, unsigned char key)
{
    int i;
    for (i = 0; i < size; i++)
    {
        data[i] ^= key;   /* XOR with the single-byte key */
    }
}

void rc4_crypt(unsigned char *data, int size, const unsigned char *key, int key_len)
{
    unsigned char S[256];
    int i, j, k;
    unsigned char tmp;

    /* Initialise S‑box */
    for (k = 0; k < 256; k++)
        S[k] = (unsigned char)k;
    j = 0;
    for (k = 0; k < 256; k++) {
        j = (j + S[k] + key[k % key_len]) % 256;
        tmp = S[k]; S[k] = S[j]; S[j] = tmp;
    }
    i = 0; j = 0;

    /* Generate keystream and XOR */
    for (k = 0; k < size; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        tmp = S[i]; S[i] = S[j]; S[j] = tmp;
        data[k] ^= S[(S[i] + S[j]) % 256];
    }
}

unsigned char key_gen()
{
    srand(time(NULL));
    return (rand() % (256));
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

/*
int main()
{
    unsigned char message[] = {0, 100, 200, 150, 25, 33};
    int size = sizeof(message) / sizeof(message[0]);
    unsigned char key = key_gen();

    printf("Original: ");
    print_decimal(message, size);

    printf("Key: %hhu\n", key);

    XOR_cipher_encrypt(message, size, key);
    printf("Encrypted: ");
    print_decimal(message, size);

    XOR_cipher_decrypt(message, size);
    printf("Decrypted: ");
    print_decimal(message, size);

    return 0;
}
*/