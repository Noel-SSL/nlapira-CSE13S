/*
* File:     nibbler.c
*
* Purpose:  Normally files are read and written one byte at a time, but
*           these routines let us read and write files one nibble (4 bits)
*           at a time.
*/

#include "nibbler.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Purpose: Being able to access the file and put stuff in it 
*            or what's in the file
*
*    Parameters: Filename - The file that's being access 
*                
*                Mode - Pointer and the mode that sets the file like 'r' or 'w'
*
*    Returns: Nibs (The pointer of the NIB structure)
*
*/

NIB *nib_open(const char *filename, const char *mode) {
    FILE* f = fopen(filename, mode);
    if (!f) {
        return NULL;
    }

    NIB *nib = calloc(1, sizeof(NIB));
    if (nib == NULL){
        fclose(f);
        return NULL;
    }
    

    // struct accesor operator (->)
    nib->underlying_f = f;
    nib->opened_for_read = (mode[0] == 'r');
    

    nib-> num_nibbles = 0;
    nib-> stored_nibble = 0;

    return nib;

}

/*  Purpose: This functions reads out a nib(character) at time and stores the least significant nibble (0-15)
            and returns the most significant nibble
            This function is considered a 'r' as it reads out every single character until EOF 
*
*    Parameters: nib- It's basically a pointer of the NIB structure as it opens for 'r'
*
*    Returns: high nibble of the byte or if it's EOF
*/


int nib_get_nibble(NIB *nib) {
    if (nib -> num_nibbles > 0) {
        nib ->num_nibbles = 0;
        return nib -> stored_nibble;
    } else{
        int byte = fgetc(nib->underlying_f);
        if (byte == EOF){
            return EOF;
        }
        
        nib -> stored_nibble = byte & 0b00001111;
        nib -> num_nibbles = 1;
        return (byte >> 4) & 0b00001111; // Why >>?
        // We're returning the high nibble and the PDF says to moves >> by 4
        // To isolate the high nibble
    }
}

/*  Purpose: Being able to write out a nibble and another nibble and it merges into one byte and it's stored into a file
*
*    Parameters: nibble - represents the lower nibble
                
                nib - represents a pointer from the NIB structure as it opens for 'w'

*    Returns: Nothing and only writes the data and storing
*/

void nib_put_nibble(int nibble, NIB *nib) {
    nibble = nibble & 0b00001111;

    if (nib -> num_nibbles > 0){
        unsigned char byte = 
            ((nib -> stored_nibble & 0b00001111) << 4) | nibble;
        fputc(byte, nib -> underlying_f);
        nib -> num_nibbles = 0;
    }else{
        nib -> stored_nibble = nibble;
        nib -> num_nibbles = 1;
    }

}
/*  Purpose: This closes the file as it finishes. However, if bytes is still stored then
            a final byte is created and after handling the bytes, the file will close and free the NIB
            structure
*
*    Parameters: nib- It's basically a pointer of the NIB structure 
*
*    Returns: Nothing
*/

void nib_close(NIB *nib) {
    if (!nib-> opened_for_read && nib-> num_nibbles > 0) {
        unsigned char byte = 
            ((nib-> stored_nibble & 0b00001111)<<4) | 0b1111;
        fputc(byte, nib -> underlying_f);
    }

    fclose(nib -> underlying_f);
    
    free(nib);
    // returns and dellcoates the given memory
        
}

