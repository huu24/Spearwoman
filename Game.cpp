#include "Game.h"

bool Game::init()
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
                        cout << "can not create renderer\n";
                           success = false;
                }
                else
                {
                        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                        int imgFlags = IMG_INIT_PNG;
                        if(!(IMG_Init(imgFlags) && imgFlags))
                        {
                                cout << "can not set render draw color\n";
                                success = false;
                        }
                }
        }
        return success;
}

bool Game::LoadImage()
{
        bool res = SkeletonTexture.LoadImg("image\\Game\\Skeleton-export.png", g_screen);
        if(res == false)
        {
                cout << "can not load Skeleton image!\n";
                return false;
        }
        bool res1 = BombTexture.LoadImg("image\\Game\\Bomb-export.png", g_screen);
        if(res1 == false)
        {
                cout << "can not load Bomb image!\n";
                return false;
        }
        bool res2 = PlayerTexture.LoadImg("image\\Game\\SpearWoman-export.png", g_screen);
        if(res2 == false)
        {
                cout << "can not load Player image!\n";
                return false;
        }
        bool res3 = Menu.LoadImg("image\\Game\\maki(1).png", g_screen);
        if(res3 == false)
        {
                cout << "can not load Menu image!\n";
                return false;
        }
        bool res4 = Button.LoadImg("image\\Game\\Button1.png", g_screen);
        if(res4 == false)
        {
                cout << "can not load Button image!\n";
                return false;
        }
        bool res5 = BossTexture.LoadImg("image\\Game\\Boss-export.png", g_screen);
        if(res5 == false)
        {
                cout << "can not load boss image!\n";
                return false;
        }
        bool res6 = SharkTexture.LoadImg("image\\Game\\SharkAttack.png", g_screen);
        if(res6 == false)
        {
                cout << "can not load shark image!\n";
                return false;
        }
        bool res7 = KeyTexture.LoadImg("image\\Game\\key-blue.png", g_screen);
        if(res7 == false)
        {
                cout << "can not load key image!\n";
                return false;
        }
        bool res8 = HPTexture.LoadImg("image\\Game\\HP.png", g_screen);
        if(res8 == false)
        {
                cout << "can not load hp image!\n";
                return false;
        }
        bool res9 = DoorTexture.LoadImg("image\\Game\\Door.png", g_screen);
        if(res9 == false)
        {
                cout << "can not load door image!\n";
                return false;
        }
        SetMap();
        SetPlayer();
        SetSkeleton();
        SetBoss();
        SetSharkAttack();
        SetBomb();
        SetKey();
        SetDoor();
        return true;
}

bool Game::SetMap()
{
        game_map.LoadFileMap("map\\map.txt");
        game_map.LoadTiles(g_screen);
        map_data = game_map.getMap();
        return true;
}

bool Game::SetPlayer()
{
        MyPlayer.set_clips();
        return true;
}

bool Game::SetSkeleton()
{
        skeleton.set_clips();
        return true;
}

bool Game::SetBoss()
{
        boss.set_clips();
        return true;
}

bool Game::SetSharkAttack()
{
        shark.set_clips();
        return true;
}

bool Game::SetBomb()
{
        bomb.set_clips();
        return true;
}

bool Game::SetKey()
{
        key.set_clips();
        return true;
}

bool Game::SetDoor()
{
        door.set_clips();
        return true;
}

void Game::HandleEvents(SDL_Event &g_event)
{
//        cerr << "h\n";
        MyPlayer.Handle(g_event);
}

void Game::RenderGame()
{
//        cerr << "h\n";
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        game_map.SetMap(map_data);
        game_map.RenderMap(g_screen);

        door.Check(MyPlayer.GetPlayerBox(), MyPlayer.GetKeys());
        door.RenderDoor(g_screen, DoorTexture.GetTexture(), MyPlayer.Map_x(), MyPlayer.Map_y());

        key.Check(MyPlayer.GetPlayerBox());
        key.RenderKey(g_screen, KeyTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Map_x(), MyPlayer.Map_y());

        hp.Check(MyPlayer.GetPlayerBox());
        hp.RenderHP(g_screen, HPTexture.GetTexture(), MyPlayer.Map_x(), MyPlayer.Map_y());

        MyPlayer.SetMapXY(map_data.current_x_pos, map_data.current_y_pos);
        MyPlayer.Move(map_data, hp.touchBloodJars(), key.touchKeys(), door.GetDoorBox(), door.DoorOpen());
        MyPlayer.RenderPlayer(g_screen, PlayerTexture.GetTexture(), skeleton.getAttackStatus(), bomb.getBombStatus(), boss.GetAttackStatus());
        MyPlayer.RenderHP(g_screen, PlayerTexture.GetTexture());

        skeleton.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.Map_x(), MyPlayer.Map_y(), map_data, MyPlayer.PlayerStatus(), MyPlayer.GetAttackStatus());
        skeleton.Render(g_screen, SkeletonTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus(), MyPlayer.PlayerStatus(), MyPlayer.Map_x(), MyPlayer.Map_y());
        skeleton.RenderHP(g_screen, SkeletonTexture.GetTexture(), MyPlayer.Map_x(), MyPlayer.Map_y());

        boss.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus());
        boss.RenderBoss(g_screen, BossTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Map_x(), MyPlayer.Map_y());
        boss.RenderHP(g_screen, BossTexture.GetTexture());

        shark.Move();
        shark.RenderSharkAttack(g_screen, SharkTexture.GetTexture(), MyPlayer.Map_x(), MyPlayer.Map_y(), boss.CountAttacks());

        bomb.RenderBomb(g_screen, BombTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Map_x(), MyPlayer.Map_y());

//        HPTexture.Render(g_screen, NULL);
//        Button.Render(g_screen, NULL);

        SDL_RenderPresent(g_screen);
}

void Game::close()
{
        SkeletonTexture.Free();
        BombTexture.Free();
        PlayerTexture.Free();

        SDL_DestroyRenderer(g_screen);
        g_screen = NULL;

        SDL_DestroyWindow(g_window);
        g_window = NULL;

        IMG_Quit();
        SDL_Quit();
}
