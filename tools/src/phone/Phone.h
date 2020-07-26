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
    uint8_t selectedCharacter = 0;

    // Screens
    enum struct Screen {
        ContactList,        // the list of contacts to chose
        Hanging,            // call is launched, you wait for the character to pickup
        Conversation        // the character and you have a conversation
    };

    // Selected screen
    Screen screen = Screen::ContactList;

    // Tells us if a screen transition occurs
    bool needToPlayHangingIntro = false;

    uint8_t xConversationStart = 10;

    uint8_t conversationLine[108];
    uint8_t lineBufferIndex = 0;

    void display(Arduboy2 arduboy, ArduboyTones sound)
    {
        switch (screen) {
            case Screen::ContactList:
                contactListScreen(arduboy);
                break;
            case Screen::Conversation:
                displayConversation(arduboy);
                break;
            case Screen::Hanging:
                hangingCallScreen(arduboy, sound);
                break;
        }
    }

    void contactListScreen(Arduboy2 arduboy)
    {
        controlsContactsList(arduboy);
        contactList.displayConctactsListTitle(arduboy, selectedCharacter);
        contactList.displayContactsList(arduboy, selectedCharacter);
    }

    void hangingCallScreen(Arduboy2 arduboy, ArduboyTones sound)
    {
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
            screen = Screen::ContactList;
        }

        if (hanging) {
            return;
        }

        screen = Screen::Conversation;

        // Populates line buffer with random indexes of alphabet symbols
        for (int i=0; i<108; i++) {
            conversationLine[i] = random(0, 30);
        }

        animationTimer.updatePreviousTime();
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
            screen = Screen::Hanging;
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
            screen = Screen::ContactList;
            return;
        }
    }
};

#endif