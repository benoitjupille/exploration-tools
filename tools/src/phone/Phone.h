#ifndef PHONE_H
#define PHONE_H

#include "bitmaps.h"
#include "tones.h"
#include "ContactList.h"
#include "HangingCall.h"

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

    // HangingCall animation
    HangingCall hangingCall;

    // Index of the displayed character
    int selectedCharacter = 0;

    // Screen number
    // 0: contacts list
    // 1: call hanging
    // 2: conversation
    int screen = 0;

    // Tells us if a screen transition occurs
    bool needToPlayHangingIntro = false;

    int xConversationStart = 10;

    int conversationLine[108];
    int lineBufferIndex = 0;

    void display(Arduboy2 arduboy, ArduboyTones sound)
    {
        switch (screen) {
            case 0:
                controlsContactsList(arduboy);
                contactList.displayConctactsListTitle(arduboy, selectedCharacter);
                contactList.displayContactsList(arduboy, selectedCharacter);
                break;
            case 2:
                displayConversation(arduboy);
                break;
            case 1:
                // Intro has not finished playing
                if (needToPlayHangingIntro) {
                    needToPlayHangingIntro = hangingCall.introIsPlaying(arduboy, selectedCharacter);
                    return;
                }

                // Hanging animation
                bool hanging = hangingCall.hanging(
                    arduboy,
                    sound,
                    selectedCharacter
                );

                if (arduboy.justPressed(B_BUTTON)) {
                    screen = 0;
                }

                if (hanging) {
                    return;
                }

                screen = 2;

                // Populates line buffer with random indexes of alphabet symbols
                for (int i=0; i<108; i++) {
                    conversationLine[i] = random(0, 30);
                }
                animationTimer.updatePreviousTime();

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
            needToPlayHangingIntro = true;
            hangingCall.init();
        }
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