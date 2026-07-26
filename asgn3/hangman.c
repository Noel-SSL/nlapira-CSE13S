#include "hangman_strings.h"

/*
* Purpose:          Determine whether a char is lower-case.
*
*                   For this assignment only,
*
*                           YOU MAY NOT USE islower()
*
*                   I want you to get experience in comparing character
*                   values.  So you will write code that checks whether c
*                   is between 'a' and 'z'.
*
* Parameter:        c   - A character.  Literally any byte value 0 to 255.
*
* Return value:     1 (true) if c is a lower-case letter (between 'a' and 'z').
*                   0 (false) otherwise.
*/
bool is_lowercase_letter(char c) {
    if(c >= 'a' && c <= 'z') {
        return 1;
    }
    return 0; 
}
 // This test pass

/*
* Purpose:          Determine whether a string contains a character.
*
*                   To determine whether the string contains the given
*                   character, you may use strlen() and a "for" loop, or
*                   you may use strchr().  Use the commands "man 3 strlen"
*                   and "man 3 strchr" to read more about these functions.
*                   Look near the end of the man page for "RETURN VALUE"
*                   for the best summary.
*
* Parameters:       string  - the string to search within
*                   ch      - the character to search for
*
* Return value:     1 if the string contains the character.
*                   0 otherwise
*/
bool string_contains_character(const char *string, char ch) {
    if (strchr(string, ch)){ // strchr checks if the ch is within the string 
        return 1;
    }

    return 0; 
}
//This test pass

/*
* Purpose:          Determine whether the length and contents of a secret
*                   are valid.  As described in the assignment PDF, valid
*                   secrets have a length that is no more than MAX_LENGTH
*                   (which already is defined for you in
*                   hangman_strings.h), and they must consist of only
*                   lower-case letters and the three punctuation characters
*                   '-', '\'', and ' '.
*
*                   Use strlen() to confirm that the length of the secret
*                   does not exceed MAX_LENGTH.  If it does, use printf()
*                   and MSG_LONG_SECRET_d to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Using a "for" loop, verify that all of the secret's
*                   characters are valid.  That is, that they are
*                   lower-case letters and the three kinds of punctuation.
*                   If any of the characters is illegal, then use printf()
*                   and MSG_INVALID_CHAR_c to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Hint:  You can test that a character of the string is
*                   punctuation using individual "==" comparisions, or you
*                   can use your function string_contains_character() and
*                   the string "punctuation" (which is defined for you in
*                   hangman_strings.h).
*
* Parameter:        secret  - A string that represents the secret to test.
*
* Return Value:     If the secret is valid, then return true.
*                   Otherwise return false.
*/
bool is_valid_secret(const char *secret) {
    size_t length = strlen(secret); // defines the length of the string
    if (length > MAX_LENGTH)  { // checks max-length from hangman_strings.h
        printf(MSG_LONG_SECRET_d, MAX_LENGTH); 
        return false;
    }
    for (int i = 0; i < length; i++) {
        char c = secret[i];
        
        bool is_letter = is_lowercase_letter(c);
        bool is_punct = string_contains_character(punctuation,c);

        if (!is_letter && !is_punct){
            printf(MSG_INVALID_CHAR_c, c);
            return false;
        }

        
    
    }
    return true; 
}

/*
* Purpose:          (1) Prompt for a character.
*                   (2) Read characters from stdin until one is read
*                       that is not '\n'.
*                   (3) If EOF is received, then call exit(1).
*
* Parameter:        None.
*
* Return value:     A character.
*/
char prompt_for_and_read_character(void) {
    printf(MSG_PROMPT); //Prompts the user
    int ch; // declare


    do {
       ch = getchar();
        
       if (ch == EOF){
        exit(1);
    }
    } while (ch == '\n'); 

    return (char) ch; 
}

/*
* See Section 2 of the assignment PDF.
*/
void run_hangman(const char *secret) {
    //int i;
    int num_wrong_guesses = 0;
    char eliminated[27] = {0};
    int elim_count = 0;


    char revealed[MAX_LENGTH];
    int length = strlen(secret);
    
    

    

    for (int i = 0; i < length; i++) {
        char c = secret[i];

        if (c == ' ' || c == '-' || c == '\'') {
            revealed[i] = c;
        }else {
            revealed[i] = '_';
        }

        
    }

    revealed[length] = '\0';



    while (1) {
        // this prints the board of the hangman
        printf("%s\n", arts[num_wrong_guesses]);
        printf("    Phrase: %s\n", revealed);
        printf("Eliminated: %s\n", eliminated);
        printf("\n");


        char guess;
        
        while (1) { // this checks for same character
            guess = prompt_for_and_read_character();

            if (!is_lowercase_letter(guess)) {
            continue;
            }

            if (string_contains_character(eliminated,guess) || string_contains_character(revealed, guess)) {
            continue;
            }
            break;
        }

        if (string_contains_character(secret,guess)) {
            for (int i = 0; i < length; i++) {
                if (secret[i] == guess) {
                    revealed[i] = guess;
                }
            }
        }  else {
            eliminated[elim_count++] = guess;
            eliminated[elim_count] = '\0';
            
            for (int i = 0; i < elim_count - 1; i++) {
                for (int j = i + 1; j < elim_count; j++) {
                    if (eliminated[j] < eliminated[i]){
                        char tmp = eliminated[i];
                        eliminated[i] = eliminated[j];
                        eliminated[j]  = tmp;
                    }
                }
            }
            num_wrong_guesses++;
        }

        int won = 1;
        for (int i = 0; i < length; i++) {
            if (revealed[i] == '_') {
                won = 0;
                break; 
            }
        }
        if (won) {
            printf("%s\n", arts[num_wrong_guesses]);
            printf("    Phrase: %s\n", revealed);
            printf("Eliminated: %s\n", eliminated);
            printf("\n");
            printf(MSG_WIN_s, secret);
            return;
        }

        if (num_wrong_guesses >= 6){
            printf("%s\n", arts[num_wrong_guesses]);
            printf("    Phrase: %s\n", revealed);
            printf("Eliminated: %s\n", eliminated);
            printf("\n");
            printf(MSG_LOSE_s, secret);
            return;
        }
    }
}
        















/*
* Purpose:          Run the hangman game.
*
*                     1. Check the value of argc to confirm that the user
*                        runs hangman with a "secret" on the command line.
*                        If the user puts the wrong number of arguments on
*                        the command line, then using printf() and
*                        MSG_WRONG_NUM_ARGS to report an error, and then
*                        "return 1".
*                     2. Call is_valid_secret().  If the function
*                        returns false, then "return 1;".
*                     3. Call run_hangman(secret).
*                     4. Return 0.
*
* Parameters:       argc    - The number of command-line arguments from main().
*                   argv    - An array of strings from main().
*
* Return value:     0 if no error.  1 otherwise.
*/
int main(int argc, char **argv) {
    if (argc != 2) { // Telling there should be two counts ./hangman "yay" == 2
        printf(MSG_WRONG_NUM_ARGS);
        return 1;
    }
    const char *secret = argv[1];

    if(!is_valid_secret(secret)){
        return 1;
    }

    run_hangman(secret);
    
    
    
    
    
    
    
    //assert(is_valid_secret("abcdefg-hijklmnop qrstuv'wxyz"));
    //assert(!is_valid_secret("A"));
    //assert(!is_valid_secret("3"));
    return 0; // Replace this line with your source code.
}
