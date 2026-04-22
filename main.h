/*====================
* read_pgm (Elouise)
* ====================
* Reads a grayscale PGM to memory
* 
* filename: path to input file
* width: pointer to store image width
* height: pointer to store image height
*
* returns 1D array of pixel values
*/
unsigned char* read_pgm(const char* filename, int* width, int* height);

/*====================
* write_pgm (Elouise)
* ====================
* Writes a grayscale image to a PGM file
* 
* filename: path to output file
* data: pointer to 1D pixel array
* width: image width
* height: image height
*
* returns void
*/
void write_pgm(const char* filename, unsigned char* data, int* width, int* height);