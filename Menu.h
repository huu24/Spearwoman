#ifndef MENU_H
#define MENU_H

#include "BaseObject.h"
#include "CommonFunc.h"

class Menu
{
public:
        Menu();
        ~Menu();

        void Handle(SDL_Event events);
        void Render(SDL_Renderer* screen, SDL_Texture* mMenuTexture);

private:
        enum MenuButton
        {
                PLAY, GUIDE, QUIT, TOTAL_BUTTONS
        };
        SDL_Rect BackGroundTexture;
        SDL_Rect ButtonBox[TOTAL_BUTTONS];
        SDL_Rect Button[TOTAL_BUTTONS];
        SDL_Rect ButtonClip[TOTAL_BUTTONS][2];
        bool MouseOver[TOTAL_BUTTONS];
};


#endif // MENU_H
