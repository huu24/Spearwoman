#include "Game.h"

int main(int argc, char* argv[])
{
        Game game;
        LTimer capTimer;

        if(game.init() == false)
        {
                cout << "can not initialize\n";
                return -1;
        }
        else
        {
                if(game.LoadImage() == false)
                {
                        cout << "can not load images\n";
                        return -1;
                }
                else if(game.loadSound() == false)
                {
                        cout << "can not load sounds\n";
                }
                else
                {
//                        cerr << "h\n";
                        while(game.isRunning() && game.GetState() != QUIT_STATE)
                        {
                                capTimer.start();
                                switch(game.GetState())
                                {
                                case MENU_STATE:
                                        while(SDL_PollEvent(&g_event))
                                                game.HandleMenuEvents(g_event);
                                        game.RenderMenu();
                                        break;
                                case PAUSE_MENU_STATE:
                                        while(SDL_PollEvent(&g_event))
                                                game.HandlePauseMenuEvents(g_event);
                                        game.RenderPauseMenu();
                                        break;
                                case GAME_OVER_MENU_STATE:
                                        while(SDL_PollEvent(&g_event))
                                                game.HandleEndGameEvents(g_event);
                                        game.RenderEndGameMenu();
                                        break;
                                case GUIDE_STATE:
                                        while(SDL_PollEvent(&g_event))
                                                game.HandleGuideMenuEvents(g_event);
                                        game.RenderGuideMenu();
                                        break;
                                case PLAY_STATE:
                                        while(SDL_PollEvent(&g_event))
                                                game.HandleGameEvents(g_event);
                                        game.RenderGame();
                                        break;
                                default:
                                        break;
                                }
                                int frameTicks = capTimer.getTicks();
                                if( frameTicks < SCREEN_TICKS_PER_FRAME )
                                {
                                    //Wait remaining time
                                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                                }
                        }
                }
        }
        game.close();
        return 0;
}
