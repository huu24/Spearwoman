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


#endif // MENU_H


//#ifndef MENU_H
//#define MENU_H
//
//class Menu
//{
//private:
//    enum MenuTexture
//    {
//        BACKGROUND_TEXTURE,
//        BUTTON_TEXTURE,
//        TOTAL_TEXTURE
//    };
//    enum MenuButton
//    {
//        PLAY,
//        GUIDE,
//        QUIT,
//        TOTAL_BUTTON
//    };
////    static const int TOTAL_MENU_TITLE_SPRITES = 7;
//    SDL_Texture *gTexture[TOTAL_TEXTURE];
//    SDL_Rect backgroundBox, buttonBox[TOTAL_BUTTON];
//    SDL_Rect titleClips[TOTAL_MENU_TITLE_SPRITES];
//    SDL_Rect buttonClips[TOTAL_BUTTON][2];
//    int mouseover[TOTAL_BUTTON];
//    int cntTitleFrames;
//
//public:
//    static const int MENU_TITLE_WIDTH = 1024;
//    static const int MENU_TITLE_HEIGHT = 256;
//    static const int MENU_TITLE_TEXTURE_WIDTH = 2048;
//    static const int MENU_TITLE_TEXTURE_HEIGHT = 512;
//
//    static const int MENU_BUTTON_WIDTH = 256;
//    static const int MENU_BUTTON_HEIGHT = 64;
//    static const int MENU_BUTTON_TEXTURE_WIDTH = 1024;
//    static const int MENU_BUTTON_TEXTURE_HEIGHT = 256;
//
//
//    Menu(SDL_Texture *backgroundTexture = NULL, SDL_Texture *buttonTexture = NULL);
//    void handleEvent(SDL_Event &e, GameState &state);
//    void render(SDL_Renderer* screen);
//};
//
//
//#endif // MENU_H
