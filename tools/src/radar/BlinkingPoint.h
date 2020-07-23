#ifndef BLINKINGPOINT_H
#define BLINKINGPOINT_H

#include <Arduboy2.h>

struct BlinkingPoint
{

private:
    int x;
    int y;
    bool visible = false;

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
     * Handles animation to make it blink
     */
    void animate(Arduboy2 arduboy)
    {
        if (!visible) {
            return;
        }

        pointTimer.updateCurrentTime();

        if (pointTimer.getElapsedTime() >= 1000)
        {
            arduboy.drawPixel(x, y, WHITE);
        }

        if (pointTimer.getElapsedTime() >= 1300 && pointTimer.getElapsedTime() < 1500)
        {
            arduboy.drawCircle(
                x,
                y,
                1,
                WHITE
            );
        }

        if (pointTimer.getElapsedTime() >= 1700)
        {
            pointTimer.updatePreviousTime();
        }
    }
};

#endif