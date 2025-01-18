#ifndef GAME_H
#define GAME_H

#include <stdio.h>

typedef struct Game {
    char *word_to_guess;
    unsigned long word_to_guess_len;

    char *letters_guessed_wrong;
    unsigned short letters_guessed_wrong_len;

    // Share the same len as word_to_guess
    char *letters_guessed_correct;

    unsigned short life_count;
    unsigned short turn_count;
} game_t;

game_t *create_new_game(unsigned short max_life);
void play_turn(game_t *game);
void print_game_state(game_t *game);
void destroy_game(game_t *game);

#endif // GAME_H
