#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "Player.h"
#include "Skeleton.h"
#include "Bomb.h"
//#include "Boss.h"

BaseObject SkeletonTexture;
BaseObject BombTexture;
BaseObject PlayerTexture;

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

bool LoadImage()
{
        bool res = SkeletonTexture.LoadImg("image\\game\\Skeleton.png", g_screen);
        if(res == false)
        {
                cout << "can not load Skeleton image!\n";
                return false;
        }
        bool res1 = BombTexture.LoadImg("image\\game\\Bomb.png", g_screen);
        if(res1 == false)
        {
                cout << "can not load Bomb image!\n";
                return false;
        }
        bool res2 = PlayerTexture.LoadImg("image\\game\\SpearWoman-export.png", g_screen);
        if(res2 == false)
        {
                cout << "can not load Player image!\n";
                return false;
        }
        return true;
}

void close()
{
        SkeletonTexture.Free();

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

        if(LoadImage() == false)
        {
                return -1;
        }

        GameMap game_map;
        game_map.LoadFileMap("map\\map.txt");
        game_map.LoadTiles(g_screen);

        Map map_data = game_map.getMap();

        Player MyPlayer;
        MyPlayer.set_clips();

//        Boss boss;
//        boss.LoadImg("image\\Game\\Boss-export.png", g_screen);
//        boss.set_clips();

        SkeletonArmy skeleton;
        skeleton.set_clips();

        BombList bomb;
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

//                boss.Move();
//                boss.Show(g_screen);

                MyPlayer.SetMapXY(map_data.current_x_pos, map_data.current_y_pos);
                MyPlayer.Move(map_data);
                skeleton.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.Map_x(), MyPlayer.Map_y(), map_data, MyPlayer.PlayerStatus(), MyPlayer.GetAttackStatus());

                game_map.SetMap(map_data);
                game_map.RenderMap(g_screen);

                MyPlayer.RenderPlayer(g_screen, PlayerTexture.GetTexture(), skeleton.getAttackStatus(), bomb.getBombStatus());
                MyPlayer.RenderHP(g_screen, PlayerTexture.GetTexture());

                bomb.RenderBomb(g_screen, BombTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Map_x(), MyPlayer.Map_y());

                skeleton.Render(g_screen, SkeletonTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus(), MyPlayer.PlayerStatus(), MyPlayer.Map_x(), MyPlayer.Map_y());
                skeleton.RenderHP(g_screen, MyPlayer.Map_x(), MyPlayer.Map_y());

                SDL_RenderPresent(g_screen);

        }
        close();
        return 0;
}
