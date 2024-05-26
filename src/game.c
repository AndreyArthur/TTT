#include "include/game.h"

/*
 * Função que inicializa a estrutura Game
 *
 * limpa todas as posições, marcando-as como ' ' (espaço)
 * coloca a vez como 'X'
 */
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

/*
 * Detecta se a posição está vazia (se é um espaço).
 *
 * game: um ponteiro para a estrutura do jogo
 * row: linha a procurar
 * column: coluna a procurar
 */
bool game_position_is_empty(Game* game, int row, int column) {
    if (game->board[row][column] == ' ') {
        return true;
    }
    return false;
}

/*
 * Insere diretamente na posição dada e muda a vez do jogo.
 *
 * game: ponteiro para a estrutura do jogo
 * row: linha a inserir
 * column: coluna a inserir
 */
void game_insert(Game* game, int row, int column) {
    game->board[row][column] = game->turn;
    if (game->turn == 'X') {
        game->turn = 'O';
    } else {
        game->turn = 'X';
    }
}

/*
 * Verifica se alguma linha do jogo está completa.
 * Se estiver completa com 'X' retorna 'X', se estiver completa com 'O',
 * retorna 'O'.
 * Caso contrário, retorna ' '.
 *
 * game: ponteiro para a estrutura do jogo
 */
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

/*
 * Verifica se alguma coluna do jogo está completa.
 * Se estiver completa com 'X' retorna 'X', se estiver completa com 'O',
 * retorna 'O'.
 * Caso contrário, retorna ' '.
 *
 * game: ponteiro para a estrutura do jogo
 */
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

/*
 * Verifica se alguma diagonal do jogo está completa.
 * Se estiver completa com 'X' retorna 'X', se estiver completa com 'O',
 * retorna 'O'.
 * Caso contrário, retorna ' '.
 *
 * game: ponteiro para a estrutura do jogo
 */
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

/*
 * Verifica se o tabuleiro (game->board) está completo (sem espaços).
 * Se estiver completo, retorna true, senão retorna false.
 *
 * game: ponteiro para a estrutura do jogo
 */
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

/*
 * Verifica se algum usuário ganhou ou se deu velha (empate).
 * Usa cada uma das funções acima para modularizar.
 *
 * Se 'X' for o vencedor, retorna 'X'.
 * Se 'O' for o vencedor, retorna 'O'.
 * Se deu empate, retorna '='.
 *
 * Se nenhuma dessas coisas aconteceu, retorna ' ' (espaço);
 */
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
