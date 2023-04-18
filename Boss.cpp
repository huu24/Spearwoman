#include "Boss.h"

Boss::Boss()
{
        x_pos = y_pos = 0;
        VelX = VelY = 0;
        max_x_boss = x_pos + 100;
        cnt_idle = 0;
        isLeft = isRight = false;
        input_type.attack1 = 0;
        FlipType = SDL_FLIP_NONE;
        isRunning = isAttacking = isIdling = false;
}
Boss::~Boss()
{

}
bool Boss::LoadImg(std::string path, SDL_Renderer* screen)
{
        bool res = BaseObject::LoadImg(path, screen);
        return res;
}

void Boss::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0 , 48*4, 30*4};
                x += 48*4;
        }
        x = 0;
        for(int i = 0; i < RUN_FRAMES; i++)
        {
                Run_clip[i] = {x, 30*4, 48*4, 28*4};
                x += 48*4;
        }
        x = 0;
        for(int i = 0; i < ATTACK_FRAMES; i++)
        {
                Attack_clip[i] = {x, 58*4, 64*4, 60*4};
                x += 48*4;
        }
        x = 0;
        for(int i = 0; i < TAKEHIT_RRAMES; i++)
        {
                TakeHit_clip[i] = {x, 119*4, 32*4, 32*4};
                x += 32*4;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 152*4, 32*4, 32*4};
                x += 32*4;
        }
        x = 0;
}

void Boss::Move()
{
        if(x_pos <= 0)
        {
                VelX = 0;
                cnt_idle++;
                isIdling = true, isRunning = false;
                if(cnt_idle >= 200)
                {
                        isRunning = true, isIdling = false;
                        FlipType = SDL_FLIP_NONE;
                        VelX = BossSpeed;
                        cnt_idle = 0;
                }
        }
        else if(x_pos >= max_x_boss)
        {
                VelX = 0;
                cnt_idle++;
                isIdling = true, isRunning = false;
                if(cnt_idle >= 200)
                {
                        isRunning = true, isIdling = false;
                        FlipType = SDL_FLIP_HORIZONTAL;
                        VelX = -BossSpeed;
                        cnt_idle = 0;
                }
        }
        x_pos += VelX;
}

void Boss::Show(SDL_Renderer* des)
{
        SDL_Rect* current_clip;
        int current_frame;
        BossBox.x = x_pos;
        BossBox.y = y_pos;

        if(isRunning)
        {
                current_frame = RUN_FRAMES;
                current_clip = &Run_clip[frame / 32];
                BossBox.w = current_clip->w;
                BossBox.h = current_clip->h;
                frame++;
                if(frame >= current_frame * 32) frame = 0;
                SDL_Rect RenderQuad = {BossBox.x, BossBox.y, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isIdling)
        {
                current_frame = IDLE_FRAMES;
                current_clip = &Idle_clip[frame / 48];
                BossBox.w = current_clip->w;
                BossBox.h = current_clip->h;
                frame++;
                if(frame >= current_frame * 48) frame = 0;
                SDL_Rect RenderQuad = {BossBox.x, BossBox.y, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isAttacking)
        {
                current_frame = ATTACK_FRAMES;
                current_clip = &Attack_clip[frame / 48];
                BossBox.w = current_clip->w;
                BossBox.h = current_clip->h;
                frame++;
                if(frame >= current_frame * 48)
                {
                        isAttacking = false;
                        frame = 0;
                }
                SDL_Rect RenderQuad = {BossBox.x, BossBox.y, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
}

