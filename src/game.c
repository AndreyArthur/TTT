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

bool game_position_is_empty(Game* game, int row, int column) {
    if (game->board[row][column] == ' ') {
        return true;
    }
    return false;
}

void game_insert(Game* game, int row, int column) {
    game->board[row][column] = game->turn;
    if (game->turn == 'X') {
        game->turn = 'O';
    } else {
        game->turn = 'X';
    }
}

static char game_verify_row(Game* game) {
    for (int index = 0; index < GAME_SIZE; index++) {
        if (game->board[index][0] != ' ' &&
            game->board[index][0] == game->board[index][1] &&
            game->board[index][1] == game->board[index][2]) {
            return game->board[index][0];
        }
    }
    return ' ';
}

static char game_verify_column(Game* game) {
    int column = 0;
    while (column < GAME_SIZE) {
        if ((game->board[0][column] == 'O') &&
            (game->board[1][column] == 'O') &&
            (game->board[2][column] == 'O')) {
            return 'O';
        } else if (
            (game->board[0][column] == 'X') &&
            (game->board[1][column] == 'X') &&
            (game->board[2][column] == 'X')) {
            return 'X';
        }
        column++;
    }
    return ' ';
}

static char game_verify_diagonal(Game* game) {
    if (game->board[0][0] != ' ' && game->board[0][0] == game->board[1][1] &&
        game->board[1][1] == game->board[2][2]) {
        return game->board[0][0];
    }

    if (game->board[0][2] != ' ' && game->board[0][2] == game->board[1][1] &&
        game->board[1][1] == game->board[2][0]) {
        return game->board[0][2];
    }

    return ' ';
}

static bool game_is_full(Game* game) {
    bool is_full = true;
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int column = 0; column < GAME_SIZE; column++) {
            if (game->board[row][column] == ' ') {
                is_full = false;
            }
        }
    }
    return is_full;
}

char game_verify_win(Game* game) {
    char winner = game_verify_row(game);
    if (winner != ' ') {
        return winner;
    }

    winner = game_verify_column(game);
    if (winner != ' ') {
        return winner;
    }

    winner = game_verify_diagonal(game);
    if (winner != ' ') {
        return winner;
    }

    if (game_is_full(game)) {
        return '=';
    }

    return ' ';
}
