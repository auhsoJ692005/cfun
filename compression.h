/*====================
* compress
* ====================
* Compresses grayscale image data using RLE (Run Length Encoding)
* 
* input: original pixel array
* input_size: size of input array
* output: buffer for compressed data
*
* returns number of elements written to output buffer
*/
int compress(unsigned char* input, int input_size, unsigned char* output);

/*====================
* decompress
* ====================
* Decompresses RLE data back into pixel values
* 
* input: compressed data array
* input_size: number of elements in compressed buffer
* output: buffer for decompressed data
*
* returns number of pixels written to output buffer
*/
int decompress(unsigned char* input, int input_size, unsigned char* output);