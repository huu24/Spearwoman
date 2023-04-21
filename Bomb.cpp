#include "Bomb.h"

Bomb::Bomb()
{
        bomb_x = 200;
        bomb_y = 200;
        bomb_frame = 0;
        bomb = false;
}

Bomb::~Bomb()
{

}

bool Bomb::LoadImg(string path, SDL_Renderer* screen)
{
        bool  res = BaseObject::LoadImg(path, screen);
        return res;
}

void Bomb::set_clips()
{
        int x = 0;
        for(int i = 0; i < BOMB_FRAMES; i++)
        {
                Bomb_clip[i] = {x, 0, 80, 64};
                x += 80;
        }
        x = 0;
        BombBox.x = bomb_x;
        BombBox.y = bomb_y;
        BombBox.w = 80;
        BombBox.h = 64;
}

bool Bomb::CheckCollision(SDL_Rect a, SDL_Rect b)
{
        int x, y, u, v;
        x = max(a.x, b.x);
        y = max(a.y, b.y);
        u = min(a.x + a.w, b.x + b.w);
        v = min(a.y + a.h, b.y + b.h);
        if (x < u && y < v) return true;
        return false;
}

void Bomb::RenderBomb(SDL_Renderer* screen, SDL_Rect PlayerBox, int map_x, int map_y)
{
        SDL_Rect tmp;
        tmp.x = PlayerBox.x;
        tmp.y = PlayerBox.y + PlayerBox.h - 5;
        tmp.w = PlayerBox.w;
        tmp.h = 5;
        if(CheckCollision(BombBox, tmp))
        {
                SDL_Rect* current_clip = &Bomb_clip[bomb_frame / 30];
                bomb_frame++;
                if(bomb_frame == 1) bomb = true;
                else bomb = false;
                if(bomb_frame >= BOMB_FRAMES * 30)
                        bomb_frame = BOMB_FRAMES * 30;
                SDL_Rect renderQuad = {BombBox.x - map_x - BombBox.w / 2, BombBox.y - map_y - BombBox.h / 2, Bomb_clip->w * 2, Bomb_clip->h * 2};
                SDL_RenderCopyEx(screen, p_object_, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }
}
