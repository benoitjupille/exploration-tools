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

    // The player trigger the movement
    bool shouldMove = false;

    // How many pixels will it move
    int movingSpeed = 2;

    // Moves every x milliseconds
    int movingDelay = 700;

    // does the point has been activated
    bool visible = false;

    // the timer for blinking animation
    Timer animationTimer;

    // the timer for movement
    Timer movementTimer;

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
     * If the player has pressed on B while it
     * was the last point added, then it will make it moving
     */
    void makeItMove()
    {
        shouldMove = true;
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
    void display(Arduboy2 arduboy)
    {
        // If the point is not visible, we don't draw
        if (!visible) {
            return;
        }

        move(arduboy);

        animationTimer.updateCurrentTime();

        arduboy.drawPixel(x, y, WHITE);

        if (animationTimer.getElapsedTime() >= 1200 && animationTimer.getElapsedTime() < 1600) {
            arduboy.drawCircle(
                x, y,
                1,
                WHITE
            );
        }

        if (animationTimer.getElapsedTime() >= 1400 && animationTimer.getElapsedTime() < 1500) {
            arduboy.drawCircle(
                x, y,
                2,
                WHITE
            );
        }

        if (animationTimer.getElapsedTime() >= 1500 && animationTimer.getElapsedTime() < 1600) {
            arduboy.drawCircle(
                x, y,
                3,
                WHITE
            );
        }

        // animation lasts 1600 milliseconds
        if (animationTimer.getElapsedTime() >= 1600) {
            animationTimer.updatePreviousTime();
        }
    }

private:
    /**
     * Makes the point moving if it has been triggered (B Button)
     */
    void move(Arduboy2 arduboy)
    {
        if (!shouldMove) {
            return;
        }

        movementTimer.updateCurrentTime();

        if (movementTimer.getElapsedTime() < movingDelay) {
            return;
        }

        x = x + random(-movingSpeed, movingSpeed + 1);
        y = y + random(-movingSpeed, movingSpeed + 1);

        movementTimer.updatePreviousTime();
    }
};

#endif