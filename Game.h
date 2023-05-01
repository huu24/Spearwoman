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

class Game
{
public:
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
        BaseObject Menu;
        BaseObject Button;
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
};



#endif // GAME_H
