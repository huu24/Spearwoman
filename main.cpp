#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "Player.h"
#include "Skeleton.h"
#include "Bomb.h"
//#include "Boss.h"

BaseObject g_background;

bool init()
{
        int success = true;
        int res = SDL_Init(SDL_INIT_VIDEO);
        if(res < 0)
        {
                std::cout << "failed to initialize\n";
                return false;
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        g_window = SDL_CreateWindow("Hoang Cong Huu", SDL_WINDOWPOS_UNDEFINED,
                                                                                        SDL_WINDOWPOS_UNDEFINED,
                                                                                        SCREEN_WIDTH, SCREEN_HEIGHT,
                                                                                        SDL_WINDOW_SHOWN);
        if(g_window == NULL)
        {
                {
                        std::cout << "failed to create window\n";
                        success = false;
                }

        }
        else
        {
                g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
                if(g_screen == NULL)
                {
                           success = false;
                }
                else
                {
                        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                        int imgFlags = IMG_INIT_PNG;
                        if(!(IMG_Init(imgFlags) && imgFlags))
                        {
                                success = false;
                        }
                }
        }
        return success;
}

bool LoadBackground()
{
        bool res = g_background.LoadImg("image\\game\\Nebula Blue.png", g_screen);
        if(res == false)
                return false;
        return true;
}

void close()
{
        g_background.Free();

        SDL_DestroyRenderer(g_screen);
        g_screen = NULL;

        SDL_DestroyWindow(g_window);
        g_window = NULL;

        IMG_Quit();
        SDL_Quit();
}

int main(int argc, char* argv[])
{
        if(init() == false)
        {
                return -1;
        }

        if(LoadBackground() == false)
        {
                return -1;
        }

        GameMap game_map;
        game_map.LoadFileMap("map\\map.txt");
        game_map.LoadTiles(g_screen);

        Player MyPlayer;
        MyPlayer.LoadImg("image\\Game\\Spearwoman-export.png", g_screen);
        MyPlayer.set_clips();

//        Boss boss;
//        boss.LoadImg("image\\Game\\Boss-export.png", g_screen);
//        boss.set_clips();

        Demon Threat;
        Threat.LoadImg("image\\Game\\Skeleton.png", g_screen);
        Threat.set_clips();

        Bomb bomb;
        bomb.LoadImg("image\\Game\\Bomb.png", g_screen);
        bomb.set_clips();

        bool quit = false;
        while(!quit)
        {
                while(SDL_PollEvent(&g_event) != 0)
                {
                        if(g_event.type == SDL_QUIT)
                        {
                                quit = true;
                        }
                        MyPlayer.Handle(g_event);
                }
                SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(g_screen);

                g_background.Render(g_screen, NULL);


                Map map_data = game_map.getMap();

//                boss.Move();
//                boss.Show(g_screen);

                MyPlayer.SetMapXY(map_data.current_x_pos, map_data.current_y_pos);
                MyPlayer.Move(map_data);
                Threat.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.Map_x(), MyPlayer.Map_y());

                game_map.SetMap(map_data);
                game_map.RenderMap(g_screen);

                MyPlayer.RenderPlayer(g_screen, Threat.getAttackStatus(), bomb.getBombStatus());
                MyPlayer.RenderHP(g_screen);

                SDL_Rect a = MyPlayer.GetPlayerBox();
                bomb.RenderBomb(g_screen, a, MyPlayer.Map_x(), MyPlayer.Map_y());

                Threat.Render(g_screen, MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus(), MyPlayer.PlayerStatus(), MyPlayer.Map_x(), MyPlayer.Map_y());
                Threat.RenderHP(g_screen, MyPlayer.Map_x(), MyPlayer.Map_y());


                SDL_RenderPresent(g_screen);

        }
        close();
        return 0;
}
