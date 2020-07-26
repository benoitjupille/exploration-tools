#ifndef HANGINGCALL_H
#define HANGINGCALL_H

/**
 * A class to show an animation when a call is hanging
 */
struct HangingCall
{

private:
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

    // initial position of centered avatar
    int const xForAvatarCenterd = 53;

    // X position of where the animation begins
    int xAnimation = 53;

    // Y position of where the animation begins
    int yAnimation = 22;

public:
    /**
     * initialize the animation
     */
    void init()
    {
        animationTimer.updateCurrentTime();
        animationTimer.updatePreviousTime();
        hangingTimer.updateCurrentTime();
        hangingTimer.updatePreviousTime();
        hangingTime = random(4000, 10000);
    }

    /**
     * Intro is playing. Returns true when the animation
     * is still playing.
     * 
     * The intro shows an avatar of the selected char in the
     * center of the screen, then this avatar moves to the left.
     * 
     * The animation stops when the avatar is on the left
     */
    bool introIsPlaying(Arduboy2 arduboy, int selectedCharacter)
    {
        animationTimer.updateCurrentTime();

        // We limit the avatar position to avoid getting of the screen
        if (xAnimation < 25) {
            xAnimation = 25;
        }

        // Stays at center for a moment
        if (animationTimer.getElapsedTime() < 700) {
            drawAvatar(arduboy, xAnimation, yAnimation, selectedCharacter);
            return true;
        }

        // Slides to the left
        if (animationTimer.getElapsedTime() < 2000) {
            drawAvatar(arduboy, xAnimation, yAnimation, selectedCharacter);
            xAnimation = xAnimation - 2;
            return true;
        }

        // Done
        animationTimer.updatePreviousTime();
        hangingTimer.updatePreviousTime();
        return false;
    }

    /**
     * Displays the animation loop when we wait to the character to
     * pick up the phone
     * 
     * The avatar is shown on the left, and a phone icon on the right.
     */
    bool hanging(Arduboy2 arduboy, ArduboyTones sound, int selectedCharacter)
    {
        hangingTimer.updateCurrentTime();
        animationTimer.updateCurrentTime();

        // Avatar shown on left
        drawAvatar(arduboy, xAnimation, yAnimation, selectedCharacter);
        // Phone at the right
        Sprites::drawOverwrite(97, yAnimation , iconsBmp, 0);

        // draws a line of points between the avatar and the phone
        for (int i=0; i<40; i++) {
            if (i % 2 == 0) {
                arduboy.drawPixel(60 + i, 32);
            }
        }

        // we blink points one by one, from left to right
        if (animationTimer.getElapsedTime() >= 20) {
            arduboy.drawPixel(60 + lastHiddenHangingCallPoint, 32, BLACK);
            animationTimer.updatePreviousTime();
            lastHiddenHangingCallPoint = lastHiddenHangingCallPoint + 2;
        }

        // Points blinking loop
        if (lastHiddenHangingCallPoint > 39) {
            lastHiddenHangingCallPoint = 0;
        }

        //sound.tones(song1);

        if (animationTimer.getElapsedTime() >= 300) {
            sound.noTone();
            animationTimer.updatePreviousTime();
        }

        // We wait for the character to pick up
        if (hangingTimer.getElapsedTime() < hangingTime) {
            return true;
        }

        sound.noTone();

        // Animation is finished, character picked up
        animationTimer.updatePreviousTime();
        hangingTimer.updatePreviousTime();
        xAnimation = xForAvatarCenterd;
        return false;
    }

private:

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