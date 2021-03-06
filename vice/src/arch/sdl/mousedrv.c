/*
 * mousedrv.c - Mouse handling for SDL.
 *
 * Written by
 *  Hannu Nuotio <hannu.nuotio@tut.fi>
 *
 * Based on code by
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Oliver Schaertel <orschaer@forwiss.uni-erlangen.de>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "vice.h"

#include "vice_sdl.h"

#include "mouse.h"
#include "mousedrv.h"
#include "ui.h"

int mouse_x, mouse_y;
int mouse_accelx = 2, mouse_accely = 2;

void mousedrv_mouse_changed(void)
{
    ui_check_mouse_cursor();
}

int mousedrv_resources_init(void)
{
    return 0;
}

/* ------------------------------------------------------------------------- */

int mousedrv_cmdline_options_init(void)
{
    return 0;
}

/* ------------------------------------------------------------------------- */

void mousedrv_init(void)
{
}

/* ------------------------------------------------------------------------- */

void mouse_button(int bnumber, int state)
{
    if (bnumber == (int)SDL_BUTTON_LEFT) {
        mouse_button_left(state);
    }

    if (bnumber == (int)SDL_BUTTON_RIGHT) {
        mouse_button_right(state);
    }
}

BYTE mousedrv_get_x(void)
{
    static int last_mouse_x=0;

    if (last_mouse_x - mouse_x > 16) {
        last_mouse_x -= 16;
        return (BYTE)((last_mouse_x * mouse_accelx) >> 1) & 0x7e;
    }
    if (last_mouse_x - mouse_x < -16) {
        last_mouse_x += 16;
        return (BYTE)((last_mouse_x * mouse_accelx) >> 1) & 0x7e;
    }
    last_mouse_x = mouse_x;
    return (BYTE)((last_mouse_x * mouse_accelx) >> 1) & 0x7e;
}

BYTE mousedrv_get_y(void)
{
    static int last_mouse_y = 0;

    if (last_mouse_y - mouse_y > 16) {
        last_mouse_y -= 16;
        return (BYTE)((last_mouse_y * mouse_accely) >> 1) & 0x7e;
    }
    if (last_mouse_y - mouse_y < -16) {
        last_mouse_y += 16;
        return (BYTE)((last_mouse_y * mouse_accely) >> 1) & 0x7e;
    }
    last_mouse_y = mouse_y;
    return (BYTE)((last_mouse_y * mouse_accely) >> 1) & 0x7e;
}

void mouse_move(int x, int y)
{
    mouse_x += x;
    mouse_y -= y;
}
