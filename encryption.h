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
void XOR_cipher_encrypt(unsigned char* data, int size, unsigned char key);

/*====================
* XOR_cipher_decrypt (Josh)
* ====================
* Decrypts grayscale image using XOR cipher
* 
* data: pointer to input data buffer
* size: number of elements in buffer
*
* returns void
*/
void XOR_cipher_decrypt(unsigned char* data, int size);

unsigned char key_gen();