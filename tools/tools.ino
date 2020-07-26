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
#include <ArduboyTones.h>
#include "src/shared/Graphics.h"
#include "src/shared/Timer.h"
#include "src/radar/Radar.h"
#include "src/phone/Phone.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Radar radar;
Phone phone;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup()
{
    // initiate arduboy instance
    arduboy.begin();

    // here we set the framerate to 15, we do not need to run at
    // default 60 and it saves us battery life
    arduboy.setFrameRate(30);

    arduboy.initRandomSeed();
    arduboy.setCursor(0, 0);
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

    //radar.display(arduboy);
    phone.display(arduboy, sound);

    // then we finaly we tell the arduboy to display what we just wrote to the display
    arduboy.display();
}


