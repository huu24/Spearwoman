#include "Menu.h"

Menu::Menu()
{
        int y = 6;
        for(int i = 0; i < TOTAL_BUTTONS; i++)
        {
                ButtonBox[i]= {0, y, 319, 73};
                y += 73;
        }
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

void Menu::Handle(SDL_Event events, int& state, Mix_Chunk *mSound[])
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
                                        Mix_PlayChannel(-1, mSound[SELECT_BUTTON_SOUND], 0);
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

//245

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
                buttonBox[i] = {480 + 160*i, 245, Button_Width, Button_Height};
        }
        for(int i = 0; i < TOTAL_BUTTON; i++)
        {
                button_clip[i][0] = {0, 320*i, Button_Width, Button_Height};
                button_clip[i][1] = {160, 320*i, Button_Width, Button_Height};
                mouseOver[i] = 0;
        }
}

void EndGameMenu::Handle(SDL_Event events, int& state, Mix_Chunk *eSound[])
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
                                        Mix_PlayChannel(-1, eSound[SELECT_BUTTON_SOUND], 0);
                                        if(i == PLAY_AGAIN)
                                        {
                                                state = AGAIN_STATE;
                                                restart = true;
                                        }
                                        if(i == HOME)
                                        {
                                                state = MENU_STATE;
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


PauseMenu::PauseMenu()
{
        for(int i = 0; i < Total_Button; i++)
        {
                buttonBox[i] = {398 + Button_Width*i, 245, Button_Width, Button_Height};
        }
        for(int i = 0; i < Total_Button; i++)
        {
                button_clip[i][0] = {0, 160*i, Button_Width, Button_Height};
                button_clip[i][1] = {160, 160*i, Button_Width, Button_Height};
                mouseOver[i] = 0;
        }
}

void PauseMenu::Handle(SDL_Event events, int& state, Mix_Chunk *pSound[])
{
        if(events.type == SDL_MOUSEBUTTONDOWN || events.type == SDL_MOUSEMOTION)
        {
                for(int i = 0; i < Total_Button; i++)
                {
                        mouseOver[i] = 0;
                }
                int x, y;
                SDL_GetMouseState(&x, &y);
                for(int i = 0; i < Total_Button; i++)
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
                                        Mix_PlayChannel(-1, pSound[SELECT_BUTTON_SOUND], 0);
                                        if(i == Play_Again)
                                        {
                                                state = AGAIN_STATE;
                                                restart = true;
                                        }
                                        if(i == Resume)
                                        {
                                                state = PLAY_STATE;
                                        }
                                        if(i == Home)
                                        {
                                                state = MENU_STATE;
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

void PauseMenu::Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture)
{
//        if(mBGMenuTexture == NULL || mButtonTexture == NULL) cout << "fuck you\n";
        SDL_Rect current_clip1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect renderQuad1 = {0, 0, SCREEN_WIDTH , SCREEN_HEIGHT};
        SDL_RenderCopyEx(screen, BGTexture, &current_clip1, &renderQuad1, 0.0, NULL, SDL_FLIP_NONE);

        for(int i = 0; i < Total_Button; i++)
        {
                SDL_Rect* current_clip2 = &button_clip[i][mouseOver[i]];
                SDL_Rect renderQuad2 = {buttonBox[i].x, buttonBox[i].y, Button_Width , Button_Height};
                SDL_RenderCopyEx(screen, ButtonTexture, current_clip2, &renderQuad2, 0.0, NULL, SDL_FLIP_NONE);
        }
}

Guide::Guide()
{
        backButtonBox = {10, 10, Button_Width, Button_Height};
        button_clip[0] = {0, 320, Button_Width * 2, Button_Height * 2};
        button_clip[1] = {160, 320, Button_Width * 2, Button_Height * 2};
        mouseOver = 0;
}

void Guide::Handle(SDL_Event events, int& state, Mix_Chunk *gSound[])
{
        if(events.type == SDL_MOUSEBUTTONDOWN || events.type == SDL_MOUSEMOTION)
        {
                mouseOver = 0;
                int x, y;
                SDL_GetMouseState(&x, &y);
                bool inside = false;
                if(backButtonBox.x < x && x < backButtonBox.x + Button_Width && backButtonBox.y < y && y < backButtonBox.y + Button_Height)
                {
                        inside = true;
                }
                if(inside)
                {
                        switch(events.type)
                        {
                        case SDL_MOUSEBUTTONDOWN:
                                Mix_PlayChannel(-1, gSound[SELECT_BUTTON_SOUND], 0);
                                state = MENU_STATE;
                                break;
                        case SDL_MOUSEMOTION:
                                        mouseOver = 1;
                                break;
                        default:
                                break;

                        }
                }
        }
}

void Guide::Render(SDL_Renderer* screen, SDL_Texture* BGTexture, SDL_Texture* ButtonTexture)
{
//        if(ButtonTexture != NULL) cout << "fuck you\n";
        SDL_Rect current_clip1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect renderQuad1 = {0, 0, SCREEN_WIDTH , SCREEN_HEIGHT};
        SDL_RenderCopyEx(screen, BGTexture, &current_clip1, &renderQuad1, 0.0, NULL, SDL_FLIP_NONE);

        SDL_Rect* current_clip2 = &button_clip[mouseOver];
        SDL_Rect renderQuad2 = {backButtonBox.x, backButtonBox.y, Button_Width , Button_Height};
        SDL_RenderCopyEx(screen, ButtonTexture, current_clip2, &renderQuad2, 0.0, NULL, SDL_FLIP_NONE);
}
