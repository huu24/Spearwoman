#ifndef DEMON_H
#define DEMON_H

#include "CommonFunc.h"
#include "BaseObject.h"

class Skeleton : public BaseObject
{
public:
        Skeleton(float x, float y);
        ~Skeleton();

        void set_clips();
        void CollisionWithMap(Map& map_data);
        void Move(SDL_Rect PlayerBox ,SDL_Rect PlayerAttackBox, int map_x, int map_y, Map& map_data, bool PlayerIsDead, bool PlayerIsAttack);
        void Render(SDL_Renderer* screen, SDL_Texture* SkeTexture, SDL_Rect PlayerBox,  SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int map_x, int map_y);
        void RenderHP(SDL_Renderer* screen, SDL_Texture* SkeletonTexture, int map_x, int map_y);
        SDL_Rect GetSkeletonBox() {return SkeletonBox;}
        SDL_Rect GetSkeletonAttackBox() {return SkeletonAttackBox;}
        bool getAttackStatus() {return isAttacking;}
private:
        const float DemonSpeed = 0.25;
        const int IDLE_FRAMES = 4;
        const int WALK_FRAMES = 4;
        const int ATTACK_FRAMES = 8;
        const int TAKEHIT_FRAMES = 3;
        const int DEATH_FRAMES = 17;

        SDL_Rect Idle_clip[4];
        SDL_Rect Walk_clip[4];
        SDL_Rect Attack_clip[8];
        SDL_Rect TakeHit_clip[3];
        SDL_Rect Death_clip[17];
        SDL_Rect HP_clip[4];

        SDL_Rect SkeletonBox;
        SDL_Rect SkeletonAttackBox;

        int HP;
        float VelX, VelY;
        float x_pos, max_x, min_x, y_pos, max_y, min_y;
        int attack_frame, idle_frame, run_frame, takehit_frame, death_frame;
        bool isWalking, isAttacking, isDead, isIdling, isAttacked, attack;

        SDL_RendererFlip FlipType;
};

class SkeletonArmy
{
public:
        SkeletonArmy();
        ~SkeletonArmy();

        void set_clips();
        void Move(SDL_Rect PlayerBox ,SDL_Rect PlayerAttackBox, int camX, int camY, Map& map_data, bool PlayerIsDead, bool PlayerIsAttack);
        void Render(SDL_Renderer* screen, SDL_Texture* SkeTexture,  SDL_Rect PlayerBox,  SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int camX, int camY);
        void RenderHP(SDL_Renderer* screen, SDL_Texture* SkeletonTexture, int camX, int camY);
        bool getAttackStatus();
private:
        vector<Skeleton> skeleton;
};

#endif // DEMON_H
