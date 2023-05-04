#include "Menu.h"

Menu::Menu()
{
        int y = 6;
        for(int i = 0; i < TOTAL_BUTTONS; i++)
        {
                ButtonBox[i]= {0, y, 319, 73};
                y += 73;
        }
        int x = 0;
        for(int i = 0; i < TOTAL_BUTTONS; i++)
        {
                ButtonClip[i][0] = {0, 73*i, 319, 73};
                ButtonClip[i][1] = {319, 73*i, 319, 73};
                MouseOver[i] = 0;
        }
}

Menu::~Menu()
{

}

void Menu::Handle(SDL_Event events, int& state)
{
        if(events.type == SDL_MOUSEBUTTONDOWN || events.type == SDL_MOUSEMOTION)
        {
                for(int i = 0; i < TOTAL_BUTTONS; i++)
                {
                        MouseOver[i] = 0;
                }
                int x, y;
                SDL_GetMouseState(&x, &y);
                for(int i = 0; i < TOTAL_BUTTONS; i++)
                {
                        bool inside = false;
                        if(ButtonBox[i].x < x && x < ButtonBox[i].x + BUTTON_WIDTH && ButtonBox[i].y < y && y < ButtonBox[i].y + BUTTON_HEIGHT)
                        {
                                inside = true;
                        }
                        if(inside)
                        {
                                switch(events.type)
                                {
                                case SDL_MOUSEBUTTONDOWN:
                                        if(i == PLAY)
                                        {
                                                state = PLAY_STATE;
                                        }
                                        if(i == QUIT)
                                        {
                                                state = QUIT_STATE;
                                        }
                                        if(i == GUIDE)
                                        {
                                                state = GUIDE_STATE;
                                        }
                                        break;
                                case SDL_MOUSEMOTION:
                                        MouseOver[i] = 1;
                                        break;
                                default:
                                        break;
                                }
                        }
                }
        }
}

void Menu::Render(SDL_Renderer* screen, SDL_Texture* mBGMenuTexture, SDL_Texture* mButtonTexture)
{
//        if(mBGMenuTexture == NULL || mButtonTexture == NULL) cout << "fuck you\n";
        SDL_Rect current_clip1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect renderQuad1 = {0, 0, SCREEN_WIDTH , SCREEN_HEIGHT};
        SDL_RenderCopyEx(screen, mBGMenuTexture, &current_clip1, &renderQuad1, 0.0, NULL, SDL_FLIP_NONE);

        for(int i = 0; i < TOTAL_BUTTONS; i++)
        {
                SDL_Rect* current_clip2 = &ButtonClip[i][MouseOver[i]];
                SDL_Rect renderQuad2 = {ButtonBox[i].x, ButtonBox[i].y, BUTTON_WIDTH , BUTTON_HEIGHT};
                SDL_RenderCopyEx(screen, mButtonTexture, current_clip2, &renderQuad2, 0.0, NULL, SDL_FLIP_NONE);
        }
}

EndGameMenu::EndGameMenu()
{
        for(int i = 0; i < TOTAL_BUTTON; i++)
        {
                buttonBox[i] = {0, 160*i, Button_Width, Button_Height};
        }
        for(int i = 0; i < TOTAL_BUTTON; i++)
        {
                button_clip[i][0] = {0, 320*i, Button_Width, Button_Height};
                button_clip[i][1] = {160, 320*i, Button_Width, Button_Height};
                mouseOver[i] = 0;
        }
}

void EndGameMenu::Handle(SDL_Event events, int& state)
{
        if(events.type == SDL_MOUSEBUTTONDOWN || events.type == SDL_MOUSEMOTION)
        {
                for(int i = 0; i < TOTAL_BUTTON; i++)
                {
                        mouseOver[i] = 0;
                }
                int x, y;
                SDL_GetMouseState(&x, &y);
                for(int i = 0; i < TOTAL_BUTTON; i++)
                {
                        bool inside = false;
                        if(buttonBox[i].x < x && x < buttonBox[i].x + Button_Width && buttonBox[i].y < y && y < buttonBox[i].y + Button_Height)
                        {
                                inside = true;
                        }
                        if(inside)
                        {
                                switch(events.type)
                                {
                                case SDL_MOUSEBUTTONDOWN:
                                        if(i == PLAY_AGAIN)
                                        {
                                                state = PLAY_STATE;
                                                restart = true;
                                        }
                                        if(i == HOME)
                                        {
                                                state = HOME_STATE;
                                        }
                                        break;
                                case SDL_MOUSEMOTION:
                                        mouseOver[i] = 1;
                                        break;
                                default:
                                        break;
                                }
                        }
                }
        }
}

void EndGameMenu::Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture)
{
//        if(mBGMenuTexture == NULL || mButtonTexture == NULL) cout << "fuck you\n";
        SDL_Rect current_clip1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect renderQuad1 = {0, 0, SCREEN_WIDTH , SCREEN_HEIGHT};
        SDL_RenderCopyEx(screen, BGTexture, &current_clip1, &renderQuad1, 0.0, NULL, SDL_FLIP_NONE);

        for(int i = 0; i < TOTAL_BUTTON; i++)
        {
                SDL_Rect* current_clip2 = &button_clip[i][mouseOver[i]];
                SDL_Rect renderQuad2 = {buttonBox[i].x, buttonBox[i].y, Button_Width , Button_Height};
                SDL_RenderCopyEx(screen, ButtonTexture, current_clip2, &renderQuad2, 0.0, NULL, SDL_FLIP_NONE);
        }
}
