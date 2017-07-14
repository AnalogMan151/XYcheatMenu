#include "cheats.h"
#include "hid.h"

void movementMenu(void)
{
    new_spoiler("Movement Codes");
        new_entry_managed_note("Walk Through Walls", "Hold R = Enable\nPress R+A to toggle", walkThruWalls, WALKTHRUWALLS, 0);
        new_entry_managed_note("Walk Faster", "Only works with walking (D-Pad)\n\nOpen menu after disabling", walkFaster, WALKFASTER, 0);
    exit_spoiler();
}

void   walkThruWalls(void)
{
    static bool permActivation = false;
    static bool btn = false;

    static const u32 offset1 = 0x0053ED50;

    static const u32 offset2[][2] =
    {
        {0x080B5820, 0x080B3A1C},
        {0x080B5824, 0x080B3A20},
    };

    static const u32 data[][2] =
    {
        {0xEBF8914A, 0xEBF898CD},
        {0xEBF89149, 0xEBF898CC},
    };

    WRITEU32(offset1 + 0x0, 0xE1A01000);
    WRITEU32(offset1 + 0x4, 0xE12FFF1E);
    WRITEU32(offset1 + 0x8, 0xE1A06000);
    WRITEU32(offset1 + 0xC, 0xE12FFF1E);
    if (is_pressed(BUTTON_R) || permActivation) {
        WRITEU32(offset1 + 0x0, 0xE3A01000);
        WRITEU32(offset1 + 0x8, 0xE3A06000);
        if (is_pressed(BUTTON_R + BUTTON_A) && !btn) {
            permActivation = !permActivation;
            btn = true;
        } else if (!is_pressed(BUTTON_R + BUTTON_A)) {
            btn = false;
        }
    }

    if (checkAddress(offset2[game][0]) && READU32(offset2[game][0]) == 0xE1A01000)
        WRITEU32(offset2[game][0], data[game][0]);
    if (checkAddress(offset2[game][1]) && READU32(offset2[game][1]) == 0xE1A06000)
        WRITEU32(offset2[game][1], data[game][1]);
}

void walkFaster(void)
{
    if (checkAddress(0x08092F38) && READU32(0x08092F38) == 0x03A05007) {
        WRITEU32(0x08092DE4, 0x13A05003);
        WRITEU32(0x08092DE8, 0x03A05002);
        WRITEU32(0x08092F34, 0x13A05005);
        WRITEU32(0x08092F38, 0x03A05003);
    }
}
