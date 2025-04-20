#include "game.h"
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_random_number(int min, int max) {
    // Seed the random number generator
    static int seeded = 0;
    // Make sure srand is only seed once, this is to ensure the func don't have the same result if called quickly
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    // Pick a random number between min and max
    return min + rand() % (max - min + 1);
}

game_t *create_new_game(unsigned short max_life) {
    // Define a new word
    const char *possible_words[5] = {"becode", "learning", "exosquelette", "mathias", "maxim"};
    const char *word_to_guess = possible_words[get_random_number(0, 4)];
    size_t word_to_guess_len = strlen(word_to_guess);

    // Store the new game in the heap
    game_t *new_game = malloc(sizeof(game_t));
    if (new_game == NULL) exit(1);

    // Store word to guess in the heap
    new_game->word_to_guess = malloc((sizeof(char) * word_to_guess_len) + 1);
    if (new_game->word_to_guess == NULL) exit(1);
    strcpy(new_game->word_to_guess, word_to_guess);

    // allocate memory in the heap for letters_guessed_correct
    new_game->letters_guessed_correct = malloc((sizeof(char) * word_to_guess_len) + 1);
    if (new_game->letters_guessed_correct == NULL) exit(1);

    // allocate memory in the heap for letters_guessed_wrong
    new_game->letters_guessed_wrong = malloc((sizeof(char) * max_life)+1);
    if (new_game->letters_guessed_wrong == NULL) exit(1);

    // Init game
    new_game->life_count = max_life;
    new_game->turn_count = 0;
    new_game->word_to_guess_len = word_to_guess_len;
    new_game->letters_guessed_wrong_len = 0;

    // Init dashes for correct guesses
    for (unsigned short i = 0; i < new_game->word_to_guess_len; i++){
        new_game->letters_guessed_correct[i] = '_';
    }

    return new_game;
}

char get_letter_from_user() {
    char input;
    printf("Guess a letter: ");
    while (1) {
        // Read a single character, ignoring leading whitespace
        if (scanf(" %c", &input) == 1) {
            // Check if it's a letter
            if (isalpha(input)) {
                break;
            } else {
                while (getchar() != '\n' && !feof(stdin));
                printf("Invalid input. Please enter a letter: ");
            }
        } else if(feof(stdin)) {
            clearerr(stdin);
            printf("\nInvalid input. Please enter a letter: ");
        } 
        else {
            // Clear the input buffer on invalid input
            while (getchar() != '\n' && !feof(stdin));
            printf("Invalid input. Please enter a letter: ");
        }
    }
    return input;
}

void play_turn(game_t *game){
    // Make sure a word to find is well defined
    if (game->word_to_guess == NULL || game->word_to_guess_len == 0) exit(1);

    char guess = get_letter_from_user();
    char is_correct_guess = 0;
    game->turn_count++;

    for (unsigned short i = 0; i < game->word_to_guess_len; i++){
        // Letters guessed before
        if (guess == game->letters_guessed_correct[i]){
            printf("'%c' already found!\n", guess);
            is_correct_guess = 1;
            return; // If the letter has been found before, the turn is increased, the user doesn't lose life
        }
    }

    for (unsigned short i = 0; i < game->word_to_guess_len; i++){
        if (guess == game->word_to_guess[i]){
            is_correct_guess = 1;
            game->letters_guessed_correct[i] = guess;
        }
    }

    if (is_correct_guess == 1) {
        printf("Good guess! '%c' is in the word!\n", guess);
    } else {
        printf("Wrong guess! '%c' is not in the word!\n", guess);
        game->life_count--;
        game->letters_guessed_wrong[game->letters_guessed_wrong_len] = guess;
        game->letters_guessed_wrong_len++;
    }
}

void print_letter_guessed(char *letter_guess_ptr, unsigned short letter_guess_len, unsigned short is_correct_guess_type){
    (is_correct_guess_type == 1) ? printf("Correct letters: ") : printf("Wrong letters: ");

    // print each guessed letter
    for(unsigned short i = 0; i < letter_guess_len; i++){
        printf("%c ", letter_guess_ptr[i]);
    }
    printf("\n");
}

void print_game_state(game_t *game){
    printf("--------- Turn %i ---------\n", game->turn_count);
    printf("Lifes remaining: %i\n", game->life_count);
    printf("Word to guess: %s\n", game->word_to_guess);
    print_letter_guessed(game->letters_guessed_wrong, game->letters_guessed_wrong_len, 0);
    print_letter_guessed(game->letters_guessed_correct, game->word_to_guess_len, 1);
    printf("\n");
}

void destroy_game(game_t *game){
    printf("Stoping game... ");
    free(game->letters_guessed_correct);
    game->letters_guessed_correct = NULL;

    free(game->letters_guessed_wrong);
    game->letters_guessed_wrong = NULL;

    free(game->word_to_guess);
    game->word_to_guess = NULL;

    free(game);
    game = NULL;

    printf("OK\n");
}
