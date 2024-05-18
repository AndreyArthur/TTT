#include "../src/include/game.h"
#include "deps/runner.h"
#include <stdbool.h>

bool test_game_init() {
    Game game = game_init();
    bool is_cleaned = true;

    for (int row = 0; row < GAME_SIZE; row++) {
        for (int column = 0; column < GAME_SIZE; column++) {
            if (game.board[row][column] != ' ') {
                is_cleaned = false;
            }
        }
    }

    return is_cleaned && game.turn == 'X';
}

int main() {
    Runner runner = runner_init("game");
    runner.test("should init with correct values", test_game_init);
    return 0;
}
