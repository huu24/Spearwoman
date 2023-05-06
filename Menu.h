#ifndef MENU_H
#define MENU_H

#include "BaseObject.h"
#include "CommonFunc.h"

class Menu
{
public:
        Menu();
        ~Menu();

        void Handle(SDL_Event events, int& state, Mix_Chunk *mSound[]);
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
        void Handle(SDL_Event events,int& state, Mix_Chunk *eSound[]);
        void Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture);
        bool GetRestart() {return restart;}
private:
        enum Button
        {
                PLAY_AGAIN,
                HOME,
                TOTAL_BUTTON
        };

       float xPos, yPos;
       SDL_Rect buttonBox[TOTAL_BUTTON];
       SDL_Rect button_clip[TOTAL_BUTTON][2];
       bool mouseOver[TOTAL_BUTTON];
       int Button_Width = 160;
       int Button_Height = 160;
       bool restart;
};

class PauseMenu
{
public:
        PauseMenu();
        void Handle(SDL_Event events,int& state, Mix_Chunk *pSound[]);
        void Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture);
        bool GetRestart() {return restart;}
private:
        enum Button
        {
                Play_Again,
                Resume,
                Home,
                Total_Button
        };

       float xPos, yPos;
       SDL_Rect buttonBox[Total_Button];
       SDL_Rect button_clip[Total_Button][2];
       bool mouseOver[Total_Button];
       int Button_Width = 160;
       int Button_Height = 160;
       bool restart;
};

class Guide
{
public:
        Guide();
        void Handle(SDL_Event events, int& state, Mix_Chunk *gSound[]);
        void Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture);
private:
       SDL_Rect backButtonBox;
       SDL_Rect button_clip[2];
       bool mouseOver;
       int Button_Width = 80;
       int Button_Height = 80;
};

#endif //MENU_H
