#ifndef PHONE_H
#define PHONE_H

#include "bitmaps.h"
#include "tones.h"
#include "ContactList.h"
#include "HangingCall.h"
#include "Conversation.h"

/**
 * A visio app to call Monkey or Frog or Robot
 *
 * You start with your contacts list, you chose one by pressing A,
 * the app will call him.
 */
struct Phone
{

private:
    // Timer for animations
    Timer animationTimer;

    // Timer to randomize the wait of the character to answer call
    Timer hangingTimer;

    // List of contacts
    ContactList contactList;

    // HangingCall animation
    HangingCall hangingCall;

    // Conversation
    Conversation conversation;

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

public:
    void init() {
        selectedCharacter = 0;
        screen = Screen::ContactList;
    }

    void display(Arduboy2 arduboy, ArduboyTones sound)
    {
        switch (screen) {
            case Screen::ContactList:
                contactListScreen(arduboy);
                break;
            case Screen::Hanging:
                hangingCallScreen(arduboy, sound);
                break;
            case Screen::Conversation:
                conversationScreen(arduboy, sound);
                break;
        }
    }

private:
    /**
     * Handles contact list screen 
     */
    void contactListScreen(Arduboy2 arduboy)
    {
        controlsContactsList(arduboy);
        contactList.displayConctactsListTitle(arduboy, selectedCharacter);
        contactList.displayContactsList(arduboy, selectedCharacter);
    }

    /**
     * Handles hanging call screen
     */
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

        conversation.init();
        screen = Screen::Conversation;
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

    void conversationScreen(Arduboy2 arduboy, ArduboyTones sound)
    {
        conversation.display(arduboy, sound, selectedCharacter);
        if (arduboy.justPressed(B_BUTTON)) {
            screen = Screen::ContactList;
            return;
        }
    }
};

#endif