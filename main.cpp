#include "Game.h"

int main(int argc, char* argv[])
{
        Game game;
        if(game.init() == false)
        {
                cout << "can not initialize\n";
                return -1;
        }
        else
        {
                if(game.LoadImage() == false)
                {
                        cout << "can not load image\n";
                        return -1;
                }
                else
                {
//                        cerr << "h\n";
                        bool quit = false;
                        while(!quit)
                        {
//                                cerr << "h\n";
                                while(SDL_PollEvent(&g_event) != 0)
                                {
//                                        cerr << "h\n";
                                        game.HandleEvents(g_event);
                                        if(g_event.type == SDL_QUIT)
                                        {
                                                quit = true;
                                        }
                                }
                                game.RenderGame();
                        }
                }
        }
        game.close();
        return 0;
}
