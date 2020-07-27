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

    Timer mouthTimer;

    // Lines to display text
    ConversationLine lines[2] = {
        ConversationLine(),
        ConversationLine(),
    };

    int mouthsPosition[3][4] = {
        {30, 22, 2, 2},
        {26, 20, 2, 2},
        {26, 20, 2, 2}
    };

    void init()
    {
        animationTimer.updateCurrentTime();
        animationTimer.updatePreviousTime();
        mouthTimer.updateCurrentTime();
        mouthTimer.updatePreviousTime();
        lines[0].init(42);
        lines[1].init(52);
    }

    void display(Arduboy2 arduboy, uint8_t selectedCharacter)
    {
        animationTimer.updateCurrentTime();
        mouthTimer.updateCurrentTime();

        arduboy.drawRect(15, 0, 34, 34);
        Sprites::drawOverwrite(20, 7, charactersBmp, selectedCharacter);
        arduboy.fillRect(
            mouthsPosition[selectedCharacter][0],
            mouthsPosition[selectedCharacter][1],
            mouthsPosition[selectedCharacter][2],
            mouthsPosition[selectedCharacter][3],
            1
        );

        if (mouthTimer.getElapsedTime() >= random(300)) {
            mouthsPosition[selectedCharacter][2] = random(1, 3);
            mouthsPosition[selectedCharacter][3] = random(1, 3);
            mouthTimer.updatePreviousTime();
        }

        // displays first line
        lines[0].display();

        // for next lines, we check if previous line has finished to print
        for (uint8_t i=1; i<2; i++) {
            if (lines[i-1].locked) {
                lines[i].display();
            }
        }

        // Let some time before making new lines
        if (animationTimer.getElapsedTime() >= random(6000, 7000)) {
            init();
        }
    }
};

#endif