#ifndef HANGINGCALL_H
#define HANGINGCALL_H

/**
 * A class to show an animation when a call is hanging
 */
struct HangingCall
{

    // Timer for animations
    Timer animationTimer;

    // Timer to randomize the wait of the character to answer call
    Timer hangingTimer;

    // A random time in milliseconds that the called character will pick up
    int hangingTime;

    // When a call is hanging, we animate a line of points
    // between the character avatar and the phone icon.
    // We hide a point on this line to make a movement from left
    // to right
    int lastHiddenHangingCallPoint = 0;

    /**
     * X position of where the animation begins
     */
    int xAnimationCall = 53;

    /**
     * Y position of where the animation begins
     */
    int yAnimationCall = 22;

    void init()
    {
        animationTimer.updateCurrentTime();
        animationTimer.updatePreviousTime();
        hangingTimer.updateCurrentTime();
        hangingTimer.updatePreviousTime();
    }

    bool hanging(Arduboy2 arduboy, ArduboyTones sound, int hangingTimeToWait, int selectedCharacter)
    {
        hangingTimer.updateCurrentTime();
        animationTimer.updateCurrentTime();

        drawAvatar(arduboy, xAnimationCall, yAnimationCall, selectedCharacter);
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

        //sound.tones(song1);

        if (animationTimer.getElapsedTime() >= 300) {
            sound.noTone();
            animationTimer.updatePreviousTime();
        }

        // We wait for the character to pick up
        if (hangingTimer.getElapsedTime() < hangingTimeToWait) {
            return true;
        }

        sound.noTone();

        // Animation is finished, character picked up
        animationTimer.updatePreviousTime();
        hangingTimer.updatePreviousTime();
        xAnimationCall = 54;
        return false;
    }

    bool introIsPlaying(Arduboy2 arduboy, int selectedCharacter)
    {
        animationTimer.updateCurrentTime();

        if (xAnimationCall < 25) {
            xAnimationCall = 25;
        }

        if (animationTimer.getElapsedTime() < 700) {
            drawAvatar(arduboy, xAnimationCall, yAnimationCall, selectedCharacter);
            return true;
        }

        if (animationTimer.getElapsedTime() < 2000) {
            drawAvatar(arduboy, xAnimationCall, yAnimationCall, selectedCharacter);
            xAnimationCall = xAnimationCall - 2;
            return true;
        }

        animationTimer.updatePreviousTime();
        hangingTimer.updatePreviousTime();
        return false;
    }

    /**
     * Draws the avatar of the selecter char at the position you want
     */
    void drawAvatar(Arduboy2 arduboy, int x, int y, int selectedCharacter)
    {
        Sprites::drawOverwrite(x, y, charactersBmp, selectedCharacter);
        arduboy.drawCircle(x + 11, y + 10, 18);
    }
};

#endif