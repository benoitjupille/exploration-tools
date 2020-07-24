#ifndef PHONE_H
#define PHONE_H

#include <Arduboy2.h>
#include "bitmaps.h"

/**
 * A visio app to call Monkey or Frog or Robot
 *
 * You start with your contacts list, you chose one by pressing A,
 * the app will call him.
 */
struct Phone
{

    // Index of the displayed character
    int characterIndex = 0;

    // Screen number
    // 0: contacts list
    // 1: call hanging
    // 2: conversation
    int screen = 0;

    int selectorsY[3] = {
        43, 67, 81
    };

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
            screen = 1;
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
        int x = 55;
        int y = 32 - (26 * characterIndex);

        for (int i=0; i < numberOfCharacters; i++) {
            Sprites::drawOverwrite(x, y, characters, i);
            y = y + 26;
        }

        arduboy.fillTriangle(
            x - 20, 43- 4,
            x - 20, 43 + 4,
            x - 16, 43
        );
    }

    void displayCallHanging(Arduboy2 arduboy)
    {

    }

    void displayConversation(Arduboy2 arduboy)
    {

    }
};

#endif