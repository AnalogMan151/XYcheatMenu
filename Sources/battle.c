#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *      Battle Modifiers        *
 *                              *
 ********************************/

void    battleMenu(void)
{
    new_spoiler("Battle Codes");
    new_spoiler("PKMN Lv 100 after Battle");
        new_entry_managed_note("PKMN 1", "Press START during battle to activate", maxLevel1, MAXLEVEL1, 0);
        new_entry_managed_note("PKMN 2", "Press START during battle to activate", maxLevel2, MAXLEVEL2, 0);
        new_entry_managed_note("PKMN 3", "Press START during battle to activate", maxLevel3, MAXLEVEL3, 0);
        new_entry_managed_note("PKMN 4", "Press START during battle to activate", maxLevel4, MAXLEVEL4, 0);
        new_entry_managed_note("PKMN 5", "Press START during battle to activate", maxLevel5, MAXLEVEL5, 0);
        new_entry_managed_note("PKMN 6", "Press START during battle to activate", maxLevel6, MAXLEVEL6, 0);
    exit_spoiler();
        new_entry_managed("Infinite HP", infiniteHP, INFINITEHP, 0);
        new_entry_managed("Infinite PP", infinitePP, INFINITEPP, 0);
        new_entry_managed("Catch Trainer's Pokemon", catchTrainersPokemon, CATCHTRAINERSPOKEMON, 0);
        new_entry_managed("100% Catch", catch100, CATCH100, 0);
        new_entry_managed_note("Wild Pokemon Shiny", "Press L+START to toggle", shinyPokemon, SHINYPOKEMON, 0);

    exit_spoiler();
}

void    infiniteHP(void)
{
    u32 offset = 0;

    if (READU32(0x081FB284) > 0x08200000 && READU32(0x081FB624) > 0x08200000) {
        offset = READU32(0x081FB284);
        for (int i=0; i < 2; i++) {
            WRITEU16(offset + 0x0E, 999);
            WRITEU16(offset + 0x10, 999);
            offset = READU32(0x081FB624);
        }
    }
}

void    infinitePP(void)
{
    u32 offset = 0;

    if (READU32(0x081FB284) > 0x08200000 && READU32(0x81FB624) > 0x08200000) {
        offset = READU32(0x081FB284);
        for (int i=0; i<2; i++) {
            for (int j=0; j<4; j++) {
                WRITEU8(offset + 0x118, 99);
                WRITEU8(offset + 0x119, 99);
                WRITEU8(offset + 0x11E, 99);
                WRITEU8(offset + 0x11F, 99);
                offset += 0x0E;
            }
        offset = READU32(0x081FB624);
        }
    }
}

void    catchTrainersPokemon(void)
{
    if (checkAddress(0x08075474) && READU32(0x08075474) == 0xE5D00000) {
        WRITEU32(0x08075474, 0xE3A0B000);
        WRITEU32(0x08075478, 0xE5C0B000);
        WRITEU32(0x0807547C, 0xEA00000E);
    }
}

void    level100(int slot)
{
    u32 offset = 0;

    if (READU32(0x081FB284) > 0x08200000 && READU32(0x081FB624) > 0x08200000) {
        offset = READU32(0x081FB280 + (slot*0x04));
        WRITEU32(offset + 0x08, 0x00200000);
        offset = READU32(0x081FB620 + (slot*0x04));
        WRITEU32(offset + 0x08, 0x00200000);
    }
}

void    maxLevel1(void)
{
    if (is_pressed(BUTTON_ST))
        level100(1);
}

void    maxLevel2(void)
{
    if (is_pressed(BUTTON_ST))
        level100(2);
}

void    maxLevel3(void)
{
    if (is_pressed(BUTTON_ST))
        level100(3);
}

void    maxLevel4(void)
{
    if (is_pressed(BUTTON_ST))
        level100(4);
}

void    maxLevel5(void)
{
    if (is_pressed(BUTTON_ST))
        level100(5);
}

void    maxLevel6(void)
{
    if (is_pressed(BUTTON_ST))
        level100(6);
}

void    catch100(void)
{
    if (checkAddress(0x08073334) && READU32(0x08073334) == 0x0A000004)
        WRITEU32(0x08073334, 0xEA000004);
}

void    shinyPokemon(void)
{
    static const u32 offset[] =
    {
        0x080B9334,
        0x080B9338,
    };

    static const u32 data[] =
    {
        0xEBF88291,
        0xEBF88290,
    };

    static bool btn = false;

    if (READU32(0x0053ED8C) != 0xE12FFF1E) {
        WRITEU32(0x0053ED80, 0xE5C70004);
        WRITEU32(0x0053ED84, 0xEA000000);
        WRITEU32(0x0053ED88, 0xE5C71006);
        WRITEU32(0x0053ED8C, 0xE12FFF1E);
    }

    if (checkAddress(offset[game]) && READU32(offset[game]) == 0xE5C70004)
        WRITEU32(0x080B9334, data[game]);
    if (is_pressed(BUTTON_L + BUTTON_ST) && !btn) {
        btn = true;
        if (READU32(0x0053ED84) == 0xE3A01001)
            WRITEU32(0x0053ED84, 0xEA000000);
        else
            WRITEU32(0x0053ED84, 0xE3A01001);
    } else if (!is_pressed(BUTTON_L + BUTTON_ST)) {
        btn = false;
    }
}
