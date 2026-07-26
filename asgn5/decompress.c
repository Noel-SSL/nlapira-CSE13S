/*
* Program:      decompress
*
* Purpose:      Decompress a file that was compressed with "compress".
*
* Usage:        decompress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  decompress INFILE -o OUTFILE\n");
    exit(0);
}

/*  Purpose: This function allows to loop and compare if nibble is within the table
            and turns them into character. If it's not within the table, it will convert 
            the nibbles into bytes and combining them 
    
    Parameters:    nib - The pointer of NIB structure, but it's consider our input file

                    fout- This is consider our output file 
    
    Return: Nothing
*/

void decompress(NIB *nib, FILE *fout) {
    int n; //Representing the numbers from the table
    while((n = nib_get_nibble(nib))!= EOF) {
       // Checks if it within the table and
       // turns the numbers into characters
        if (n >=0 &&  n <=14) { 
            char out;

            switch(n) {
                case 0: out = ' '; break;
                case 1: out = 'e'; break;
                case 2: out = 't'; break;
                case 3: out = 'n'; break;
                case 4: out = 'r'; break;
                case 5: out = 'o'; break;
                case 6: out = 'a'; break;
                case 7: out = 'i'; break;
                case 8: out = 's'; break;
                case 9: out = 'd'; break;
                case 10: out = 'l'; break;
                case 11: out = 'h'; break;
                case 12: out = 'c'; break;
                case 13: out = 'f'; break;
                case 14: out = 'p'; break;
            }
            //Let's put this character into the output file and skip the rest of the loop
            fputc(out,fout);
            continue;
        }

        // If it's not within the table, then convert the nibbles
        // into bytes and combine them 
        if (n == 15) {
            int high_nibble = nib_get_nibble(nib);
            
            if (high_nibble == EOF) 
                break;
            
             int low_nibble = nib_get_nibble(nib);
             if (low_nibble == EOF) 
                break;
             
             unsigned char byte = (high_nibble << 4) | low_nibble;
             fputc(byte,fout);
            
        } 
    }
}

/* Purpose: This functions allows you to decompress the file then allows 
            you to compare the orginal and decompressed files. This functions also checks
            for errors before decompressing 

    Parameters- argc - Our argumnent count in the command line 

                argv- The values on the command line 
    
    Returns: Nothing if succeeded unless it hits any errors
*/

int main(int argc, char **argv) {
    // This function is the same as compress, but it's in reveresed
    // You have NIB *nib as your input file this time and
    // File *fout as your output file
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
    NIB *nib = nib_open(input_file, "r");
        if (nib == NULL) {
            fprintf(stderr,"Can't open file for output: %s\n", input_file);
            exit(1);
        }
    // Opens out_file and reports any errors
    FILE *fout = fopen(output_file, "w");
        if (fout == NULL){
            fprintf(stderr, "Can't open file for input: %s\n", output_file );
            exit(1);
        }
    // Decompresses the files then closes them
    decompress(nib, fout);
    nib_close(nib);
    fclose(fout);
}
