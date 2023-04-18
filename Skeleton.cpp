#include "Skeleton.h"

Demon::Demon()
{
        HP = 3;
        x_pos = 200, y_pos = 200;
        max_x = x_pos + 150;
        min_x = x_pos - 150;
        max_y = y_pos + 150;
        min_y = y_pos - 150;
        VelX = 0, VelY = 0;
        idle_frame = run_frame = attack_frame = takehit_frame = death_frame = 0;
        width_frame = 0;
        height_frame = 0;
        input_type.attack1 = 0;
        FlipType = SDL_FLIP_HORIZONTAL;
        isWalking = isAttacking = isDead = false;
        isIdling = true;
}
Demon::~Demon()
{

}

bool Demon::LoadImg(std::string path, SDL_Renderer* screen)
{
        bool res = BaseObject::LoadImg(path, screen);
        return res;
}

void Demon::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0 , 48, 51};
                x += 48;
        }
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
        SkeletonAttackBox.w = 96;
        SkeletonAttackBox.h = 57;
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
        x = std::max(a.x, b.x);
        y = std::max(a.y, b.y);
        u = std::min(a.x + a.w, b.x + b.w);
        v = std::min(a.y + a.h, b.y + b.h);
        if (x < u && y < v)
                return true;
        return false;
}

void Demon::Move(SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox)
{
        if(isDead || isAttacked || isAttacking || PlayerBox.x <= min_x || PlayerBox.x >= max_x || PlayerBox.y >= max_y || PlayerBox.y <= min_y)
        {
                isWalking = false;
                return;
        }

        if(SkeletonBox.x <= min_x)
        {
                VelX = DemonSpeed;
        }
        else if(SkeletonBox.x >= max_x)
        {
                VelX = -DemonSpeed;
                FlipType = SDL_FLIP_HORIZONTAL;
        }
        else
        {
                if(FlipType == SDL_FLIP_NONE)
                {
                        if(SkeletonBox.x  + SkeletonBox.w <= PlayerBox.x) VelX = DemonSpeed;
                        isWalking = true;
                }
                else
                {
                        if(SkeletonBox.x >= PlayerBox.x + PlayerBox.w) VelX = -DemonSpeed;
                        isWalking = true;
                }
                if(CheckCollision(SkeletonBox, PlayerBox))
                {
                        VelX = 0;
                }

        }
        if(SkeletonBox.y < min_y || SkeletonBox.y > max_y)
        {
                VelY = -VelY;
        }
        else
        {
                if(SkeletonBox.y < PlayerBox.y) VelY = DemonSpeed;
                else if(SkeletonBox.y > PlayerBox.y) VelY = -DemonSpeed;
                else VelY = 0;
                isWalking = true;
        }

        x_pos += VelX;
        y_pos += VelY;

        //if(VelX  != 0 || VelY != 0) isWalking = true;

        if(PlayerBox.x > SkeletonBox.x)
        {
                if(FlipType == SDL_FLIP_HORIZONTAL) FlipType = SDL_FLIP_NONE;
        }
        else
        {
                if(FlipType == SDL_FLIP_NONE) FlipType = SDL_FLIP_HORIZONTAL;
        }
}

void Demon::Show(SDL_Renderer* des, SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int map_x, int map_y)
{
        SDL_Rect* current_clip;
        int current_frame;

        SkeletonBox.x = x_pos;
        SkeletonBox.y = y_pos;

        SkeletonAttackBox.x = x_pos;
        SkeletonAttackBox.y = y_pos;

        if(HP == 0)
        {
                isDead = true;
                current_clip = &Death_clip[death_frame / 40];
                current_frame = DEATH_FRAMES;
                death_frame++;
                if(death_frame >= current_frame * 40) death_frame = current_frame * 40;
                SkeletonBox.w = current_clip->w;
                SkeletonBox.h = current_clip->h;
                SDL_Rect RenderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y,SkeletonBox.w ,SkeletonBox.h };
                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(CheckCollision(SkeletonBox, PlayerAttackBox))
        {
                if(PlayerIsAttack)
                {
                        --HP;
                        isAttacked = true;
                }
                if(isAttacked)
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
                        SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                }
                else if(CheckCollision(SkeletonAttackBox, PlayerBox))
                {
                        if(PlayerIsDead)
                        {
                                current_clip = &Idle_clip[idle_frame / 40];
                                current_frame = IDLE_FRAMES;
                                idle_frame++;
                                if(idle_frame >= current_frame * 40) idle_frame = 0;
                                SkeletonBox.w = current_clip->w;
                                SkeletonBox.h = current_clip->h;
                                SDL_Rect RenderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y, SkeletonBox.w ,SkeletonBox.h };
                                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                        }
                        else
                        {
                                current_clip = &Attack_clip[attack_frame / 60];
                                current_frame = ATTACK_FRAMES;
                                attack_frame++;
                                if(attack_frame == (current_frame - 1) * 60) isAttacking = true;
                                else isAttacking = false;
                                if(attack_frame >= current_frame * 60)
                                {
                                        attack_frame = 0;
                                }
                                SkeletonBox.w = current_clip->w;
                                SkeletonBox.h = current_clip->h;

                                if(FlipType == SDL_FLIP_HORIZONTAL)
                                {
                                        SDL_Rect RenderQuad = {SkeletonBox.x - map_x - 38, SkeletonBox.y - map_y - 6, SkeletonBox.w, SkeletonBox.h };
                                        SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                                }
                                else
                                {
                                        SDL_Rect RenderQuad = {SkeletonBox.x - map_x - 7, SkeletonBox.y - map_y, SkeletonBox.w, SkeletonBox.h };
                                        SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                                }
                        }
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
                        SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                }
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
                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
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
                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
}

void Demon::RenderHP(SDL_Renderer* des, int map_x, int map_y)
{
        if(!isDead)
        {
                SDL_Rect* current_clip = &HP_clip[HP];
                SDL_Rect renderQuad = {SkeletonBox.x - map_x, SkeletonBox.y - map_y - 14, current_clip->w, current_clip->h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }
}
