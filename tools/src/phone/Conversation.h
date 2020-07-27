#ifndef COnVERSATION_H
#define CONVERSATION_H

#include "ConversationLine.h"

/**
 * A screen to show the character speaking
 */
struct Conversation
{

    // Timer for animations
    Timer animationTimer;

    // Lines to display text
    ConversationLine lines[2] = {
        ConversationLine(),
        ConversationLine(),
    };

    void init()
    {
        animationTimer.updateCurrentTime();
        animationTimer.updatePreviousTime();
        lines[0].init(40);
        lines[1].init(50);
    }

    void display(uint8_t selectedCharacter)
    {
        animationTimer.updateCurrentTime();
        Sprites::drawOverwrite(10, 10, charactersBmp, selectedCharacter);

        lines[0].display();
        for (uint8_t i=1; i<2; i++) {
            if (lines[i-1].locked) {
                lines[i].display();
            }
        }

        if (animationTimer.getElapsedTime() >= random(6000, 7000)) {
            init();
        }
    }
};

#endif