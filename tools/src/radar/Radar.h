#ifndef RADAR_H
#define RADAR_H

#include <Arduboy2.h>
#include "../shared/Graphics.h"

/**
 * The radar is the main element. It contains the drawing of the circles
 * and the scanner (the lines that spin)
 *
 * The scanner is made by drawing lines next to each other.
 */
struct Radar
{

    Graphics graphics;

    // angle of the scanner first line
    float angle = 0;

    // speed of the scanner movement
    float speed = 0.1;

    void init(Arduboy2 arduboy)
    {
        graphics.drawCircleCentered(arduboy, 4);
        graphics.drawCircleCentered(arduboy, 16);
        graphics.drawCircleCentered(arduboy, 28);
    }
};

#endif
