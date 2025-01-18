#include "game.h"
#include <string.h>

int main(){
    game_t *game = create_new_game(3);
    print_game_state(game);

    while (strcmp(game->letters_guessed_correct, game->word_to_guess) != 0 && game->life_count > 0){
        play_turn(game);
        print_game_state(game);
    }

    (game->life_count < 1) ? printf("GAME OVER!\n") : printf("Well done! Guessed in %i turn\n", game->turn_count);
    destroy_game(game);
}
