/*
* Program:      compress
*
* Purpose:      Compress a file.
*
* Usage:        compress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  compress INFILE -o OUTFILE\n");
    exit(0);
}

/*  Purpose: This function allows to loop and compare if the ch is 
            in the table and if it isn't then goes to default
    
    Parameters: fin - Basically our input file
                
                nib - The pointer of NIB strucuter, but it's consider our output file
    
    Return: Nothing
*/

void compress(FILE *fin, NIB *nib) {
    int ch;
    while((ch = fgetc(fin))!= EOF) { // This line goes into a loop to check each character
        switch (ch) {
            case ' ': nib_put_nibble(0,nib); break;
            case 'e': nib_put_nibble(1,nib); break;
            case 't': nib_put_nibble(2,nib); break;
            case 'n': nib_put_nibble(3,nib); break;
            case 'r': nib_put_nibble(4,nib); break;
            case 'o': nib_put_nibble(5,nib); break;
            case 'a': nib_put_nibble(6,nib); break;
            case 'i': nib_put_nibble(7,nib); break;
            case 's': nib_put_nibble(8,nib); break;
            case 'd': nib_put_nibble(9,nib); break;
            case 'l': nib_put_nibble(10,nib); break;
            case 'h': nib_put_nibble(11,nib); break;
            case 'c': nib_put_nibble(12,nib); break;
            case 'f': nib_put_nibble(13,nib); break;
            case 'p': nib_put_nibble(14,nib); break;
            //Checks if ch is within the table
        default:
            //If not set it as default and break
            nib_put_nibble(15,nib);
            nib_put_nibble((ch >> 4) & 0xF, nib);
            nib_put_nibble(ch & 0xF, nib);
            break;
        }
    }


}

/* Purpose: This functions allows you to compress the file then allows 
            you to compare the orginal and compressed files. This functions also checks
            for errors before compressing 

    Parameters- argc - Our argumnent count in the command line 

                argv- The values on the command line 
    
    Returns: Nothing if succeeded unless it hits any errors
*/


int main(int argc, char **argv) {
    if (argc != 4) {
        print_usage();
    }
    // Remember to use strcmp because your comparing a string
    // if you did agrv != "-o", it will give an error (Which I did this the first time)
    if (strcmp(argv[2], "-o")!= 0) {
        print_usage();
    }
    // These two are pointers and stores in the argv listed 
    const char *input_file = argv[1]; 
    const char *output_file = argv[3];
    
    //This opens the input_file and calls if any erros
    FILE *fin = fopen(input_file, "r");
        if (fin == NULL) {
            fprintf(stderr,"Can't open file for output: %s\n", input_file);
            exit(1);
        }
    // Opens out_file and reports any errors
    NIB *nib = nib_open(output_file, "w");
        if (nib == NULL){
            fprintf(stderr, "Can't open file for input: %s\n", output_file );
            exit(1);
        }
    // Compresses the files then closes them
    compress(fin, nib);
    
    fclose(fin);
    nib_close(nib);
}
