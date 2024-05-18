#include "include/game.h"

Game game_init() {
    Game game;
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int column = 0; column < GAME_SIZE; column++) {
            game.board[row][column] = ' ';
        }
    }
    game.turn = 'X';
    return game;
}
