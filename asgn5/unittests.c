#include "nibbler.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_TESTS 12

/*
* Purpose:          Create a file from a string.
*
* Parameters:       filename    -- the name of the file to create
*                   data        -- pointer to the string
*
* Returns:          nothing
*/
void create_file_from_string(const char *filename, const char *data) {
    FILE *f = fopen(filename, "w");
    assert(f);
    fprintf(f, "%s", data);
    fclose(f);
}

/*
* Purpose:          Read a file and confirm that it contains exactly a
*                   given character sequence.
*
* Parameters:       filename    -- file to read
*                   p           -- pointer to the string data
*
* Returns:          nothing
*/
void verify_file_from_string(const char *filename, const char *p) {
    /*
    * Open the file.
    */
    FILE *f = fopen(filename, "r");
    assert(f);

    /*
    * Check each char of the string.
    */
    for (;;) {
        int ch = fgetc(f);

        if (ch == EOF) {
            /*
            * End of file:  verify that the string ends, too.
            */
            assert(*p == '\0');
            break;
        }

        /*
        * Same?  good.
        */
        assert(ch == *p);

        /*
        * Next char of the string.
        */
        ++p;
    }

    fclose(f);
}

void test_nib_open_for_read(void) {
    /*
    * Create a temporary file.
    */
    const char *filename = "_test_nib_open.txt";
    create_file_from_string(filename, "'Twas brillig");

    NIB *nib = nib_open(filename, "r");

    assert(nib != NULL);
    assert(nib->underlying_f != NULL);
    assert(nib->opened_for_read);
    assert(nib->num_nibbles == 0);

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_open_no_file(void) {
    /*
    * Be certain that there is no file named _nonexistent.txt .
    */
    const char *filename = "_nonexistent.txt";
    unlink(filename);

    NIB *nib = nib_open(filename, "r");

    assert(!nib);

    printf("PASS\n");
}

void test_nib_open_for_write(void) {
    /*
    * Create a temporary file.
    */
    const char *filename = "_test_nib_open.txt";
    NIB *nib = nib_open(filename, "w");

    assert(nib->underlying_f != NULL);
    assert(!nib->opened_for_read);
    assert(nib->num_nibbles == 0);

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_close_after_write_0(void) {
    /*
    * Create a temporary file.
    */
    const char *filename = "_test_nib_close.txt";
    FILE *f = fopen(filename, "w");

    /*
    * Initialize a NIB data structure with zero pending nibbles.
    */
    NIB *nib = calloc(1, sizeof(NIB));
    nib->underlying_f = f;
    nib->opened_for_read = 0;
    nib->num_nibbles = 0;
    nib->stored_nibble = 0x7;

    /*
    * Close the file.
    */
    nib_close(nib);

    /*
    * Check that the file is empty.
    */
    verify_file_from_string(filename, "");

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_close_after_write_1(void) {
    /*
    * Create a temporary file.
    */
    const char *filename = "_test_nib_close.txt";
    FILE *f = fopen(filename, "w");

    /*
    * Initialize a NIB data structure with one pending nibble.
    */
    NIB *nib = calloc(1, sizeof(NIB));
    nib->underlying_f = f;
    nib->opened_for_read = 0;
    nib->num_nibbles = 1;
    nib->stored_nibble = 0x6;    // expect byte 0x6f to get written

    /*
    * Close the file.
    */
    nib_close(nib);

    /*
    * Verify that 0x6f got written.
    */
    verify_file_from_string(filename, "\x6f");

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_get_nibble_1(void) {
    /*
    * Initialize a NIB data structure with one pending nibble.
    */
    NIB nib;
    nib.underlying_f = stdin;
    nib.opened_for_read = 1;
    nib.num_nibbles = 1;
    nib.stored_nibble = 0xa;

    /*
    * Get the nibble.
    */
    assert(nib_get_nibble(&nib) == 0xa);

    /*
    * Verify that there are no more pending nibbles.
    */
    assert(nib.num_nibbles == 0);

    printf("PASS\n");
}

void test_nib_get_nibble_2(void) {
    /*
    * Create a temporary file with the two nibbles 1 and 2.
    */
    const char *filename = "_test_nib_get_nibble.txt";
    create_file_from_string(filename, "\x12");

    /*
    * Open the temporary file.
    */
    NIB *nib = nib_open(filename, "r");

    /*
    * Verify that we get 1, 2, and EOF.
    */
    assert(nib_get_nibble(nib) == 1);
    assert(nib_get_nibble(nib) == 2);
    assert(nib_get_nibble(nib) == EOF);

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_get_nibble_4(void) {
    /*
    * Create a temporary file with the four nibbles 1, 2, 3, and 4.
    */
    const char *filename = "_test_nib_get_nibble.txt";
    create_file_from_string(filename, "\x12\x34");

    /*
    * Open the temporary file.
    */
    NIB *nib = nib_open(filename, "r");

    /*
    * Verify that we get 1, 2, 3, 4, and EOF.
    */
    assert(nib_get_nibble(nib) == 1);
    assert(nib_get_nibble(nib) == 2);
    assert(nib_get_nibble(nib) == 3);
    assert(nib_get_nibble(nib) == 4);
    assert(nib_get_nibble(nib) == EOF);

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_put_nibble_1(void) {
    /*
    * Create a temporary file.
    */
    const char *filename = "_test_nib_put_nibble.txt";
    FILE *f = fopen(filename, "w");

    /*
    * Initialize a NIB data structrue with one pending nibble:
    * the most-significant nibble of the character 'U'.
    */
    NIB nib;
    nib.underlying_f = f;
    nib.opened_for_read = 0;
    nib.num_nibbles = 1;
    nib.stored_nibble = ('U' >> 4) & 0xf;

    /*
    * Put the least-significant nibble of the character 'U'.
    */
    nib_put_nibble('U' & 0xf, &nib);

    /*
    * Verify that the NIB data structure has been updated.
    */
    assert(nib.num_nibbles == 0);

    /*
    * Close the temporary file.
    */
    fclose(f);

    /*
    * Check that the temporary file contains 'U'.
    */
    verify_file_from_string(filename, "U");

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_put_nibble_2(void) {
    /*
    * Create a temporary file with the nibble sequence 1, 2.
    */
    const char *filename = "_test_nib_put_nibble.txt";
    NIB *nib = nib_open(filename, "w");
    nib_put_nibble(0x1, nib);
    nib_put_nibble(0x2, nib);
    nib_close(nib);

    /*
    * Verify that the temporary file contains 0x12.
    */
    verify_file_from_string(filename, "\x12");

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_put_nibble_4(void) {
    /*
    * Create a temporary file with the nibble sequence 1, 2.
    */
    const char *filename = "_test_nib_put_nibble.txt";
    NIB *nib = nib_open(filename, "w");
    nib_put_nibble(0x1, nib);
    nib_put_nibble(0x2, nib);
    nib_put_nibble(0x3, nib);
    nib_put_nibble(0x4, nib);
    nib_close(nib);

    /*
    * Verify that the temporary file contains 0x12 and 0x34.
    */
    verify_file_from_string(filename, "\x12\x34");

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

void test_nib_put_nibble_3(void) {
    /*
    * Create a temporary file with the nibble sequence 1, 2, 3.
    */
    const char *filename = "_test_nib_put_nibble.txt";
    NIB *nib = nib_open(filename, "w");
    nib_put_nibble(0x1, nib);
    nib_put_nibble(0x2, nib);
    nib_put_nibble(0x3, nib);
    nib_close(nib);

    /* 
    * Verify that the file contains 0x12 and 0x3f.
    */
    verify_file_from_string(filename, "\x12\x3f");

    /*
    * Delete the temporary file.
    */
    unlink(filename);

    printf("PASS\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./unittests NUMBER_OF_TESTS (1 to %d)\n", NUM_TESTS);
        exit(0);
    }

    int m = atoi(argv[1]);

    if (m > NUM_TESTS) {
        printf("Usage: ./unittests NUMBER_OF_TESTS (1 to %d)\n", NUM_TESTS);
        exit(0);
    }

    printf("Running %d of %d tests\n", m, NUM_TESTS);

    for (int i = 1; i <= m; ++i) {
        printf("\ntest %d:\n", i);

        switch (i) {
        case 1: test_nib_open_for_read(); break;
        case 2: test_nib_open_no_file(); break;
        case 3: test_nib_open_for_write(); break;
        case 4: test_nib_close_after_write_0(); break;
        case 5: test_nib_close_after_write_1(); break;
        case 6: test_nib_get_nibble_1(); break;
        case 7: test_nib_get_nibble_2(); break;
        case 8: test_nib_get_nibble_4(); break;
        case 9: test_nib_put_nibble_1(); break;
        case 10: test_nib_put_nibble_2(); break;
        case 11: test_nib_put_nibble_4(); break;
        case 12:
            test_nib_put_nibble_3();
            break;
            // Rememeber to update NUM_TESTS
        }
    }

    printf("\n");
    printf("Have we proven that your Nibbler ADT has no bugs?\n");
    printf("No.  We cannot prove that a program works.\n");
    printf("We can only show when it doesn't work.\n");

    return 0;
}
