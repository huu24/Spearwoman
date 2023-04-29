#ifndef BOSS_H
#define BOSS_H

#include "CommonFunc.h"
#include "BaseObject.h"

class SharkAttack : public BaseObject
{
public:
        SharkAttack();
        ~SharkAttack();

        void set_clips();
        void Move();
        void RenderSharkAttack(SDL_Renderer* screen, SDL_Texture* mSharkTexture, int camX, int camY, int TimesBossIsAttacked);
private:
        const float SharkSpeed = 0.5;
        const int SHARK_FRAMES = 18;
        int frame;
        float xpos, ypos;

        SDL_Rect Shark_clip[18];
        SDL_Rect SharkBox;

        SDL_RendererFlip FlipType;
};

class Boss : public BaseObject
{
public:
        Boss();
        ~Boss();

        void set_clips();
        void Move(SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, bool PlayerIsAttack);
        void RenderBoss(SDL_Renderer* screen, SDL_Texture* mBossTexture, SDL_Rect PlayerBox, int camX, int camY);
        bool GetAttackStatus() {return causeDamage;}
        int CountAttacks() {return cntAttack;}
private:
        const float BossSpeed = 0.5;
        const int IDLE_FRAMES = 9;
        const int RUN_FRAMES = 6;
        const int ATTACK_FRAMES = 12;
        const int TAKEHIT_FRAMES = 5;
        const int DEATH_FRAMES = 9;
        float VelX, VelY;
        float x_pos, y_pos;
        float max_x_boss, max_y_boss, min_x_boss, min_y_boss;
        int cnt_idle, cntAttack;

        SDL_Rect BossBox;
        SDL_Rect BossAttackBox;

        SDL_Rect Idle_clip[9];
        SDL_Rect Run_clip[6];
        SDL_Rect Attack_clip[12];
        SDL_Rect TakeHit_clip[5];
        SDL_Rect Death_clip[9];

        int idle_frame, run_frame, attack_frame, takehit_frame, death_frame;
        bool isRunning, isAttacking, isIdling, isTakinghit, isAttacked, isDead, causeDamage;
        bool isLeft, isRight;

        SDL_RendererFlip FlipType;
};

#endif // BOSS_H

