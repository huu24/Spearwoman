#ifndef BOMB_H
#define BOMB_H

#include "BaseObject.h"
#include "CommonFunc.h"

class Bomb : public BaseObject
{
public:
        Bomb();
        ~Bomb();
        bool LoadImg(string path, SDL_Renderer* screen);
        void set_clips();
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        void RenderBomb(SDL_Renderer* screen, SDL_Rect PlayerBox, int map_x, int map_y);
        bool getBombStatus() {return bomb;}
private:
        float bomb_x, bomb_y;
        const int BOMB_FRAMES = 14;
        int bomb_frame;
        SDL_Rect Bomb_clip[14];
        SDL_Rect BombBox;
        bool bomb;
};

#endif // BOMB_H
