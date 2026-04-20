/*====================
* encrypt
* ====================
* Encrypts grayscale image using XOR cipher (Possibly)
* 
* data: pointer to input data buffer
* size: number of elements in buffer
* key: encryption key used for XOR operation
*
* returns void
*/
void encrypt(unsigned char* data, int size, unsigned char key);

/*====================
* decrypt
* ====================
* decrypts XOR encrypted data back to original (Possibly)
* 
* data: pointer to encrypted data buffer
* size: number of elements in buffer
* key: encryption key used for XOR operation
*
* returns void
*/
void decrypt(unsigned char* data, int size, unsigned char key);