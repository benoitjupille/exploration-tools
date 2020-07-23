#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduboy2.h>

struct Graphics
{

    static void drawCircleCentered(Arduboy2 arduboy, int rayon)
    {
        arduboy.drawCircle(
            arduboy.width() / 2,
            arduboy.height() / 2,
            rayon,
            WHITE
        );
    }
};

#endif