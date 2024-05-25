#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#define GAME_SIZE 3

typedef struct Game {
    char board[GAME_SIZE][GAME_SIZE];
    char turn;
} Game;

Game game_init();

bool game_position_is_empty(Game* game, int row, int column);

void game_insert(Game* game, int row, int column);

char game_verify_win(Game* game);

#endif
