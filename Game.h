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

class Game
{
public:
        Game();
        ~Game();
        bool init();
        bool LoadImage();
        bool SetMap();
        bool SetPlayer();
        bool SetSkeleton();
        bool SetBoss();
        bool SetSharkAttack();
        bool SetBomb();
        bool SetKey();
        bool SetDoor();
        void HandleEvents(SDL_Event &g_event);
        void RenderGame();
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
        GameMap game_map;
        Map map_data;
        Player MyPlayer;
        Boss boss;
        SharkAttack shark;
        SkeletonArmy skeleton;
        BombList bomb;
        AllKeys key;
        AllHps hp;
        Door door;
        Menu menu;

        int GameState;
        bool InMenu;
        bool InGame;
};



#endif // GAME_H
