#include "Bomb.h"

Bomb::Bomb(int x, int y)
{
        bomb_x = x;
        bomb_y = y;
        bomb_frame = 0;
        bomb = collide = false;
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
                collide = true;
        }
        if(collide)
        {
                SDL_Rect* current_clip = &Bomb_clip[bomb_frame / 60];
                bomb_frame++;
                if(CheckCollision(PlayerBox, BombBox) && bomb_frame == 3 * 60)
                {
                        bomb = true;
                }
                else bomb = false;
                if(bomb_frame >= BOMB_FRAMES * 60)
                {
                        collide = false;
                }
                SDL_Rect renderQuad = {BombBox.x - map_x - BombBox.w / 2, BombBox.y - map_y - BombBox.h / 2, Bomb_clip->w * 2, Bomb_clip->h * 2};
                SDL_RenderCopyEx(screen, p_object_, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }
}

BombList::BombList()
{
        srand(time(NULL));
        int max_num_x = MAX_MAP_X * TILE_SIZE, max_num_y = MAX_MAP_Y * TILE_SIZE;
        for(int i = 0; i < TOTAL_BOMB; i++)
        {
                int bomb_x = rand() % max_num_x;
                int bomb_y = rand() % max_num_y;
                bomblist.push_back(Bomb(bomb_x, bomb_y));
        }
}
BombList::~BombList()
{

}

bool BombList::LoadImg(string path, SDL_Renderer* screen)
{
        for(int i = 0; i < bomblist.size(); i++)
        {
                bomblist[i].LoadImg(path, screen);
        }
}
void BombList::set_clips()
{
        for(int i = 0; i < bomblist.size(); i++)
        {
                bomblist[i].set_clips();
        }
}
void BombList::RenderBomb(SDL_Renderer* screen, SDL_Rect PlayerBox, int map_x, int map_y)
{
        for(int i = 0; i < bomblist.size(); i++)
        {
                bomblist[i].RenderBomb(screen, PlayerBox, map_x, map_y);
        }
}
bool BombList::getBombStatus()
{
        for(int i = 0; i < bomblist.size(); i++)
        {
                if(bomblist[i].getBombStatus()) return true;
        }
        return false;
}
