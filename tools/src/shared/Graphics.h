#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * Drawing graphic helpers
 */
struct Graphics
{

    /**
     * Draws a circle at the center of the screen,
     * with the given radius
     */
    static void drawCircleCentered(Arduboy2 arduboy, int radius)
    {
        arduboy.drawCircle(
            arduboy.width() / 2,
            arduboy.height() / 2,
            radius,
            WHITE
        );
    }
};

#endif