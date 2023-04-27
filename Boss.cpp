#include "Boss.h"

Boss::Boss()
{
        idle_frame = run_frame = attack_frame = takehit_frame = death_frame = 0;
        x_pos = 200;
        y_pos = 200;
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

void Boss::set_clips()
{
        int x = 130;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0 , 350, 300};
                x += 480;
        }
        x = 100;
        for(int i = 0; i < RUN_FRAMES; i++)
        {
                Run_clip[i] = {x, 300, 380, 280};
                x += 480;
        }
        x = 100;
        for(int i = 0; i < ATTACK_FRAMES; i++)
        {
                Attack_clip[i] = {x, 580, 540, 600};
                x += 640;
        }
        x = 0;
        for(int i = 0; i < TAKEHIT_FRAMES; i++)
        {
                TakeHit_clip[i] = {x, 1190, 320, 320};
                x += 320;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 1520, 320, 320};
                x += 320;
        }
        x = 0;
}

void Boss::Move()
{
        isDead = true;
//        if(x_pos <= 0)
//        {
//                VelX = 0;
//                cnt_idle++;
//                isIdling = true, isRunning = false;
//                if(cnt_idle >= 200)
//                {
//                        isRunning = true, isIdling = false;
//                        FlipType = SDL_FLIP_NONE;
//                        VelX = BossSpeed;
//                        cnt_idle = 0;
//                }
//        }
//        else if(x_pos >= max_x_boss)
//        {
//                VelX = 0;
//                cnt_idle++;
//                isIdling = true, isRunning = false;
//                if(cnt_idle >= 200)
//                {
//                        isRunning = true, isIdling = false;
//                        FlipType = SDL_FLIP_HORIZONTAL;
//                        VelX = -BossSpeed;
//                        cnt_idle = 0;
//                }
//        }
//        x_pos += VelX;
}

void Boss::RenderBoss(SDL_Renderer* screen, SDL_Texture* mBossTexture, int camX, int camY)
{

        SDL_Rect* current_clip;
        int current_frame;
        BossBox.x = x_pos;
        BossBox.y = y_pos;

        if(isRunning)
        {
                current_frame = RUN_FRAMES;
                current_clip = &Run_clip[run_frame / 60];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                run_frame++;
                if(run_frame >= current_frame * 60) run_frame = 0;
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &RenderQuad);
        }
        else if(isIdling)
        {
                current_frame = IDLE_FRAMES;
                current_clip = &Idle_clip[idle_frame / 60];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                idle_frame++;
                if(idle_frame >= current_frame * 60) idle_frame = 0;
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &RenderQuad);
        }
        else if(isAttacking)
        {
                current_frame = ATTACK_FRAMES;
                current_clip = &Attack_clip[attack_frame / 60];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                attack_frame++;
                if(attack_frame >= current_frame * 60)
                {
                        isAttacking = false;
                        attack_frame = 0;
                }
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &RenderQuad);
        }
        else if(isTakinghit)
        {
                current_frame = TAKEHIT_FRAMES;
                current_clip = &TakeHit_clip[takehit_frame / 60];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                takehit_frame++;
                if(takehit_frame >= current_frame * 60)
                {
                        takehit_frame = 0;
                }
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &RenderQuad);
        }
        else
        {
                current_frame = DEATH_FRAMES;
                current_clip = &Death_clip[death_frame / 60];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                death_frame++;
                if(death_frame >= current_frame * 60)
                {
                        death_frame = current_frame * 60 - 60;
                }
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &RenderQuad);
        }
}

