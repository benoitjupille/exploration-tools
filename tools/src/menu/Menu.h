#ifndef MENU_H
#define MENU_H

/**
 * Main menu of the app
 */
struct MENU_H
{

    enum struct Screen {
        Phone,
        Radar
    }

    Screen screen = Screen::Phone;

    void display()
    {
        switch (screen) {
            case Screen::Phone:
                break;
            case Screen::Radar:
                break;
        }
    }
};

#endif