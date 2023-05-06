#include "Game.h"

Game::Game()
{
        GameState = -1;
        GameState = MENU_STATE;
        running = true;
}

Game::~Game()
{

}

bool Game::init()
{
        bool success = 1;
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
                printf("Failed to init SDL, error: %s\n", SDL_GetError());
                success = 0;
        }
        else
        {
                g_window = SDL_CreateWindow("hoang cong huu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                if (g_window == NULL)
                {
                        printf("Failed to create window, error: %s\n", SDL_GetError());
                        success = 0;
                }
                else
                {
                        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
                        if (g_screen == NULL)
                        {
                                printf("Failed to render, error: %s\n", SDL_GetError());
                                success = 0;
                        }
                        else
                        {

                                SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_SetRenderDrawBlendMode(g_screen, SDL_BLENDMODE_BLEND);
                                int imgFlags = IMG_INIT_PNG;
                                if (!(IMG_Init(imgFlags) & imgFlags))
                                {
                                        printf("Failed to init SDL_image, error: %sn", IMG_GetError());
                                        success = 0;
                                }
                                if (TTF_Init() == -1)
                                {
                                        printf("Failed to init SDL_ttf, error: %s\n", TTF_GetError());
                                        success = 0;
                                }
                                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                                {
                                        printf("Failed to init SDL_mixer, error: %s\n", Mix_GetError());
                                        success = 0;
                                }
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
        bool res13 = BackGroundWin.LoadImg("image\\Game\\BackGroundWin.png", g_screen);
        if(res13 == false)
        {
                cout << "can not load back ground win!\n";
                return false;
        }
        bool res14 = BackGroundLose.LoadImg("image\\Game\\BackGroundLose.png", g_screen);
        if(res14 == false)
        {
                cout << "can not load back ground lose!\n";
                return false;
        }
        SetMap();
        return true;
}
bool Game::loadSound()
{
        bool success = true;

        // player sounds
        PlayerSound[ATTACK_SOUND] = Mix_LoadWAV("sounds/player/attack3.wav");
        if (PlayerSound[ATTACK_SOUND] == NULL)
        {
                printf("Failed to load player attack sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        PlayerSound[TAKE_HIT_SOUND] = Mix_LoadWAV("sounds/player/damaged3.wav");
        if (PlayerSound[TAKE_HIT_SOUND] == NULL)
        {
                printf("Failed to load player take hit sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        PlayerSound[WALK_SOUND] = Mix_LoadWAV("sounds/player/walk2.wav");
        if (PlayerSound[WALK_SOUND] == NULL)
        {
                printf("Failed to load player walk sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        PlayerSound[HEALING_SOUND] = Mix_LoadWAV("sounds/player/healed3.wav");
        if (PlayerSound[HEALING_SOUND] == NULL)
        {
                printf("Failed to load player healing effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        PlayerSound[DEATH_SOUND] = Mix_LoadWAV("sounds/player/death.wav");
        if (PlayerSound[DEATH_SOUND] == NULL)
        {
                printf("Failed to load death sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        PlayerSound[PAUSE_SOUND] = Mix_LoadWAV("sounds/other/select-button.wav");
        if (PlayerSound[PAUSE_SOUND] == NULL)
        {
                printf("Failed to load player pause sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        PlayerSound[GET_KEY_SOUND] = Mix_LoadWAV("sounds/player/getkey.wav");
        if (PlayerSound[GET_KEY_SOUND] == NULL)
        {
                printf("Failed to load player get key sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        // skeleton
        SkeletonSound[ATTACK_SOUND_] = Mix_LoadWAV("sounds/skeleton/sword-hit.wav");
        if(SkeletonSound[ATTACK_SOUND_] == NULL)
        {
                 printf("Failed to load skeleton attack sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        SkeletonSound[WALK_SOUND_] = Mix_LoadWAV("sounds/skeleton/Skeletonwalk.wav");
        if(SkeletonSound[WALK_SOUND_] == NULL)
        {
                 printf("Failed to load skeleton walk sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        SkeletonSound[DEATH_SOUND_] = Mix_LoadWAV("sounds/skeleton/bone-crack.wav");
        if(SkeletonSound[DEATH_SOUND_] == NULL)
        {
                 printf("Failed to load skeleton death sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        SkeletonSound[BOOM_SOUND_] = Mix_LoadWAV("sounds/skeleton/boom1.wav");
        if(SkeletonSound[BOOM_SOUND_] == NULL)
        {
                 printf("Failed to load skeleton boom sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        //boss sound
        BossSound[Attack_Sound] = Mix_LoadWAV("sounds/boss/bossattack.wav");
        if (BossSound[Attack_Sound] == NULL)
        {
                printf("Failed to load boss attack sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        BossSound[Walk_Sound] = Mix_LoadWAV("sounds/boss/bosswalk.wav");
        if (BossSound[Walk_Sound] == NULL)
        {
                printf("Failed to load boss walk sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        BossSound[TakeHit_Sound] = Mix_LoadWAV("sounds/boss/bosstakehit.wav");
        if (BossSound[TakeHit_Sound] == NULL)
        {
                printf("Failed to load boss takehit sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        // other sound
        OtherSound[SELECT_BUTTON_SOUND] = Mix_LoadWAV("sounds/other/select-button.wav");
        if (OtherSound[SELECT_BUTTON_SOUND] == NULL)
        {
                printf("Failed to load select button sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }
        OtherSound[BOOM_SOUND] = Mix_LoadWAV("sounds/other/boom1.wav");
        if (OtherSound[BOOM_SOUND] == NULL)
        {
                printf("Failed to load select button sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        GameSound = Mix_LoadMUS("sounds/menutheme.wav");
        if(GameSound == NULL)
        {
                printf("Failed to load menu sound! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
        }

        return success;
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
        if(Mix_PlayingMusic() == 0)
        {
                Mix_PlayMusic(GameSound, -1);
                Mix_VolumeMusic(32);
        }
        if(g_event.type == SDL_QUIT)
                running = false;
        menu.Handle(g_event, GameState, OtherSound);
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
        pauseMenu.Handle(g_event, GameState, OtherSound);
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

void Game::HandleEndGameEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        egmenu.Handle(g_event, GameState, OtherSound);
        if(GameState == AGAIN_STATE)
        {
                GameState = PLAY_STATE;
                SetObject();
        }
}
void Game::RenderEndGameMenu()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        if(MyPlayer.PlayerStatus())
        {
                egmenu.Render(g_screen, BackGroundLose.GetTexture(), EGButtonTexture.GetTexture());
        }
        if(boss.BossIsDead())
        {
                egmenu.Render(g_screen, BackGroundWin.GetTexture(), EGButtonTexture.GetTexture());
        }

        SDL_RenderPresent(g_screen);
}

void Game::HandleGuideMenuEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        guide.Handle(g_event, GameState, OtherSound);
}
void Game::RenderGuideMenu()
{
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        guide.Render(g_screen, GuideTexture.GetTexture(), EGButtonTexture.GetTexture());
        SDL_RenderPresent(g_screen);
}

void Game::HandleGameEvents(SDL_Event &g_event)
{
        if(g_event.type == SDL_QUIT)
                running = false;
        MyPlayer.Handle(g_event, GameState, PlayerSound);
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

        MyPlayer.Move(map_data, hp.touchBloodJars(), key.touchKeys(), door.GetDoorBox(), door.DoorOpen(), PlayerSound);
        MyPlayer.RenderPlayer(g_screen, PlayerTexture.GetTexture(), skeleton.getAttackStatus(), bomb.getBombStatus(), boss.GetAttackStatus(), PlayerSound);
        MyPlayer.RenderHP(g_screen, PlayerTexture.GetTexture());

        skeleton.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), map_data, MyPlayer.PlayerStatus(), MyPlayer.GetAttackStatus());
        skeleton.Render(g_screen, SkeletonTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus(), MyPlayer.PlayerStatus(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), SkeletonSound);
        skeleton.RenderHP(g_screen, SkeletonTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

        boss.Move(MyPlayer.GetPlayerBox(), MyPlayer.GetPlayerAttackBox(), MyPlayer.GetAttackStatus());
        boss.RenderBoss(g_screen, BossTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), BossSound);
        boss.RenderHP(g_screen, BossTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y());

//                shark.Move();
//                shark.RenderSharkAttack(g_screen, SharkTexture.GetTexture(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), boss.CountAttacks());

        bomb.RenderBomb(g_screen, BombTexture.GetTexture(), MyPlayer.GetPlayerBox(), MyPlayer.Cam_X(), MyPlayer.Cam_Y(), OtherSound);

        if(MyPlayer.PlayerStatus() || boss.BossIsDead())
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

        for (Mix_Chunk *mSound : OtherSound)
        {
                Mix_FreeChunk(mSound);
                mSound = NULL;
        }
        for (Mix_Chunk *mSound : PlayerSound)
        {
                Mix_FreeChunk(mSound);
                mSound = NULL;
        }
        for (Mix_Chunk *mSound : SkeletonSound)
        {
                Mix_FreeChunk(mSound);
                mSound = NULL;
        }
        for (Mix_Chunk *mSound : BossSound)
        {
                Mix_FreeChunk(mSound);
                mSound = NULL;
        }

                Mix_Quit();
                IMG_Quit();
                SDL_Quit();
}
