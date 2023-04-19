#ifndef DEMON_H
#define DEMON_H

#include "CommonFunc.h"
#include "BaseObject.h"

class Demon : public BaseObject
{
public:
        Demon();
        ~Demon();

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void set_clips();
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        void Move(SDL_Rect PlayerBox ,SDL_Rect PlayerAttackBox, int map_x, int map_y);
        void Show(SDL_Renderer* des, SDL_Rect PlayerBox,  SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int map_x, int map_y);
        void RenderHP(SDL_Renderer* des, int map_x, int map_y);
        SDL_Rect GetSkeletonBox() {return SkeletonBox;}
        SDL_Rect GetSkeletonAttackBox() {return SkeletonAttackBox;}
        bool getAttackStatus() {return isAttacking;}
private:
        const float DemonSpeed = 0.1;
        const int IDLE_FRAMES = 4;
        const int WALK_FRAMES = 4;
        const int ATTACK_FRAMES = 8;
        const int TAKEHIT_FRAMES = 3;
        const int DEATH_FRAMES = 4;
        int HP;
        int cntIdle;
        float VelX, VelY;
        float x_pos, max_x, min_x;
        float y_pos, max_y, min_y;

        int width_frame;
        int height_frame;

        SDL_Rect Idle_clip[4];
        SDL_Rect Walk_clip[4];
        SDL_Rect Attack_clip[8];
        SDL_Rect TakeHit_clip[3];
        SDL_Rect Death_clip[4];
        SDL_Rect HP_clip[4];

        Input input_type;
        int attack_frame, idle_frame, run_frame, takehit_frame, death_frame;

        bool isWalking, isAttacking, isDead, isIdling, isAttacked;

        SDL_RendererFlip FlipType;
        SDL_Rect SkeletonBox;
        SDL_Rect SkeletonAttackBox;
};

#endif // DEMON_H
