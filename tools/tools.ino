/*
  Hello, World! example
  June 11, 2015
  Copyright (C) 2015 David Martinez
  All rights reserved.
  This code is the most basic barebones code for writing a program for Arduboy.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
*/

#include <Arduboy2.h>
#include "src/radar/DetectedPoint.h"
#include "src/radar/Radar.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;

// angle of the scanner first line
float angle = 0;

float speed = 0.1;

// Number to start the counter
int counter = 44;
int counterDecimal = 7;
int moving = 10;

DetectedPoint points[5] {
    DetectedPoint(),
    DetectedPoint(),
    DetectedPoint(),
    DetectedPoint(),
    DetectedPoint()
};

int indexLastActivatedPoint = 0;

Radar radar;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup()
{
    // initiate arduboy instance
    arduboy.begin();

    // here we set the framerate to 15, we do not need to run at
    // default 60 and it saves us battery life
    arduboy.setFrameRate(15);

    arduboy.initRandomSeed();
}

// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop()
{
    // pause render until it's time for the next frame
    if (!(arduboy.nextFrame()))
        return;

    // first we clear our screen to black
    arduboy.clear();
    arduboy.pollButtons();

    // we set our cursor 5 pixels to the right and 10 down from the top
    // (positions start at 0, 0)
    arduboy.setCursor(4, 9);

    radar.init(arduboy);
    drawScanner();
    drawCounter();

    if (arduboy.justPressed(A_BUTTON)) {
        handlePointsVisibility();
    }

    animatePoints();

    // then we finaly we tell the arduboy to display what we just wrote to the display
    arduboy.display();
}

void drawCounter()
{
    arduboy.setTextSize(1);
    arduboy.setCursor(arduboy.width() - 29, 3);
    arduboy.print(counter);
    arduboy.print(".");
    arduboy.print(counterDecimal);

    if (moving == arduboy.frameCount) {
        moving = arduboy.frameCount + 2;
        counterDecimal = rand() % 9 + 0;
    }

        arduboy.setCursor(3, arduboy.height() - 9);
        arduboy.print(indexLastActivatedPoint);
}

void drawScanner()
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

void drawCircleCentered(int rayon)
{
    arduboy.drawCircle(
        arduboy.width() / 2,
        arduboy.height() / 2,
        rayon,
        WHITE
    );
}

void animatePoints()
{
    for (int i=0; i < 5; i++) {
        points[i].animate(arduboy);
    }
}

void initPoint(int i)
{
    points[i].show();
    points[i].setPosition(
        random(20, 108),
        random(10, 54)
    );
}

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
