#include "include/interface.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
#ifdef _WIN32
    printf("Adicionando suporte a acentos...\n");
    system("chcp 65001");
    printf("\n");
#endif

    Interface interface = interface_init();

    interface_get_names(&interface);

    interface_display_game(&interface);

    while (1) {
        interface_make_move(&interface);

        interface_display_game(&interface);

        if (interface_game_is_over(&interface)) {
            bool new_game = interface_ask_new_game(&interface);

            if (new_game == false) {
                return 0;
            }
        }
    }

    return 0;
}
