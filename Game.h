#ifndef GAME_H
#define GAME_H

#include "BaseObject.h"
#include "CommonFunc.h"
#include "game_map.h"
#include "Player.h"
#include "Skeleton.h"
#include "Bomb.h"
#include "Boss.h"

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
        GameMap game_map;
        Map map_data;
        Player MyPlayer;
        Boss boss;
        SharkAttack shark;
        SkeletonArmy skeleton;
        BombList bomb;
};



#endif // GAME_H
