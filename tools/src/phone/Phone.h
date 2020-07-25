#ifndef PHONE_H
#define PHONE_H

#include "bitmaps.h"
#include "ContactList.h"

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

    // List of contacts
    ContactList contactList;

    int hangingRandomTime;

    // Index of the displayed character
    int selectedCharacter = 0;

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

    int conversationLine[108];
    int lineBufferIndex = 0;

    void display(Arduboy2 arduboy)
    {
        switch (screen) {
            case 0:
                controlsContactsList(arduboy);
                contactList.displayConctactsListTitle(arduboy, selectedCharacter);
                contactList.displayContactsList(arduboy, selectedCharacter);
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
        selectedCharacter = contactList.selectCharacter(arduboy, selectedCharacter);

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

            // Populates line buffer with random indexes of alphabet symbols
            for (int i=0; i<128; i++) {
                conversationLine[i] = random(0, 30);
            }
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
        Sprites::drawOverwrite(x, y, charactersBmp, selectedCharacter);
        arduboy.drawCircle(x + 11, y + 10, 18);
    }

    void displayConversation(Arduboy2 arduboy)
    {
        animationTimer.updateCurrentTime();
        Sprites::drawOverwrite(10, 10, charactersBmp, selectedCharacter);

        if (animationTimer.getElapsedTime() >= random(0, 200) && lineBufferIndex < sizeof(conversationLine) / sizeof(conversationLine[0])) {
            lineBufferIndex = lineBufferIndex + random(1, 7);
            animationTimer.updatePreviousTime();
        }

        for (int i=0; i<lineBufferIndex; i++) {
            Sprites::drawOverwrite(xConversationStart + i, 40, alphabetBmp, conversationLine[i]);
        }

        if (arduboy.justPressed(B_BUTTON)) {
            screen = 0;
            return;
        }
    }
};

#endif