#include "cheats.h"

// Note: Luma3DS LayeredFS writes code up to 0x005977B8. Do not use addresses
// prior to this when storing ASM code for cheats

char	*builder_name = "AnalogMan",
        version[7] = "v1.0.0",
        formattedVer[27];

int     game = -1;

void    always_run(void) {
    execute_all();
}

int    set_game(void) {
    u32 tid = get_tid_low();
    if (tid == 0x00055D00) {
        game = 0; ///< Pokémon X
        return 0;
    } else if (tid == 0x00055E00) {
        game = 1; ///< Pokémon Y
        return 0;
    } else {
        return 1;
    }
}

void	my_menus(void) {

    if (set_game()) {
        new_unselectable_entry("Unsupported game");
        return;
    }
    overlayInit();
    xsprintf(formattedVer, "%19s", version);
    new_unselectable_entry("Entries w/ an orange background");
    new_unselectable_entry("have notes. Press (Y) to view.");
    new_super_unselectable_entry(formattedVer, always_run);
	new_separator();
    battleMenu();
    movementMenu();
    miscMenu();
}
