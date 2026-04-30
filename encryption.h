/*====================
* encrypt (Josh)
* ====================
* Encrypts and decrypts grayscale image using XOR cipher (Possibly)
* 
* data: pointer to input data buffer
* size: number of elements in buffer
* key: encryption key used for XOR operation
*
* returns void
*/
void XOR_cipher(unsigned char* data, int size, unsigned char key);