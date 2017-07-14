#include "cheats.h"
#include "hid.h"

void miscMenu(void)
{
    new_spoiler("Misc Codes");
        new_entry_arg_note("Access PC Anywhere", "Use tiny Settings button along bottom of lower screen to access PC", accessPC, 0, ACCESSPC, TOGGLE);
        new_entry_managed("Instant Text", instantText, INSTANTTEXT, 0);
        new_entry_managed_note("Quick Egg Delivery", "Press START to force egg", quickDayCare, QUICKDAYCARE, 0);
        new_entry_managed("Instant Egg Hatching", instantHatch, INSTANTHATCH, 0);

    exit_spoiler();
}

void accessPC(u32 state)
{
    if (state)
        WRITEU32(0x003BBFA8, 0xE3A00004);
    else
        WRITEU32(0x003BBFA8, 0xE3A00018);
}

void    instantText(void)
{
    WRITEU32(0x003F6FB4, 0xE3A04003);
    WRITEU32(0x003F7818, 0xE3A05003);
}

void quickDayCare(void)
{
    if (is_pressed(BUTTON_ST) && checkAddress(0x08C67234))
        WRITEU16(0x08C67234, 0x0100);
}

void instantHatch(void)
{
    if (checkAddress(0x08C67261))
        WRITEU16(0x08C67261, 0x0100);
}
