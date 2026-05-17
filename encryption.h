/*====================
* XOR_cipher_encrypt (Josh)
* ====================
* Encrypts grayscale image using XOR cipher
* 
* data: pointer to input data buffer
* size: number of elements in buffer
* key: encryption key used for XOR operation
*
* returns void
*/
void XOR_cipher_crypt(unsigned char* data, int size, unsigned char key);

void rc4_crypt(unsigned char *data, int size, const unsigned char *key, int key_len);

unsigned char key_gen();