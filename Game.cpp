#include "Game.h"

Game::Game()
{
        GameState = -1;
        InMenu = true;
        InGame = false;
        InGuide = false;
        inEndGameMenu = false;
        GameState = MENU_STATE;
        running = true;
}

Game::~Game()
{

}

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
        bool res3 = BGMenuTexture.LoadImg("image\\Game\\maki(1).png", g_screen);
        if(res3 == false)
        {
                cout << "can not load BGMenuTexture image!\n";
                return false;
        }
        bool res4 = ButtonTexture.LoadImg("image\\Game\\Button1.png", g_screen);
        if(res4 == false)
        {
                cout << "can not load ButtonTexture image!\n";
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
        bool res10 = GuideTexture.LoadImg("image\\Game\\Guide.png", g_screen);
        if(res10 == false)
        {
                cout << "can not load door image!\n";
                return false;
        }
        bool res11 = EGBGTexture.LoadImg("image\\Game\\SubMenuBG.png", g_screen);
        if(res11 == false)
        {
                cout << "can not load end game menu image!\n";
                return false;
        }
        bool res12 = EGButtonTexture.LoadImg("image\\Game\\button - Copy.png", g_screen);
        if(res12 == false)
        {
                cout << "can not load end game menu image!\n";
                return false;
        }
        bool res13 = BackButtonTexture.LoadImg("image\\Game\\backButton.png", g_screen);
        if(res13 == false)
        {
                cout << "can not load back button image!\n";
                return false;
        }
        SetMap();
        SetPlayer();
        SetSkeleton();
        SetBoss();
//        SetSharkAttack();
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
        MyPlayer = Player();
        MyPlayer.set_clips();
        return true;
}

bool Game::SetSkeleton()
{
        skeleton = SkeletonArmy();
        skeleton.set_clips();
        return true;
}

bool Game::SetBoss()
{
        boss = Boss();
        boss.set_clips();
        return true;
}

//bool Game::SetSharkAttack()
//{
//        shark.set_clips();
//        return true;
//}

bool Game::SetBomb()
{
        bomb = BombList();
        bomb.set_clips();
        return true;
}

bool Game::SetKey()
{
        key = AllKeys();
        key.set_clips();
        return true;
}

bool Game::SetHP()
{
        hp = AllHps();
        return true;
}
bool Game::SetDoor()
{
        door = Door();
        door.set_clips();
        return true;
}

bool Game::SetObject()
{
        if(!SetPlayer())
        {
                cout << "can not set player.\n";
                return false;
        }
        if(!SetSkeleton())
        {
                cout << "can not set skeleton.\n";
                return false;
        }
        if(!SetBoss())
        {
                cout << "can not set boss.\n";
                return false;
        }
//        bool SetSharkAttack();
        if(!SetBomb())
        {
                cout << "can not set bomb.\n";
                return false;
        }
        if(!SetKey())
        {
                cout << "can not set key.\n";
                return false;
        }
        if(!SetHP())
        {
                cout << "can not set blood jar.\n";
                return false;
        }
        if(!SetDoor())
        {
                cout << "can not set door\n";
                return false;
        }
        return true;
}

void Game::HandleMenuEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        menu.Handle(g_event, GameState);
        if(GameState == PLAY_STATE)
        {
                SetObject();
        }
}
void Game::RenderMenu()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        menu.Render(g_screen, BGMenuTexture.GetTexture(), ButtonTexture.GetTexture());
        SDL_RenderPresent(g_screen);
}

void Game::HandlePauseMenuEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        pauseMenu.Handle(g_event, GameState);
        if(GameState == AGAIN_STATE)
        {
                GameState = PLAY_STATE;
                SetObject();
        }
}
void Game::RenderPauseMenu()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        pauseMenu.Render(g_screen, EGBGTexture.GetTexture(), EGButtonTexture.GetTexture());
        SDL_RenderPresent(g_screen);
}

void Game::HandleGameOverEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        egmenu.Handle(g_event, GameState);
        if(GameState == AGAIN_STATE)
        {
                GameState = PLAY_STATE;
                SetObject();
        }
}
void Game::RenderGameOverMenu()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        egmenu.Render(g_screen, EGBGTexture.GetTexture(), EGButtonTexture.GetTexture());
        SDL_RenderPresent(g_screen);
}

void Game::HandleGuideMenuEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        guide.Handle(g_event, GameState);
}
void Game::RenderGuideMenu()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        guide.Render(g_screen, GuideTexture.GetTexture(), BackButtonTexture.GetTexture());
        SDL_RenderPresent(g_screen);
}

void Game::HandleGameEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        MyPlayer.Handle(g_event, GameState);
}

void Game::RenderGame()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);


                game_map.SetMap(map_data);
                game_map.RenderMap(g_screen);

                door.Check(MyPlayer.GetPlayerBox(), MyPlayer.GetKeys());
                door.RenderDoor(g_screen, DoorTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

                key.Check(MyPlayer.GetPlayerBox());
                key.RenderKey(g_screen, KeyTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

                hp.Check(MyPlayer.GetPlayerBox());
                hp.RenderHP(g_screen, HPTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

                MyPlayer.Move(map_data, hp.touchBloodJars(), key.touchKeys(), door.GetDoorBox(), door.DoorOpen());
                MyPlayer.RenderPlayer(g_screen, PlayerTexture.GetTexture(), skeleton.getAttackStatus(), bomb.getBombStatus(), boss.GetAttackStatus());
                MyPlayer.RenderHP(g_screen, PlayerTexture.GetTexture());

                skeleton.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), map_data, MyPlayer.PlayerStatus(), MyPlayer.GetAttackStatus());
                skeleton.Render(g_screen, SkeletonTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus(), MyPlayer.PlayerStatus(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());
                skeleton.RenderHP(g_screen, SkeletonTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

                boss.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus());
                boss.RenderBoss(g_screen, BossTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());
                boss.RenderHP(g_screen, BossTexture.GetTexture());

//                shark.Move();
//                shark.RenderSharkAttack(g_screen, SharkTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), boss.CountAttacks());

                bomb.RenderBomb(g_screen, BombTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

                if(MyPlayer.PlayerStatus())
                        GameState = GAME_OVER_MENU_STATE;

        SDL_RenderPresent(g_screen);
}

void Game::close()
{
        SkeletonTexture.Free();
        BombTexture.Free();
        PlayerTexture.Free();
        BossTexture.Free();
        SharkTexture.Free();
        BGMenuTexture.Free();
        ButtonTexture.Free();
        KeyTexture.Free();
        HPTexture.Free();
        DoorTexture.Free();
        GuideTexture.Free();
        EGBGTexture.Free();
        EGButtonTexture.Free();


        SDL_DestroyRenderer(g_screen);
        g_screen = NULL;

        SDL_DestroyWindow(g_window);
        g_window = NULL;

        IMG_Quit();
        SDL_Quit();
}
