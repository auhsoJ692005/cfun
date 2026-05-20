/*====================
* XOR_cipher_crypt (Josh)
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

/*====================
* rc4_crypt (Josh)
* ====================
* Encrypts or decrypts data using RC4 stream cipher (XOR with keystream)
* 
* data: pointer to input data buffer (will be modified in place)
* size: number of bytes in buffer
* key: pointer to the encryption key bytes
* key_len: number of bytes in the key (1 to 256)
*
* returns void
*/
void rc4_crypt(unsigned char *data, int size, const unsigned char *key, int key_len);

/*====================
* key_gen (Josh)
* ====================
* Generates a random 8-bit key for XOR cipher
* 
* no input parameters
*
* returns unsigned char – a random number between 0 and 255
*/
unsigned char key_gen();