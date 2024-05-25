#include "include/interface.h"
#include <stdio.h>

int main() {
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
