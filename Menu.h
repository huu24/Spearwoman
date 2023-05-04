#ifndef MENU_H
#define MENU_H

#include "BaseObject.h"
#include "CommonFunc.h"

class Menu
{
public:
        Menu();
        ~Menu();

        void Handle(SDL_Event events, int& state);
        void Render(SDL_Renderer* screen, SDL_Texture* mBGMenuTexture, SDL_Texture* mButtonTexture);

private:
        enum MenuButton
        {
                PLAY, GUIDE, QUIT, TOTAL_BUTTONS
        };
//        SDL_Rect BackGroundTexture;
        SDL_Rect ButtonBox[TOTAL_BUTTONS];
        SDL_Rect Button[TOTAL_BUTTONS];
        SDL_Rect ButtonClip[TOTAL_BUTTONS][2];
        bool MouseOver[TOTAL_BUTTONS];
        int BUTTON_WIDTH = 319;
        int BUTTON_HEIGHT = 73;
};


class EndGameMenu
{
public:
        EndGameMenu();
        void Handle(SDL_Event events,int& state);
        void Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture);
        bool GetRestart() {return restart;}
private:
        int PLAY_AGAIN = 0;
        int HOME = 1;
        int TOTAL_BUTTON = 2;
       float xPos, yPos;
       SDL_Rect buttonBox[2];
       SDL_Rect button_clip[2][2];
       bool mouseOver[2];
       int Button_Width = 160;
       int Button_Height = 160;
       bool restart;
};

#endif //MENU_H
