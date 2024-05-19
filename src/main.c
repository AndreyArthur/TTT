#include "include/game.h"
#include <stdio.h>

int main() {
    Game game = game_init();

    for (int row = 0; row < GAME_SIZE; row++) {
        for (int column = 0; column < GAME_SIZE; column++) {
            if (column == GAME_SIZE - 1) {
                printf(" %c ", game.board[row][column]);
            } else {
                printf(" %c |", game.board[row][column]);
            }
        }

        if (row != GAME_SIZE - 1) {
            printf("-----------\n");
        }
    }
    return 0;
}
