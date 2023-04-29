#ifndef BOMB_H
#define BOMB_H

#include "BaseObject.h"
#include "CommonFunc.h"

class Bomb : public BaseObject
{
public:
        Bomb(int x, int y);
        ~Bomb();
        void set_clips();
        void RenderBomb(SDL_Renderer* screen, SDL_Texture* BombTexture, SDL_Rect PlayerBox, int map_x, int map_y);
        bool getBombStatus() {return bomb;}
private:
        int bomb_x, bomb_y;
        const int BOMB_FRAMES = 14;
        int bomb_frame;
        SDL_Rect Bomb_clip[14];
        SDL_Rect BombBox;
        bool bomb, collide;
};

class BombList
{
public:
        BombList();
        ~BombList();

        void set_clips();
        void RenderBomb(SDL_Renderer* screen, SDL_Texture* BombTexture, SDL_Rect PlayerBox, int map_x, int map_y);
        bool getBombStatus();

private:
        const int TOTAL_BOMB = 100;
        vector<Bomb> bomblist;
};

#endif // BOMB_H
