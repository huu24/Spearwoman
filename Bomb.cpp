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

void Bomb::set_clips()
{
        int x = 0;
        for(int i = 0; i < BOMB_FRAMES; i++)
        {
                Bomb_clip[i] = {x, 0, 80*2, 64*2};
                x += 80*2;
        }
        x = 0;
        BombBox.x = bomb_x;
        BombBox.y = bomb_y;
        BombBox.w = 80;
        BombBox.h = 64;
}

void Bomb::RenderBomb(SDL_Renderer* screen, SDL_Texture* BombTexture, SDL_Rect PlayerBox, int camX, int camY, Mix_Chunk *bombSound[])
{
        SDL_Rect tmp;
        tmp.x = PlayerBox.x;
        tmp.y = PlayerBox.y + PlayerBox.h - 5;
        tmp.w = PlayerBox.w;
        tmp.h = 5;
        if(BaseObject::CheckCollision(BombBox, tmp))
        {
                collide = true;
                Mix_PlayChannel(-1, bombSound[BOOM_SOUND], 0);
        }
        if(collide)
        {
                SDL_Rect* current_clip = &Bomb_clip[bomb_frame / 10];
                bomb_frame++;
                if(BaseObject::CheckCollision(PlayerBox, BombBox) && bomb_frame == 4 * 10)
                {
                        bomb = true;
                }
                else bomb = false;
                if(bomb_frame >= BOMB_FRAMES * 10)
                {
                        collide = false;
                        BombBox.h = 0;
                        BombBox.w = 0;
                        BombBox.x = 0;
                        BombBox.y = 0;
                }
                SDL_Rect renderQuad = {BombBox.x - camX - BombBox.w / 2, BombBox.y - camY - BombBox.h / 2, Bomb_clip->w, Bomb_clip->h};
                SDL_RenderCopyEx(screen, BombTexture, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
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
void BombList::set_clips()
{
        for(int i = 0; i < (int)bomblist.size(); i++)
        {
                bomblist[i].set_clips();
        }
}
void BombList::RenderBomb(SDL_Renderer* screen, SDL_Texture* BombTexture, SDL_Rect PlayerBox, int camX, int camY, Mix_Chunk *bombSound[])
{
        for(int i = 0; i < (int)bomblist.size(); i++)
        {
                bomblist[i].RenderBomb(screen, BombTexture, PlayerBox, camX, camY, bombSound);
        }
}
bool BombList::getBombStatus()
{
        for(int i = 0; i < (int)bomblist.size(); i++)
        {
                if(bomblist[i].getBombStatus()) return true;
        }
        return false;
}
