#include <stdio.h>

typedef struct Game {
    // Actual string
    char *word_to_guess;
    unsigned long word_to_guess_len;

    char *letters_guessed_wrong;
    unsigned short letters_guessed_wrong_len;

    // Share the same len as word_to_guess
    char *letters_guessed_correct;

    unsigned short life_count;
    unsigned short turn_count;
} game_t;
