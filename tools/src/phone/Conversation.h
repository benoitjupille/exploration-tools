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

    // Mouths animation by character
    // x, y, height, width, smaller to bigger mouth
    int mouthsPosition[3][5] = {
        {30, 22, 2, 2, 1},
        {29, 21, 2, 2, 3},
        {29, 23, 2, 2, 4}
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

    void display(Arduboy2 arduboy, ArduboyTones sound, uint8_t selectedCharacter)
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


        // displays first line
        lines[0].display();

        // for next lines, we check if previous line has finished to print
        for (uint8_t i=1; i<2; i++) {
            if (lines[i-1].locked) {
                lines[i].display();
            }
        }

        for (uint8_t i=0; i<2; i++) {
            if (!lines[i].playing) {
                continue;
            }

            if (mouthTimer.getElapsedTime() >= random(200)) {
                mouthsPosition[selectedCharacter][2] = random(1, 3) * mouthsPosition[selectedCharacter][4];
                mouthsPosition[selectedCharacter][3] = random(1, 3);
                mouthTimer.updatePreviousTime();
            }

            if (!sound.playing()) {
                sound.tones(words[random(0, 6)]);
            }
        }

        // Let some time before making new lines
        if (animationTimer.getElapsedTime() >= random(4000, 10000)) {
            init();
        }
    }
};

#endif