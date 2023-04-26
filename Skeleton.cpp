#include "Skeleton.h"

Demon::Demon(float x, float y)
{
        HP = 3;
        x_pos = x, y_pos = y;
        max_x = x_pos + 300;
        min_x = x_pos - 300;
        max_y = y_pos + 300;
        min_y = y_pos - 300;
        VelX = 0, VelY = 0;
        idle_frame = run_frame = attack_frame = takehit_frame = death_frame = 0;
        input_type.attack1 = 0;
        FlipType = SDL_FLIP_HORIZONTAL;
        isWalking = isAttacking = isDead = isAttacked = attack = false;
        isIdling = true;
}
Demon::~Demon()
{

}

void Demon::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0 , 48, 51};
                x += 48;
        }
        SkeletonBox.h = 51;
        SkeletonBox.w = 48;
        x = 0;
        for(int i = 0; i < WALK_FRAMES; i++)
        {
                Walk_clip[i] = {x, 52, 48, 53};
                x += 48;
        }
        x = 0;
        for(int i = 0; i < ATTACK_FRAMES; i++)
        {
                Attack_clip[i] = {x, 102, 96, 57};
                x += 96;
        }
        x = 0;
        for(int i = 0; i < TAKEHIT_FRAMES; i++)
        {
                TakeHit_clip[i] = {x, 159, 48, 53};
                x += 48;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 212, 48, 60};
                x += 48;
        }
        x = 0;
        for(int i = 1; i <= 3; i++)
        {
                HP_clip[i] = {x, 263, 48, 6};
                x += 48;
        }
        x = 0;
}

bool Demon::CheckCollision(SDL_Rect a, SDL_Rect b)
{
        int x, y, u, v;
        x = max(a.x, b.x);
        y = max(a.y, b.y);
        u = min(a.x + a.w, b.x + b.w);
        v = min(a.y + a.h, b.y + b.h);
        if (x < u && y < v)
                return true;
        return false;
}

void Demon::CollisionWithMap(Map& map_data)
{
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check horizontal

        int min_height = min(TILE_SIZE, SkeletonBox.h);

        x1 = (x_pos) / TILE_SIZE;
        x2 = (x_pos + SkeletonBox.w) / TILE_SIZE;

        y1 = (y_pos + SkeletonBox.h - min_height) / TILE_SIZE;
        y2 = (y_pos + SkeletonBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelX > 0)
                {
                        if(map_data.TileType[y1][x2] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                x_pos -= VelX;
                        }
                }
                else if(VelX < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y2][x1] >= 4)
                        {
                                x_pos -= VelX;
                        }
                }
        }

        //check_vertical
        x1 = x_pos / TILE_SIZE;
        x2 = (x_pos + SkeletonBox.w) / TILE_SIZE;

        y1 = (y_pos + SkeletonBox.h - min_height) / TILE_SIZE;
        y2 = (y_pos + SkeletonBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelY > 0)
                {
                        if(map_data.TileType[y2][x1] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                y_pos -= VelY;
                        }
                }
                else if(VelY < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y1][x2] >= 4)
                        {
                                y_pos -= VelY;
                        }
                }
        }

        if(x_pos < 0)
        {
                x_pos = 0;
        }
        else if(x_pos + SkeletonBox.w > map_data.max_x_)
        {
                x_pos = map_data.max_x_ - SkeletonBox.w;
        }

        if(y_pos < 0)
        {
                y_pos = 0;
        }
        else if(y_pos + SkeletonBox.h > map_data.max_y_)
        {
                y_pos = map_data.max_y_ - SkeletonBox.h;
        }
}

void Demon::Move(SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, int map_x, int map_y, Map& map_data, bool PlayerIsDead, bool PlayerIsAttack)
{
        if(PlayerIsAttack)
        {
                if(CheckCollision(SkeletonBox, PlayerAttackBox))
                {
                        --HP;
                        isAttacked = true;
                }
        }
        else
        {
                if(!PlayerIsDead && CheckCollision(SkeletonBox, PlayerBox))
                {
                        attack = true;
                }
        }
        if(isDead || isAttacked || attack || PlayerBox.x <= min_x || PlayerBox.x >= max_x || PlayerBox.y >= max_y || PlayerBox.y <= min_y)
        {
                isWalking = false;
                return;
        }
        SkeletonBox.x = x_pos;
        SkeletonBox.y = y_pos;

        if(PlayerBox.x > SkeletonBox.x)
        {
                if(FlipType == SDL_FLIP_HORIZONTAL) FlipType = SDL_FLIP_NONE;
        }
        else
        {
                if(FlipType == SDL_FLIP_NONE) FlipType = SDL_FLIP_HORIZONTAL;
        }

        if(SkeletonBox.x <= min_x || SkeletonBox.x >= max_x)
        {
                VelX = 0;
        }
        else
        {
                if(FlipType == SDL_FLIP_NONE)
                {
                        if(SkeletonBox.x  + SkeletonBox.w <= PlayerBox.x)
                        {
                                VelX = DemonSpeed;
                        }
                        else VelX = 0;
                }
                else
                {
                        if(SkeletonBox.x >= PlayerBox.x + PlayerBox.w)
                        {
                                VelX = -DemonSpeed;
                        }
                        else VelX = 0;
                }
                if(CheckCollision(SkeletonBox, PlayerBox))
                {
                        VelX = 0;
                }
        }
        if(SkeletonBox.y <= min_y || SkeletonBox.y >= max_y)
        {
                VelY = 0;
        }
        else
        {
                if(SkeletonBox.y  + SkeletonBox.h < PlayerBox.y + PlayerBox.h)
                {
                        VelY = DemonSpeed;
                }
                else if(SkeletonBox.y  + SkeletonBox.h > PlayerBox.y + PlayerBox.h)
                {
                        VelY = - DemonSpeed;
                }
                else VelY = 0;

        }
        if(VelX == 0 && VelY == 0) isWalking = false;
        else isWalking = true;

        CollisionWithMap(map_data);

        x_pos += VelX;
        y_pos += VelY;
}

void Demon::Render(SDL_Renderer* screen, SDL_Texture* SkeTexture ,SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int map_x, int map_y)
{
        if(HP <= 0) isDead = true;

        SDL_Rect* current_clip;
        int current_frame;

        SkeletonBox.x = x_pos;
        SkeletonBox.y = y_pos;

        SkeletonAttackBox.x = x_pos;
        SkeletonAttackBox.y = y_pos;

        if(isDead)
        {
                current_clip = &Death_clip[death_frame / 40];
                current_frame = DEATH_FRAMES;
                death_frame++;
                if(death_frame >= current_frame * 40) death_frame = current_frame * 40;
                SkeletonBox.w = current_clip->w;
                SkeletonBox.h = current_clip->h;
                SDL_Rect RenderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y,SkeletonBox.w ,SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isAttacked)
        {
                current_clip = &TakeHit_clip[takehit_frame / 48];
                current_frame = TAKEHIT_FRAMES;
                takehit_frame++;
                if(takehit_frame >= current_frame * 48)
                {
                        takehit_frame = 0;
                        isAttacked = false;
                }
                if(HP <= 0) HP = 0;
                SkeletonBox.w = current_clip->w;
                SkeletonBox.h = current_clip->h;
                SDL_Rect RenderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y - 4,SkeletonBox.w ,SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(attack)
        {
                current_clip = &Attack_clip[attack_frame / 60];
                current_frame = ATTACK_FRAMES;
                attack_frame++;
                if(attack_frame == (current_frame - 1) * 60 && CheckCollision(PlayerBox, SkeletonAttackBox)) isAttacking = true;
                else isAttacking = false;
                if(attack_frame >= current_frame * 60)
                {
                        attack_frame = 0;
                        attack = false;
                }
                SkeletonAttackBox.x = x_pos + ((FlipType == SDL_FLIP_NONE) ? -7 : -38);
                SkeletonAttackBox.y = y_pos + ((FlipType == SDL_FLIP_NONE) ? 0 : -7);
                SkeletonAttackBox.w = current_clip->w;
                SkeletonAttackBox.h = current_clip->h;

                SDL_Rect RenderQuad = {SkeletonAttackBox.x - map_x, SkeletonAttackBox.y - map_y, SkeletonAttackBox.w, SkeletonAttackBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isWalking)
        {
                current_clip = &Walk_clip[run_frame / 60];
                current_frame = WALK_FRAMES;
                run_frame++;
                if(run_frame >= current_frame * 60) run_frame = 0;
                SkeletonBox.w = current_clip->w;
                SkeletonBox.h = current_clip->h;
                SDL_Rect RenderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y, SkeletonBox.w, SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else
        {
                current_clip = &Idle_clip[idle_frame / 40];
                current_frame = IDLE_FRAMES;
                idle_frame++;
                if(idle_frame >= current_frame * 40) idle_frame = 0;
                SkeletonBox.w = current_clip->w;
                SkeletonBox.h = current_clip->h;
                SDL_Rect RenderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y, SkeletonBox.w, SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
}

void Demon::RenderHP(SDL_Renderer* screen, int map_x, int map_y)
{
        if(!isDead)
        {
                SDL_Rect* current_clip = &HP_clip[HP];
                SDL_Rect renderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y - 14, current_clip->w, current_clip->h};
                SDL_RenderCopyEx(screen, BaseObject::GetTexture(), current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }
}

SkeletonArmy::SkeletonArmy()
{
        skeleton.push_back(Demon(300, 300));
        skeleton.push_back(Demon(500, 500));
        skeleton.push_back(Demon(900, 650));
        skeleton.push_back(Demon(700, 1000));
        skeleton.push_back(Demon(0, 900));
        skeleton.push_back(Demon(1500, 1500));
        skeleton.push_back(Demon(700, 1100));
        skeleton.push_back(Demon(800, 1100));
        skeleton.push_back(Demon(23*64, 14*64));
        skeleton.push_back(Demon(22*64, 16*64));
        skeleton.push_back(Demon(22*64, 16*64));
        skeleton.push_back(Demon(29*64, 8*64));
        skeleton.push_back(Demon(38*64, 4*64));
        skeleton.push_back(Demon(39*64, 10*64));
        skeleton.push_back(Demon(30*64, 17*64));
        skeleton.push_back(Demon(40*64, 17*64));
        skeleton.push_back(Demon(27*64, 6*64));
        skeleton.push_back(Demon(44*64, 9*64));
        skeleton.push_back(Demon(44*64, 10*64));
        skeleton.push_back(Demon(45*64, 7*64));
        skeleton.push_back(Demon(47*64, 7*64));
        skeleton.push_back(Demon(49*64, 7*64));
        skeleton.push_back(Demon(51*64, 7*64));
        skeleton.push_back(Demon(53*64, 7*64));
        skeleton.push_back(Demon(46*64, 11*64));
        skeleton.push_back(Demon(48*64, 12*64));
        skeleton.push_back(Demon(50*64, 11*64));
        skeleton.push_back(Demon(52*64, 12*64));
        skeleton.push_back(Demon(54*64, 11*64));
        skeleton.push_back(Demon(20*64, 1*64));
        skeleton.push_back(Demon(25*64, 3*64));
        skeleton.push_back(Demon(27*64, 2*64));
        skeleton.push_back(Demon(57*64, 14*64));
        skeleton.push_back(Demon(60*64, 16*64));
        skeleton.push_back(Demon(68*64, 13*64));
        skeleton.push_back(Demon(68*64, 18*64));
        skeleton.push_back(Demon(87*64, 1*64));
        skeleton.push_back(Demon(87*64, 2*64));
        skeleton.push_back(Demon(87*64, 3*64));
        skeleton.push_back(Demon(77*64, 7*64));
        skeleton.push_back(Demon(77*64, 9*64));
        skeleton.push_back(Demon(77*64, 11*64));
        skeleton.push_back(Demon(77*64, 13*64));
        skeleton.push_back(Demon(81*64, 7*64));
        skeleton.push_back(Demon(81*64, 9*64));
        skeleton.push_back(Demon(81*64, 11*64));
        skeleton.push_back(Demon(81*64, 13*64));
        skeleton.push_back(Demon(79*64, 10*64));
        skeleton.push_back(Demon(75*64, 17*64));
        skeleton.push_back(Demon(78*64, 17*64));
        skeleton.push_back(Demon(81*64, 17*64));
        skeleton.push_back(Demon(84*64, 17*64));
        skeleton.push_back(Demon(90*64, 5*64));
        skeleton.push_back(Demon(90*64, 15*64));
        skeleton.push_back(Demon(93*64, 10*64));
        skeleton.push_back(Demon(99*64, 10*64));
        skeleton.push_back(Demon(96*64, 7*64));
        skeleton.push_back(Demon(96*64, 13*64));

}

SkeletonArmy::~SkeletonArmy()
{

}

//bool SkeletonArmy::LoadImg(std::string path, SDL_Renderer* screen)
//{
//        for(int i = 0; i < skeleton.size(); i++)
//        {
//                skeleton[i].LoadImg(path, screen);
//        }
//}

void SkeletonArmy::set_clips()
{
        for(int i = 0; i < skeleton.size(); i++)
        {
                skeleton[i].set_clips();
        }
}

void SkeletonArmy::Move(SDL_Rect PlayerBox ,SDL_Rect PlayerAttackBox, int map_x, int map_y, Map& map_data, bool PlayerIsDead, bool PlayerIsAttack)
{
        for(int i = 0; i < skeleton.size(); i++)
        {
                skeleton[i].Move(PlayerBox, PlayerAttackBox, map_x, map_y, map_data, PlayerIsDead, PlayerIsAttack);
        }
}

void SkeletonArmy::Render(SDL_Renderer* screen, SDL_Texture* SkeTexture, SDL_Rect PlayerBox,  SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int map_x, int map_y)
{
        for(int i = 0; i < skeleton.size(); i++)
        {
                skeleton[i].Render(screen, SkeTexture,PlayerBox, PlayerAttackBox, PlayerIsAttack, PlayerIsDead, map_x, map_y);
        }
}
void SkeletonArmy::RenderHP(SDL_Renderer* screen, int map_x, int map_y)
{
        for(int i = 0; i < skeleton.size(); i++)
        {
                skeleton[i].RenderHP(screen, map_x, map_y);
        }
}

bool SkeletonArmy::getAttackStatus()
{
        for(int i = 0; i < skeleton.size(); i++)
        {
                if(skeleton[i].getAttackStatus()) return true;
        }
        return false;
}
