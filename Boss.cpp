#include "Boss.h"

SharkAttack::SharkAttack()
{
        xpos = (MAX_MAP_X - 7) * TILE_SIZE;
        ypos = 500;
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
        //xpos += SharkSpeed;
        SharkBox.x = xpos;
        SharkBox.y = ypos;
}

void SharkAttack::RenderSharkAttack(SDL_Renderer* screen, SDL_Texture* mSharkTexture, int camX, int camY, int TimesBossIsAttacked)
{
        if(TimesBossIsAttacked == 0 || TimesBossIsAttacked % 3 != 0) return;
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
        x_pos = 245 * TILE_SIZE;
        y_pos = 100;
        VelX = VelY = 0;
        min_x_boss = 230*64;
        max_x_boss = 248*64;
        min_y_boss = 0;
        max_y_boss = 18*64;
        cntAttack = 0;
        isLeft = isRight = false;
        FlipType = SDL_FLIP_HORIZONTAL;
        isRunning = isAttacking = isAttacked = isTakinghit = isDead = causeDamage = false;
        isIdling = true;
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
        BossBox.w = 175;
        BossBox.h = 140;
}

void Boss::Move(SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, bool PlayerIsAttack)
{
        BossBox.x = x_pos;
        BossBox.y = y_pos;

        BossAttackBox.x = x_pos - BossAttackBox.w / 2 + 39;
        BossAttackBox.y = y_pos - BossAttackBox.h / 2 + 29;
        if(PlayerIsAttack)
        {
                if(BaseObject::CheckCollision(PlayerAttackBox, BossBox))
                {
                isTakinghit = true;
                cntAttack++;
                }
                else isTakinghit = false;
        }
        else
        {
                if(BaseObject::CheckCollision(PlayerBox, BossAttackBox))
                {
                        isAttacking = true;
                }
        }
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

void Boss::RenderBoss(SDL_Renderer* screen, SDL_Texture* mBossTexture, SDL_Rect PlayerBox, int camX, int camY)
{

        SDL_Rect* current_clip;
        int current_frame;

        if(isTakinghit)
        {
                current_frame = TAKEHIT_FRAMES;
                current_clip = &TakeHit_clip[takehit_frame / 60];
                BossBox.w = current_clip->w / 2;
                BossBox.h = current_clip->h / 2;
                takehit_frame++;
                if(takehit_frame >= current_frame * 60)
                {
                        takehit_frame = 0;
                        isTakinghit = false;
                }
                SDL_Rect RenderQuad = {BossBox.x - camX, BossBox.y - camY, BossBox.w, BossBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &RenderQuad);
        }
        else if(isAttacking)
        {
                current_frame = ATTACK_FRAMES;
                current_clip = &Attack_clip[attack_frame / 60];
//                BossAttackBox.x = x_pos - BossAttackBox.w / 2 + 39;
//                BossAttackBox.y = y_pos - BossAttackBox.h / 2 + 29;
//                BossAttackBox.w = current_clip->w / 2;
//                BossAttackBox.h = current_clip->h / 2;
                attack_frame++;
                if(attack_frame == 10 * 60 && BaseObject::CheckCollision(BossAttackBox, PlayerBox)) causeDamage = true;
                else
                        causeDamage = false;
                if(attack_frame >= current_frame * 60)
                {
                        isAttacking = false;
                        attack_frame = 0;
                }
                SDL_Rect RenderQuad = {BossAttackBox.x - camX, BossAttackBox.y - camY, BossAttackBox.w, BossAttackBox.h};
                SDL_RenderCopyEx(screen, mBossTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
//                SDL_RenderDrawRect(screen, &RenderQuad);
        }
        else if(isRunning)
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
//                SDL_RenderDrawRect(screen, &RenderQuad);
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

