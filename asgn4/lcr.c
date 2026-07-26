/*
* File:     lcr.c
*
* Purpose:  This is the main file of the LCR program.
*
*           The main() program already has been written, you you can edit
*           it to temporarily run unit tests.
*/

#include "game.h"
#include "lcr_strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    int num_players;
    unsigned seed;

    if (argc != 3) {
        printf(PROGRAM_USAGE_s, argv[0]);
        return 1;
    }

    int scanf_result = sscanf(argv[1], "%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {
        printf(ERROR_INVALID_PLAYERS);
        num_players = 3;
    }

    scanf_result = sscanf(argv[2], "%u", &seed);

    if (scanf_result < 1 || seed > 999999) {
        printf(ERROR_INVALID_SEED);
        seed = 4823;
    }

    play_game(seed, num_players);

    return 0;
}
