#ifndef RADAR_H
#define RADAR_H

#include <Arduboy2.h>
#include "../shared/Graphics.h"
#include "DetectedPoint.h"

/**
 * The radar is the main element. It contains the drawing of the circles
 * and the scanner (the lines that spin)
 *
 * The scanner is made by drawing lines next to each other.
 *
 * It also contains the points that are shown on the radar.
 */
struct Radar
{

    Graphics graphics;

    // angle of the scanner first line
    float angle = 0;

    // speed of the scanner movement
    float speed = 0.1;

    // Number to start the counter
    int counter = 44;

    // Decimals of the counter
    int counterDecimal;

    // The next frame when the counter should be updated
    int frameToAnimateCounter = 10;

    // Collection of points
    DetectedPoint points[5] {
        DetectedPoint(),
        DetectedPoint(),
        DetectedPoint(),
        DetectedPoint(),
        DetectedPoint()
    };

    // Last activated points
    int indexLastActivatedPoint = 0;

    /**
     * Displays the radar and the points
     */
    void display(Arduboy2 arduboy)
    {
        graphics.drawCircleCentered(arduboy, 4);
        graphics.drawCircleCentered(arduboy, 16);
        graphics.drawCircleCentered(arduboy, 28);

        drawScanner(arduboy);

        if (arduboy.justPressed(A_BUTTON)) {
            handlePointsVisibility();
        }

        animatePoints(arduboy);
        drawCounter(arduboy);
    }

    /**
     * Draws the scanner animation
     */
    void drawScanner(Arduboy2 arduboy)
    {
        float line = 1;

        while (line > 0) {
            arduboy.drawLine(
                arduboy.width() / 2, arduboy.height() / 2,
                arduboy.width() / 2 + cos(angle - line) * 28, arduboy.height() / 2 + sin(angle - line) * 28,
                WHITE
            );
            line = line - 0.02;
        }

        angle = angle + speed;

        if (angle == 1) {
            angle = 0;
        }
    }

    /**
     * Plays the blinking animation of points
     */
    void animatePoints(Arduboy2 arduboy)
    {
        for (int i=0; i < 5; i++) {
            points[i].animate(arduboy);
        }
    }

    /**
     * Init a point to be displayed
     */
    void initPoint(int i)
    {
        points[i].show();
        points[i].setPosition(
            random(20, 108),
            random(10, 54)
        );
    }

    /**
     * According to the index of the last activated point,
     * this function will determine which point is about to be activated,
     * activates it if possible, or reset the points to hidden state
     */
    void handlePointsVisibility()
    {
        if (indexLastActivatedPoint == 5) {
            indexLastActivatedPoint = 0;
            // hide all points
            for (int i=0; i<5; i++) {
                points[i].hide();
            }

            return;
        }

        initPoint(indexLastActivatedPoint);
        indexLastActivatedPoint++;
    }

    void drawCounter(Arduboy2 arduboy)
    {
        arduboy.setTextSize(1);
        arduboy.setCursor(arduboy.width() - 29, 3);
        arduboy.print(counter);
        arduboy.print(".");
        arduboy.print(counterDecimal);

        if (frameToAnimateCounter == arduboy.frameCount) {
            frameToAnimateCounter = arduboy.frameCount + 2;
            counterDecimal = rand() % 9 + 0;
        }

            arduboy.setCursor(3, arduboy.height() - 9);
            arduboy.print(indexLastActivatedPoint);
    }
};

#endif
