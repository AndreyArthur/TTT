#include "include/interface.h"
#include "include/game.h"
#include <stdio.h>
#include <string.h>

Interface interface_init() {
    Game game = game_init();
    Interface interface;
    interface.game = game;
    return interface;
}

void interface_get_names(Interface* interface) {
    printf("Insira o nome do jogador X: ");
    scanf(" %32[^\n]", interface->x_player);
    printf("Insira o nome do jogador O: ");
    scanf(" %32[^\n]", interface->o_player);
}

void interface_display_game(Interface* interface) {
    printf("\n");

    int row, column;

    printf("   ");
    for (column = 0; column < GAME_SIZE; column++) {
        printf(" %d  ", column);
    }
    printf("\n");

    for (row = 0; row < GAME_SIZE; row++) {
        printf(" %d ", row);
        for (column = 0; column < GAME_SIZE; column++) {
            printf(" %c ", interface->game.board[row][column]);

            if (column != GAME_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");

        if (row != GAME_SIZE - 1) {
            printf("   -----------\n");
        }
    }

    printf("\n");
}

void interface_make_move(Interface* interface) {
    char turn = interface->game.turn;
    char name[32];
    if (turn == 'X') {
        strcpy(name, interface->x_player);
    } else {
        strcpy(name, interface->o_player);
    }

    bool occupied = true;

    while (occupied) {
        int row = -1, column = -1;

        while (row < 0 || row > 2) {
            printf(
                "%s (%c), escolha a linha que você quer jogar: ", name, turn);
            scanf("%d", &row);

            if (row < 0 || row > 2) {
                printf("Entrada inválida, precisa estar entre 0 e 2.\n");
            }
        }

        while (column < 0 || column > 2) {
            printf(
                "%s (%c), escolha a coluna que você quer jogar: ", name, turn);
            scanf("%d", &column);

            if (column < 0 || column > 2) {
                printf("Entrada inválida, precisa estar entre 0 e 2.\n");
            }
        }

        if (game_position_is_empty(&interface->game, row, column)) {
            occupied = false;
            game_insert(&interface->game, row, column);
        } else {
            printf("Entrada inválida, esta posição já está ocupada.\n");
        }
    }
}

bool interface_game_is_over(Interface* interface) {
    char win = game_verify_win(&interface->game);

    if (win == 'X') {
        printf("Parabéns %s, você venceu!\n", interface->x_player);
        return true;
    } else if (win == 'O') {
        printf("Parabéns %s, você venceu!\n", interface->o_player);
        return true;
    } else if (win == '=') {
        printf("Deu velha! Ninguém ganhou.\n");
        return true;
    }

    return false;
}

bool interface_ask_new_game(Interface* interface) {
    char choice = ' ';
    while (choice != 'S' && choice != 'N') {
        printf("Desejam jogar novamente (S/N)? ");
        scanf(" %c", &choice);

        if (choice == 's') {
            choice = 'S';
        } else if (choice == 'n') {
            choice = 'N';
        }
    }

    if (choice == 'N') {
        return false;
    }

    choice = ' ';
    while (choice != 'S' && choice != 'N') {
        printf("São os mesmos jogadores (S/N)? ");
        scanf(" %c", &choice);

        if (choice == 's') {
            choice = 'S';
        } else if (choice == 'n') {
            choice = 'N';
        }
    }

    if (choice == 'N') {
        interface_get_names(interface);
    }

    interface->game = game_init();

    return true;
}
