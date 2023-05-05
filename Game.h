#ifndef GAME_H
#define GAME_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "game_map.h"
#include "Player.h"
#include "Skeleton.h"
#include "Bomb.h"
#include "Boss.h"
#include "Item.h"
#include "Menu.h"
#include "Timer.h"

class Game
{
public:
        Game();
        ~Game();
        bool init();
        bool LoadImage();
        bool loadSound();
        bool SetMap();
        bool SetPlayer();
        bool SetSkeleton();
        bool SetBoss();
        bool SetSharkAttack();
        bool SetBomb();
        bool SetKey();
        bool SetHP();
        bool SetDoor();
        bool SetObject();
        bool isRunning() {return running;};
        int GetState() {return GameState;};
        void HandleGameEvents(SDL_Event &g_event);
        void HandleMenuEvents(SDL_Event &g_event);
        void HandlePauseMenuEvents(SDL_Event &g_event);
        void HandleGameOverEvents(SDL_Event &g_event);
        void HandleGuideMenuEvents(SDL_Event &g_event);
        void RenderGame();
        void RenderMenu();
        void RenderPauseMenu();
        void RenderGameOverMenu();
        void RenderGuideMenu();
        void close();

private:
        BaseObject SkeletonTexture;
        BaseObject BombTexture;
        BaseObject PlayerTexture;
        BaseObject BossTexture;
        BaseObject SharkTexture;
        BaseObject BGMenuTexture;
        BaseObject ButtonTexture;
        BaseObject KeyTexture;
        BaseObject HPTexture;
        BaseObject DoorTexture;
        BaseObject GuideTexture;
        BaseObject EGBGTexture;
        BaseObject EGButtonTexture;
        BaseObject BackButtonTexture;
        GameMap game_map;
        Map map_data;
        Player MyPlayer;
        Boss boss;
//        SharkAttack shark;
        SkeletonArmy skeleton;
        BombList bomb;
        AllKeys key;
        AllHps hp;
        Door door;
        Menu menu;
        EndGameMenu egmenu;
        PauseMenu pauseMenu;
        Guide guide;

        Mix_Chunk *MenuSound[TOTAL_MENU_SOUND_EFFECT];
        Mix_Chunk *PlayerSound[TOTAL_PLAYER_SOUND_EFFECT];

        int GameState;
        bool InMenu;
        bool InGame;
        bool InGuide;
        bool inEndGameMenu;
        bool running;
};



#endif // GAME_H
