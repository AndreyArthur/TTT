#ifndef GAME_H
#define GAME_H

#define GAME_SIZE 3

typedef struct Game {
    char board[GAME_SIZE][GAME_SIZE];
    char turn;
} Game;

Game game_init();

#endif
