/*
* File:     game.c
*
* Purpose:  Edit this file!  It is just a starting point.  You make your
*           assignment starting with this file.
*/

#include "game.h"
#include "randi.h"
#include "lcr_strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Here is an array of player names.  Given a player number i, use the
* player names like this:
*
*   player_name[i]
*
* The player number i can be anything from 0 to MAX_PLAYERS - 1.  (See
* lcr_strings.h for the definition of MAX_PLAYERS.)
*/
const char *player_name[] = {

    "Ada Lovelace",
    /*
    * 1815-1852.  English mathematician and writer who was the first
    * computer programmer.
    */

    "Margaret Hamilton",
    /*
    * 1936-.  Starting when she was 29 years old, lead the team that wrote
    * and tested the Apollo moon program's on-board flight software.
    * Invented the term "software engineering".
    */

    "Katherine Johnson",
    /*
    * 1918-2020.  Mathematician who hand-calculated trajectories for crewed
    * spaceflights.
    */

    "Joy Buolamwini",
    /*
    * ~1989-.  MIT computer scientist who works to challenge racial and
    * gender bias in AI-based decision software.
    */

    "Grace Hopper",
    /*
    * 1906-1992.  Mathematician and computer scientist who made the first
    * machine-independent computer language.
    */

    "Adele Goldberg",
    /*
    * 1945-.  Managed the team at Xerox that developed object-oriented
    * programming and graphical user interfaces.
    */

    "Annie Easley",
    /*
    * 1933-2011.  NASA computer scientist and mathematician who developed
    * algorithms that analyze various power technologies.
    */

    "Jeannette Wing",
    /*
    * 1956-.  Led many research projects as a university professor and as a
    * vice president at Microsoft Research.
    */

    "Mary Kenneth Keller",
    /*
    * 1913-1985.  First person to earn a Ph.D. in computer science in the
    * United States.
    */

    "Megan Smith",
    /*
    * 1964-.  Vice president at Google and 3rd Chief Technology Officer of
    * the United States.
    */

    "Radia Perlman",
    /*
    * 1958-.  Computer programmer and network engineer who invented many
    * network protocols include the Spanning Tree Protocol used by network
    * bridges.
    */
};

/*
* Faces of the die are numbered 0 through 5, and each face has a symbol.
* Below we create an array of six Symbols that is indexed by the face
* number.  Then you can convert the roll of a die (0-5) into a Symbol by
* accessing the array like this:
*
*    Symbol sym = symbol_of_roll[roll];
*/
const Symbol symbol_of_roll[6] = {
    DOT,
    DOT,
    DOT,
    LEFT,
    CENTER,
    RIGHT,
};

/*
* This array of ints stores the score of player i in score[i].
*/
int score[MAX_PLAYERS];

/*
* Purpose:      Return the letter of the Symbol according to this table:
*
*                    sym    return
*                   ------  ------
*                   DOT      '.'
*                   LEFT     'L'
*                   CENTER   'C'
*                   RIGHT    'R'
*
* Parameter:    sym - the Symbol DOT, LEFT, CENTER, or RIGHT.
*
* Returns:      a char that represents the letter of the Symbol.
*/
char letter_of_symbol(Symbol sym) {
    if (sym == DOT){
        return '.';
    } else if (sym == LEFT){
        return 'L';
    } else if (sym == CENTER) {
        return 'C';
    } else if (sym == RIGHT) {
        return 'R';
    }
    return '?'; // This helps us see if something go wrong within the program

}

/*
* Purpose:      Compute the minimum of two ints.
*
* Parameters:   ints a and b
*
* Returns:      a or b, whichever is smallest.
*/
int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
   
}

/*
* Purpose:      Return the next roll of a CSE 13S die.  That is, call randi(),
*               and then convert the result into a number between 0 and 5.
*
* Parameter:    none
*
* Returns:      An int from 0 to 5 representing a die roll
*/
int rand_roll(void) {
    return randi() % 6;
    // Use %, but doesn't work for negative numbers
}

/*
* Purpose:      Compute the number of the player that is to the LEFT of the
*               player with the number given in parameter "player".
*               (See Section 2 of the assignment PDF.)
*
* Parameters:   player      - player number from 0 to num_players - 1
*               num_players - the number of players in this game
*
* Returns:      int from 0 to num_players - 1
*/
int left_of(int player, int num_players) {
    // use %
    return (player + 1) % num_players;
}

/*
* Purpose:      Compute the number of the player that is to the RIGHT of the
*               player with the number given in parameter "player".
*               (See Section 2 of the assignment PDF.)
*
* Parameters:   player      - player number from 0 to num_players - 1
*               num_players - the number of players in this game
*
* Returns:      int from 0 to num_players - 1
*/
int right_of(int player, int num_players) {
    // use %
    return (player - 1 + num_players) % num_players;
    // why (player - 1 + num_players)? This helps us avoid negative numbers
}

/*
* Purpose:      Print all of the players' scores followed by the number of
*               chips in the pot.  The scores are in the array score[],
*               which is delcared near the top of this file.  You can
*               compute the number of chips in the pot (the game has a
*               total of 3 * num_players chips), or you can maintain the
*               pot's score in a new variable that you declare up where the
*               score[] array is.
*
*               Here is an example of the output:

Current scores:
    3 -- Ada Lovelace
    3 -- Margaret Hamilton
    3 -- Katherine Johnson
    0 -- pot

*               If you want, you can use two format strings in the file
*               lcr_strings.h:  CURRENT_SCORES and SCORE_ds.  Look in
*               lcr_strings.h to see what they represent.
*
* Parameter:    num_players - an int which is the number of players.
*
* Returns:      nothing
*/



void print_scores(int num_players) {
    printf(CURRENT_SCORES);
    int sum = 0;
    
    
    

    int total_chips = 3 * num_players;

    for (int i = 0; i < num_players; i++) {
        printf(SCORE_ds, score[i], player_name[i]);
        sum += score[i];
    
    }

    int pot = total_chips - sum;
    printf(SCORE_ds, pot, "pot");



}

/* Purpose:     The purpose of this function is that this will run the game 
                and using the functions we did above within our play_game.
                We will also use the messages from lcr_strings such as TURN_s
                to indicate who's turn is it and what they're rolling



    Parameters:  seed- The seed that's genereted using the pseudo-random generator  
                        and used in randi_seed()
                num_players - the numbers of players that are playing the game 
    
    
    Other variables used:
    
    player_name[i] - the player name and number 
    
    Symbol sym = symbol_of_roll[roll] - For rolling the dice 
    0-2 = DOT
    3 = LEFT
    4 = CENTER
    5 = RIGHT 

    
    

    Returns: Nothing
    We're finding out who won and not expecting a value in return



*/


void play_game(unsigned seed, int num_players) {

    randi_seed(seed); 

    // Checks if the num_players is valid

    if (num_players <= 2 || num_players > MAX_PLAYERS) {
        printf(ERROR_INVALID_PLAYERS);
        num_players = 3;
    }
    for (int i = 0 ; i < num_players; i++) {
        score[i] = 3;
        // Sets all players to have 3 chips
    }
    print_scores(num_players); //players starting with 3 chips and the pot of 0 

    int current_player = 0;

    while (1) {
        int with_chips = 0;
        for (int i = 0; i < num_players; i++) {
            if (score[i] > 0) { // meaning if a player has a chips
                with_chips++; 
            }
        }
        if (with_chips == 1) { // check every round if a player has chips or not
            break;
        }
        // we also need to implement if a player has no chips
        if (score[current_player] == 0) {
            printf(HAS_NO_CHIPS_s, player_name[current_player]);
            current_player = (current_player + 1) % num_players;
            continue; 
        }
        // We use min if a player has less then 3 chips
        // If they have two chips, they will roll only 2 dice
        int dice = min(score[current_player], 3);

        printf(TURN_s, player_name[current_player]);

        for (int d = 0; d < dice; d++) {
            // This is where we roll the dice and seeing what we get 
            int roll = rand_roll();
            Symbol sym = symbol_of_roll[roll];
            char c = letter_of_symbol(sym);
            printf(ROLLS_c, c);

            // Now we check if we give our chips to the left or right or
            // adding it to the pot
            if (sym == LEFT) {
                int left = left_of(current_player, num_players);
                score[current_player]--;
                score[left]++;
                printf(GIVES_A_CHIP_TO_s, player_name[left]);
            } else if (sym == RIGHT) {
                int right = right_of(current_player, num_players);
                score[current_player]--;
                score[right]++;
                printf(GIVES_A_CHIP_TO_s, player_name[right]);
            }else if (sym == CENTER) {
                score[current_player]--;
                printf(PUTS_A_CHIP);
            }
        }
        // Prints the current score and moves to the next player
        print_scores(num_players);

        current_player = (current_player + 1) % num_players;
    }

    // After the game loop is done, this will print the winner
    for (int i = 0; i < num_players; i++){
        if (score[i] > 0) {
             printf(ONE_PLAYER_HAS_CHIPS);
             printf(WON_s, player_name[i]);
              break;
        }
    }
}
