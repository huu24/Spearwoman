#ifndef PLAYER_H
#define PLAYER_H

#include "CommonFunc.h"
#include "BaseObject.h"


class Player : public BaseObject
{
public:
        Player();
        ~Player();

        void set_clips();
        void Handle(SDL_Event events, int& state, Mix_Chunk *playerSound[]);
        void Move(Map& map_data, bool touchHP, bool touchKey, SDL_Rect DoorBox, bool DoorOpen, Mix_Chunk *playerSound[]);
        void CollisionWithMap(Map& map_data);
        void SetCamera(Map& map_data);
        SDL_Rect GetPlayerBox() const {return PlayerBox;}
        SDL_Rect GetPlayerAttackBox() const {return PlayerAttackBox;}
        bool GetAttackStatus() const {return isAttacking;}
        bool PlayerStatus() const {return dead;}
        int Cam_X() const {return camX;}
        int Cam_Y() const {return camY;}
        int GetKeys() {return KEYS;}
        void RenderPlayer(SDL_Renderer* screen, SDL_Texture* mPlayerTexture, bool SkeletonIsAttacking, bool bomb, bool BossIsAttacking, Mix_Chunk *playerSound[]);
        void RenderHP(SDL_Renderer* screen, SDL_Texture* mPlayerTexture);

private:
        float PlayerSpeed = 3;
        int IDLE_FRAMES = 8;
        int WALK_FRAMES = 8;
        int ATTACK1_FRAMES = 6;
        int ATTACK2_FRAMES = 12;
        int ATTACK3_FRAMES = 5;
        int TAKEHIT_FRAMES = 4;
        int DEATH_FRAMES = 8;
        int KEY_FRAMES = 3;

        SDL_Rect Idle_clip[8];
        SDL_Rect Walk_clip[8];
        SDL_Rect Attack1_clip[6];
        SDL_Rect Attack2_clip[14];
        SDL_Rect Attack3_clip[5];
        SDL_Rect Takehit_clip[4];
        SDL_Rect Death_clip[8];
        SDL_Rect HP_clip[6];
        SDL_Rect Energy_clip[4];
        SDL_Rect Key_clip[6];

        SDL_Rect PlayerBox;
        SDL_Rect PlayerAttackBox;
        SDL_Rect HpBox;

        float VelX, VelY;
        float xPos, yPos;
        int HP, ENERGY, KEYS;
        int camX, camY;
        int idle_frame, attack1_frame, attack2_frame, run_frame, takehit_frame, death_frame;

        bool isAttacking, isWalking, dead, isAttacked;

        Input input_type;
        SDL_RendererFlip FlipType;
};

#endif // PLAYER_H
