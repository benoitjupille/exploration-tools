#ifndef CONTACTLIST_H
#define CONTACTLIST_H

struct ContactList
{

    // Amount of different characters in the game
    int numberOfCharacters = 3;

    /**
     * Selects the character index according to buttons pushed
     */
    int selectCharacter(Arduboy2 arduboy, int selectedCharacter)
    {
        if (arduboy.justPressed(DOWN_BUTTON) && selectedCharacter < numberOfCharacters - 1) {
            return selectedCharacter + 1;
        }

        if (arduboy.justPressed(UP_BUTTON) && selectedCharacter > 0) {
            return selectedCharacter - 1;
        }

        return selectedCharacter;
    }

    /**
     * Displays the title of contacts list Screen
     */
    void displayConctactsListTitle(Arduboy2 arduboy, int selectedCharacter)
    {
        if (selectedCharacter > 0) {
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
    void displayContactsList(Arduboy2 arduboy, int selectedCharacter)
    {
        int x = 53;

        // We remove a value to y based on the index. This will make the list to go up.
        int y = 32 - (26 * selectedCharacter);

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
};

#endif