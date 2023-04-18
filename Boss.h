#ifndef BOSS_H
#define BOSS_H

#include "CommonFunc.h"
#include "BaseObject.h"

class Boss : public BaseObject
{
public:
        Boss();
        ~Boss();

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void set_clips();
        void Move();
        void Show(SDL_Renderer* des);
private:
        const float BossSpeed = 0.3;
        const int IDLE_FRAMES = 9;
        const int RUN_FRAMES = 6;
        const int ATTACK_FRAMES = 12;
        const int TAKEHIT_RRAMES = 5;
        const int DEATH_FRAMES = 9;
        float VelX, VelY;
        float x_pos, y_pos;
        float max_x_boss, max_y_boss;
        int cnt_idle;

        SDL_Rect BossBox;

        SDL_Rect Idle_clip[9];
        SDL_Rect Run_clip[6];
        SDL_Rect Attack_clip[12];
        SDL_Rect TakeHit_clip[5];
        SDL_Rect Death_clip[9];

        Input input_type;
        int frame;

        bool isRunning, isAttacking, isIdling;
        bool isLeft, isRight;

        SDL_RendererFlip FlipType;
};

#endif // BOSS_H

