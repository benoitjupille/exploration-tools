#ifndef COnVERSATIONLINE_H
#define CONVERSATIONLINE_H

/**
 * A line of Conversation
 */
struct ConversationLine
{

    Arduboy2 arduboy;

    // Timer for animations
    Timer animationTimer;

    // y position of line
    uint8_t y;

    // pixels size of one char in our alphabet bitmap
    uint8_t charSize = 8;

    // Max length of a line
    uint8_t maxLength = 13;

    // Random symbols that make a line
    uint8_t symbols[13];

    // buffer index to animate a line
    uint8_t bufferIndex = 0;

    // The size of alphabet
    // The last char is a space character
    uint8_t alphabetSize = 30;

    // Is the buffer moving forward ?
    // We need this to sync the sound and the mouth character animation
    bool playing = false;

    // line is printed completely
    bool locked = false;

    void init(uint8_t yPosition)
    {
        arduboy.initRandomSeed();
        animationTimer.updateCurrentTime();
        animationTimer.updatePreviousTime();
        y = yPosition;
        bufferIndex = 0;
        locked = false;
        playing = false;

        // Populates line buffer with random indexes of alphabet symbols
        for (int i=0; i<10; i++) {
            symbols[i] = random(0, alphabetSize);
            randomSpace(i);
        }

        // We make sure that the first char is not a space
        symbols[0] = random(0, alphabetSize - 1);
    }

    /**
     * inserts random space
     */
    void randomSpace(uint8_t index)
    {
        if (3 % random(1, 6)) {
            symbols[index] = 30;
        }
    }

    void display()
    {
        animationTimer.updateCurrentTime();
        playing = false;

        // we increment the buffer size every random time to make typing animation
        if (animationTimer.getElapsedTime() >= random(100, 600) && bufferIndex < maxLength) {
            bufferIndex = bufferIndex + random(1, 4);
            animationTimer.updatePreviousTime();
            playing = true;
        }

        for (int i=0; i<bufferIndex; i++) {
            writeBuffer(i);
        }

        if (bufferIndex >= maxLength - 1) {
            locked = true;
            playing = false;
        }
    }

    /**
     * write the char a buffer position
     */
    void writeBuffer(uint8_t i)
    {
        Sprites::drawOverwrite(charSize * i + maxLength, y, alphabetBmp, symbols[i]);
    }
};

#endif