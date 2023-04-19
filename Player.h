#ifndef PLAYER_H
#define PLAYER_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Skeleton.h"

class Player : public BaseObject
{
public:
        Player();
        ~Player();

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void set_clips();
        bool CheckCollision(SDL_Rect& a, SDL_Rect& b);
        void Handle(SDL_Event events);
        void Move(Map& map_data);
        void CollisionWithMap(Map& map_data);
        void RenderPlayer(SDL_Renderer* des, bool SkeletonIsAttacking);
        void RenderHP(SDL_Renderer* des);
        void SetMapXY(const int x, const int y) {map_x = x, map_y = y;}
        void SetCamera(Map& map_data);
        SDL_Rect GetPlayerBox() {return PlayerBox;}
        SDL_Rect GetPlayerAttackBox() {return PlayerAttackBox;}
        bool GetAttackStatus() {return isAttacking;}
        bool PlayerStatus() {return dead;}
        int Map_x() {return map_x;}
        int Map_y() {return map_y;}




private:
        const float PlayerSpeed = 0.4;
        const int IDLE_FRAMES = 8;
        const int WALK_FRAMES = 8;
        const int ATTACK1_FRAMES = 6;
        const int ATTACK2_FRAMES = 12;
        const int ATTACK3_FRAMES = 5;
        const int TAKEHIT_FRAMES = 4;
        const int DEATH_FRAMES = 8;
        int HP;

        float VelX, VelY;

        float x_pos;
        float y_pos;

        int width_frame;
        int height_frame;

        int map_x, map_y;

        SDL_Rect Idle_clip[8];
        SDL_Rect Walk_clip[8];
        SDL_Rect Attack1_clip[6];
        SDL_Rect Attack2_clip[14];
        SDL_Rect Attack3_clip[5];
        SDL_Rect Takehit_clip[4];
        SDL_Rect Death_clip[8];
        SDL_Rect HP_clip[6];

        Input input_type;
        int idle_frame, attack1_frame, attack2_frame, run_frame, takehit_frame, death_frame;
        bool isAttacking, dead, isAttacked;

        SDL_RendererFlip FlipType;
        SDL_Rect PlayerBox;
        SDL_Rect PlayerAttackBox;

};



#endif // PLAYER_H
