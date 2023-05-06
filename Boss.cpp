#include "Boss.h"

SharkAttack::SharkAttack()
{
        xpos = (MAX_MAP_X - 7) * TILE_SIZE;
        ypos = 500;

        xpos = 0;
        ypos = 0;
        minY = 64;
        maxY = 18 * 64 - 160;
        cout << ypos << '\n';
        frame = 0;
        FlipType = SDL_FLIP_NONE;
}

SharkAttack::~SharkAttack()
{

}

void SharkAttack::set_clips()
{
        int x = 0;
        for(int i = 0; i < SHARK_FRAMES; i++)
        {
                Shark_clip[i] = {x, 0, 448, 160};
                x += 448;
        }
        x = 0;
}

void SharkAttack::Move()
{
//        cout << rand() % (maxY - minY + 1) + minY << '\n';
        //xpos += SharkSpeed;
        SharkBox.x = xpos;
        SharkBox.y = ypos;
}

void SharkAttack::RenderSharkAttack(SDL_Renderer* screen, SDL_Texture* mSharkTexture, int camX, int camY, int TimesBossIsAttacked)
{
//        if(TimesBossIsAttacked == 0 || TimesBossIsAttacked % 3 != 0) return;
        SDL_Rect* current_clip = &Shark_clip[frame / 60];
        SharkBox.w = current_clip->w;
        SharkBox.h = current_clip->h;
        frame++;
        if(frame >= SHARK_FRAMES * 60)
                frame = 0;
        SDL_Rect renderQuad = {SharkBox.x - camX, SharkBox.y - camY, SharkBox.w, SharkBox.h};
        SDL_RenderCopyEx(screen, mSharkTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);
        SDL_RenderDrawRect(screen, &renderQuad);
}

Boss::Boss()
{
        idle_frame = run_frame = attack_frame = takehit_frame = death_frame = 0;
        x_pos = 240 * TILE_SIZE;
        y_pos = 500;
        VelX = VelY = 0;
        min_x_boss = 230*64;
        max_x_boss = 248*64;
        min_y_boss = 0;
        max_y_boss = 18*64;
        HP = 2;
        FlipType = SDL_FLIP_HORIZONTAL;
        isRunning = isAttacking = isAttacked = isTakinghit = isDead = causeDamage = cantAttacked = renderHP = false;
        isIdling = true;
        BossBox.x = x_pos;
        BossBox.y = y_pos;
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
        BossAttackBox.w = 270;
        BossAttackBox.h = 300;
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
        HpBox = {0, 1840, 200, 16};
        BossBox.w = 175;
        BossBox.h = 140;
}

void Boss::Move(SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, bool PlayerIsAttack)
{
        if(PlayerBox.x + PlayerBox.w < min_x_boss || PlayerBox.y > max_y_boss)
        {
                isRunning = false;
                return;
        }
        renderHP = true;
        BossBox.x = x_pos;
        BossBox.y = y_pos;

        if(FlipType == SDL_FLIP_HORIZONTAL)
        {
                BossAttackBox.x = x_pos - BossAttackBox.w / 2 + 39;
                BossAttackBox.y = y_pos - BossAttackBox.h / 2 + 29;
        }
        else
        {
                BossAttackBox.x = x_pos;
                BossAttackBox.y = y_pos - BossAttackBox.h / 2 + 29;
        }

        if(PlayerIsAttack)
        {
                if(BaseObject::CheckCollision(PlayerAttackBox, BossBox) && !cantAttacked)
                {
                isTakinghit = true;
                --HP;
                }
        }
        else
        {
                if(BaseObject::CheckCollision(PlayerBox, BossAttackBox))
                {
                        isAttacking = true;
                }
        }

        if(x_pos > PlayerBox.x + PlayerBox.w)
        {
                FlipType = SDL_FLIP_HORIZONTAL;
                VelX = -BossSpeed;
                isRunning = true;
        }
        else if(x_pos + BossBox.w < PlayerBox.x)
        {
                FlipType = SDL_FLIP_NONE;
                VelX = BossSpeed;
                isRunning = true;
        }
        else
        {
                VelX = 0;
        }
        if(y_pos + BossBox.h > PlayerBox.y + PlayerBox.h)
        {
                VelY = -BossSpeed;
                isRunning = true;
        }
        else if(y_pos + BossBox.h < PlayerBox.y + PlayerBox.h)
        {
                VelY = BossSpeed;
                isRunning = true;
        }
        else
        {
                VelY = 0;
        }
        if(isAttacking || isTakinghit) return;
        if(VelX == 0 && VelY == 0) isRunning = false;

        x_pos += VelX;
        y_pos += VelY;

        if(x_pos + BossBox.w >= max_x_boss)
        {
                isRunning = false;
                x_pos = max_x_boss - BossBox.w;
        }
        else if(x_pos <= min_x_boss)
        {
                isRunning = false;
                x_pos = min_x_boss;
        }
        if(y_pos + BossBox.h >= max_y_boss)
        {
                isRunning = false;
                y_pos = max_y_boss - BossBox.h;
        }
        else if(y_pos <= min_y_boss)
        {
                isRunning = false;
                y_pos = min_y_boss;
        }
}

void Boss::RenderBoss(SDL_Renderer* screen, SDL_Texture* mBossTexture, SDL_Rect PlayerBox, int camX, int camY, Mix_Chunk *sound[])
{
        SDL_Rect* current_clip;
        int current_frame;

        if(HP <= 0)
        {
                current_frame = DEATH_FRAMES;
                current_clip = &Death_clip[death_frame / 10];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                death_frame++;
                if(death_frame >= current_frame * 10)
                {
                        death_frame = current_frame * 10 - 10;
                        isDead = true;
                }
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isTakinghit)
        {
                current_frame = TAKEHIT_FRAMES;
                current_clip = &TakeHit_clip[takehit_frame / 10];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                takehit_frame++;
                if(takehit_frame == 1)
                {
                        Mix_PlayChannel(12, sound[TakeHit_Sound], 0);
                }
                if(takehit_frame >= current_frame * 10)
                {
                        takehit_frame = 0;
                        isTakinghit = false;
                }
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isAttacking)
        {
                current_frame = ATTACK_FRAMES;
                current_clip = &Attack_clip[attack_frame / 12];
                attack_frame++;
                if(attack_frame >= 2* 12 && attack_frame <= ATTACK_FRAMES * 12) cantAttacked = true;
                else cantAttacked = false;
                if(attack_frame == 9 * 12)
                {
                        Mix_PlayChannel(13, sound[Attack_Sound], 0);
                }
                if(attack_frame == 9 * 12 && BaseObject::CheckCollision(BossAttackBox, PlayerBox)) causeDamage = true;
                else
                        causeDamage = false;
                if(attack_frame >= current_frame * 12)
                {
                        isAttacking = false;
                        attack_frame = 0;
                }
                SDL_Rect RenderQuad = {BossAttackBox.x - camX, BossAttackBox.y - camY, BossAttackBox.w, BossAttackBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isRunning)
        {
                current_frame = RUN_FRAMES;
                current_clip = &Run_clip[run_frame / 20];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
//                if(run_frame == 0 || run_frame == 3 * 20)
//                {
//                        Mix_PlayChannel(-1, sound[Walk_Sound], 0);
//                }
                run_frame++;
                if(run_frame >= current_frame * 20) run_frame = 0;
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isIdling)
        {
                current_frame = IDLE_FRAMES;
                current_clip = &Idle_clip[idle_frame / 10];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                idle_frame++;
                if(idle_frame >= current_frame * 10) idle_frame = 0;
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }

}
void Boss::RenderHP(SDL_Renderer* screen, SDL_Texture* mBossTexture, int camX, int camY)
{
        if(!renderHP || HP == 0) return;
        SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY - 35, HP * 10, HpBox.h};
        SDL_RenderCopyEx(screen, mBossTexture, &HpBox, &RenderQuad, 0.0, NULL, SDL_FLIP_HORIZONTAL);

}

