#ifndef PHONE_H
#define PHONE_H

#include <Arduboy2.h>
#include "bitmaps.h"
#include "../shared/Timer.h"

/**
 * A visio app to call Monkey or Frog or Robot
 *
 * You start with your contacts list, you chose one by pressing A,
 * the app will call him.
 */
struct Phone
{

    // Timer for animations
    Timer animationTimer;

    // Timer to randomize the wait of the character to answer call
    Timer hangingTimer;

    int hangingRandomTime;

    // Index of the displayed character
    int characterIndex = 0;

    // Screen number
    // 0: contacts list
    // 1: call hanging
    // 2: conversation
    int screen = 0;

    // Tells us if a screen transition occurs
    bool screenJustSwitched = false;

    // When a call is hanging, we animate a line of points
    // between the character avatar and the phone icon.
    // We hide a point on this line to make a movement from left
    // to right
    int lastHiddenHangingCallPoint = 0;

    int xAnimationCall = 53;
    int yAnimationCall = 22;

    int xConversationStart = 10;

    // Amount of different characters in the game
    int numberOfCharacters = 3;

    void display(Arduboy2 arduboy)
    {
        switch (screen) {
            case 0:
                controlsContactsList(arduboy);
                displayConctactsListTitle(arduboy);
                displayContactsList(arduboy);
                break;
            case 1:
                displayCallHanging(arduboy);
                break;
            case 2:
                displayConversation(arduboy);
                break;
        }
    }

    /**
     * Controls the actions you can make on the
     * contacts list screen
     */
    void controlsContactsList(Arduboy2 arduboy)
    {
        if (arduboy.justPressed(DOWN_BUTTON) && characterIndex < numberOfCharacters - 1) {
            characterIndex++;
        }

        if (arduboy.justPressed(UP_BUTTON) && characterIndex > 0) {
            characterIndex--;
        }

        if (arduboy.justPressed(A_BUTTON)) {
            animationTimer.updateCurrentTime();
            animationTimer.updatePreviousTime();
            hangingTimer.updateCurrentTime();
            hangingTimer.updatePreviousTime();
            screen = 1;
            screenJustSwitched = true;
            xAnimationCall = 54;
            hangingRandomTime = random(2000, 5000);
        }
    }

    /**
     * Displays the title of contacts list Screen
     */
    void displayConctactsListTitle(Arduboy2 arduboy)
    {
        if (characterIndex > 0) {
            return;
        }

        arduboy.setCursor(20, 3);
        arduboy.setTextSize(2);
        arduboy.print("CONTACTS");
        arduboy.drawLine(0, 25, arduboy.width(), 25);
    }

    /**
     * Displays contacts as a list
     * When we reached the bottom of the screen but there are still
     * contacts in the list, we make the character avatars going up
     */
    void displayContactsList(Arduboy2 arduboy)
    {
        int x = 53;

        // We remove a value to y based on the index. This will make the list to go up.
        int y = 32 - (26 * characterIndex);

        for (int i=0; i < numberOfCharacters; i++) {
            Sprites::drawOverwrite(x, y, charactersBmp, i);
            y = y + 26;
        }

        // The cursor
        arduboy.fillTriangle(
            x - 20, 43- 4,
            x - 20, 43 + 4,
            x - 16, 43
        );
    }

    void displayCallHanging(Arduboy2 arduboy)
    {
        animationTimer.updateCurrentTime();
        hangingTimer.updateCurrentTime();

        if (screenJustSwitched) {
            animationCallLaunched(arduboy);
            return;
        }

        drawAvatar(arduboy, xAnimationCall, yAnimationCall);
        Sprites::drawOverwrite(97, yAnimationCall , iconsBmp, 0);

        for (int i=0; i<40; i++) {
            if (i % 2 == 0) {
                arduboy.drawPixel(60 + i, 32);
            }
        }

        if (lastHiddenHangingCallPoint > 39) {
            lastHiddenHangingCallPoint = 0;
        }

        if (animationTimer.getElapsedTime() >= 20) {
            arduboy.drawPixel(60 + lastHiddenHangingCallPoint, 32, BLACK);
            animationTimer.updatePreviousTime();
            lastHiddenHangingCallPoint = lastHiddenHangingCallPoint + 2;
        }

        if (arduboy.justPressed(B_BUTTON)) {
            screen = 0;
            return;
        }

        if (hangingTimer.getElapsedTime() >= hangingRandomTime) {
            screen = 2;
            animationTimer.updatePreviousTime();
        }
    }

    void animationCallLaunched(Arduboy2 arduboy)
    {
        if (xAnimationCall < 25) {
            xAnimationCall = 25;
        }

        if (animationTimer.getElapsedTime() < 700) {
            drawAvatar(arduboy, xAnimationCall, yAnimationCall);
            return;
        }

        if (animationTimer.getElapsedTime() < 2000) {
            drawAvatar(arduboy, xAnimationCall, yAnimationCall);
            xAnimationCall = xAnimationCall - 2;

            return;
        }

        screenJustSwitched = false;
    }

    /**
     * Draws the avatar of the selecter char at the position you want
     */
    void drawAvatar (Arduboy2 arduboy, int x, int y)
    {
        Sprites::drawOverwrite(x, y, charactersBmp, characterIndex);
        arduboy.drawCircle(x + 11, y + 10, 18);
    }

    void displayConversation(Arduboy2 arduboy)
    {
        animationTimer.updateCurrentTime();
        Sprites::drawOverwrite(10, 10, charactersBmp, characterIndex);
        
        if (animationTimer.getElapsedTime() >= 300 && xConversationStart < 128) {
            Sprites::drawOverwrite(xConversationStart, 40, alphabetBmp, random(0, 30));
            xConversationStart = xConversationStart + 10;
            animationTimer.updatePreviousTime();
        }

        if (arduboy.justPressed(B_BUTTON)) {
            screen = 0;
            return;
        }
    }
};

#endif