#ifndef BLINKINGPOINT_H
#define BLINKINGPOINT_H

#include <Arduboy2.h>
#include "../shared/Timer.h"

/**
 * Detected points by the radar.
 *
 * Those points are representated by an animation of a blinking point.
 */
struct DetectedPoint
{

private:
    // x position
    int x;

    // y position
    int y;

    // does the point has been activated
    bool visible = false;

    // the timer
    Timer pointTimer;

public:

    /**
     * Sets position of the point
     */
    void setPosition(int positionX, int positionY)
    {
        x = positionX;
        y = positionY;
    }

    /**
     * Set the visible flag to true, will be drawn on screen
     */
    void show()
    {
        visible = true;
    }

    /**
     * Set the visible flag to false, won't be drawn on screen
     */
    void hide()
    {
        visible = false;
    }

    /**
     * Handles animation to make a point blink on screen.
     *
     * The idea is to layer multiple cercles to create a filled circle.
     * The animation starts adding a single pixel, then wraps it in a
     * 1 pixel radius circle, then another circle of 2 pixels radius.
     *
     * It gives a circle that appears from its center, and deflate to finally disapper,
     * and repeats.
     */
    void animate(Arduboy2 arduboy)
    {
        // If the point is not visible, we don't draw
        if (!visible) {
            return;
        }

        pointTimer.updateCurrentTime();

        if (pointTimer.getElapsedTime() >= 1000) {
            arduboy.drawPixel(x, y, WHITE);
        }

        if (pointTimer.getElapsedTime() >= 1200 && pointTimer.getElapsedTime() < 1600) {
            arduboy.drawCircle(
                x, y,
                1,
                WHITE
            );
        }

        if (pointTimer.getElapsedTime() >= 1400 && pointTimer.getElapsedTime() < 1500) {
            arduboy.drawCircle(
                x, y,
                2,
                WHITE
            );
        }

        // animation lasts 1400 milliseconds
        if (pointTimer.getElapsedTime() >= 1600) {
            pointTimer.updatePreviousTime();
        }
    }
};

#endif