#include "Skeleton.h"

Skeleton::Skeleton(float x, float y)
{
        HP = 3;
        x_pos = x, y_pos = y;
        max_x = x_pos + 300;
        min_x = x_pos - 300;
        max_y = y_pos + 300;
        min_y = y_pos - 300;
        VelX = 0, VelY = 0;
        idle_frame = walk_frame = attack_frame = takehit_frame = death_frame = 0;
        FlipType = SDL_FLIP_HORIZONTAL;
        isWalking = isAttacking = isDead = isAttacked = attack = false;
        isIdling = true;
}
Skeleton::~Skeleton()
{

}

void Skeleton::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0 , 48*3, 51*3};
                x += 48*3;
        }
        SkeletonBox.h = 51*3 / 2;
        SkeletonBox.w = 48*3 / 2;
        x = 0;
        for(int i = 0; i < WALK_FRAMES; i++)
        {
                Walk_clip[i] = {x, 51*3, 48*3, 53*3};
                x += 48*3;
        }
        x = 0;
        for(int i = 0; i < ATTACK_FRAMES; i++)
        {
                Attack_clip[i] = {x, 102*3, 96*3, 57*3};
                x += 96*3;
        }
        x = 0;
        for(int i = 0; i < TAKEHIT_FRAMES; i++)
        {
                TakeHit_clip[i] = {x, 159*3, 48*3, 53*3};
                x += 48*3;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 212*3, 80*3, 63*3};
                x += 80*3;
        }
        x = 0;
        for(int i = 1; i <= 3; i++)
        {
                HP_clip[i] = {x, 275*3, 48*3, 6*3};
                x += 48*3;
        }
        x = 0;
}

void Skeleton::CollisionWithMap(Map& map_data)
{
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check horizontal


        x1 = (x_pos) / TILE_SIZE;
        x2 = (x_pos + SkeletonBox.w) / TILE_SIZE;


        y1 = (y_pos ) / TILE_SIZE;
        y2 = (y_pos + SkeletonBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelX > 0)
                {
                        if(map_data.TileType[y1][x2] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                VelX = 0;
                        }
                }
                else if(VelX < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y2][x1] >= 4)
                        {
                                VelX = 0;
                        }
                }
        }

        //check_vertical
        x1 = x_pos / TILE_SIZE;
        x2 = (x_pos + SkeletonBox.w) / TILE_SIZE;

        y1 = (y_pos ) / TILE_SIZE;
        y2 = (y_pos + SkeletonBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelY > 0)
                {
                        if(map_data.TileType[y2][x1] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                VelY = 0;
                        }
                }
                else if(VelY < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y1][x2] >= 4)
                        {
                                VelY = 0;
                        }
                }
        }

        if(x_pos < 0)
        {
                x_pos = 0;
        }
        else if(x_pos + SkeletonBox.w > map_data.max_x_)
        {
                x_pos = map_data.max_x_ - SkeletonBox.w;
        }

        if(y_pos < 0)
        {
                y_pos = 0;
        }
        else if(y_pos + SkeletonBox.h > map_data.max_y_)
        {
                y_pos = map_data.max_y_ - SkeletonBox.h;
        }
}

void Skeleton::Move(SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, int camX, int camY, Map& map_data, bool PlayerIsDead, bool PlayerIsAttack)
{
        if(PlayerIsAttack)
        {
                if(BaseObject::CheckCollision(SkeletonBox, PlayerAttackBox))
                {
                        --HP;
                        isAttacked = true;
                }
        }
        else
        {
                if(!PlayerIsDead && BaseObject::CheckCollision(SkeletonBox, PlayerBox))
                {
                        attack = true;
                }
        }
        if(isDead || isAttacked || attack || PlayerBox.x <= min_x || PlayerBox.x >= max_x || PlayerBox.y >= max_y || PlayerBox.y <= min_y)
        {
                isWalking = false;
                return;
        }
        SkeletonBox.x = x_pos;
        SkeletonBox.y = y_pos;

        if(PlayerBox.x > SkeletonBox.x)
        {
                if(FlipType == SDL_FLIP_HORIZONTAL) FlipType = SDL_FLIP_NONE;
        }
        else
        {
                if(FlipType == SDL_FLIP_NONE) FlipType = SDL_FLIP_HORIZONTAL;
        }

        if(SkeletonBox.x <= min_x || SkeletonBox.x >= max_x)
        {
                VelX = 0;
        }
        else
        {
                if(FlipType == SDL_FLIP_NONE)
                {
                        if(SkeletonBox.x  + SkeletonBox.w <= PlayerBox.x)
                        {
                                VelX = DemonSpeed;
                        }
                        else VelX = 0;
                }
                else
                {
                        if(SkeletonBox.x >= PlayerBox.x + PlayerBox.w)
                        {
                                VelX = -DemonSpeed;
                        }
                        else VelX = 0;
                }
                if(CheckCollision(SkeletonBox, PlayerBox))
                {
                        VelX = 0;
                }
        }
        if(SkeletonBox.y <= min_y || SkeletonBox.y >= max_y)
        {
                VelY = 0;
        }
        else
        {
                if(SkeletonBox.y  + SkeletonBox.h < PlayerBox.y + PlayerBox.h)
                {
                        VelY = DemonSpeed;
                }
                else if(SkeletonBox.y  + SkeletonBox.h > PlayerBox.y + PlayerBox.h)
                {
                        VelY = - DemonSpeed;
                }
                else VelY = 0;

        }
        if(VelX == 0 && VelY == 0) isWalking = false;
        else isWalking = true;

        CollisionWithMap(map_data);

        x_pos += VelX;
        y_pos += VelY;
}

void Skeleton::Render(SDL_Renderer* screen, SDL_Texture* SkeTexture ,SDL_Rect PlayerBox, SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int camX, int camY, Mix_Chunk *skeSound[])
{
        if(HP <= 0) isDead = true;

        SDL_Rect* current_clip;
        int current_frame;

        SkeletonBox.x = x_pos;
        SkeletonBox.y = y_pos;

        SkeletonAttackBox.x = x_pos;
        SkeletonAttackBox.y = y_pos;

        if(isDead)
        {
                current_clip = &Death_clip[death_frame / 10];
                current_frame = DEATH_FRAMES;
                if(death_frame == 0)
                {
                        Mix_PlayChannel(1, skeSound[DEATH_SOUND_], 0);
                }
                death_frame++;
                if(death_frame == 7 * 10)
                {
                        Mix_PlayChannel(1, skeSound[BOOM_SOUND_], 0);
                }
                if(death_frame == 9 * 10 && BaseObject::CheckCollision(PlayerBox, SkeletonBox))
                {
                        isAttacking = true;
                }
                else isAttacking = false;
                if(death_frame >= current_frame * 10) death_frame = current_frame * 10;
                SkeletonBox.w = current_clip->w / 2;
                SkeletonBox.h = current_clip->h / 2;
                SDL_Rect RenderQuad = {SkeletonBox.x - camX, SkeletonBox.y - camY,SkeletonBox.w ,SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isAttacked)
        {
                current_clip = &TakeHit_clip[takehit_frame / 10];
                current_frame = TAKEHIT_FRAMES;
                takehit_frame++;
                if(takehit_frame >= current_frame * 10)
                {
                        takehit_frame = 0;
                        isAttacked = false;
                }
                if(HP <= 0) HP = 0;
                SkeletonBox.w = current_clip->w / 2;
                SkeletonBox.h = current_clip->h / 2;
                SDL_Rect RenderQuad = {SkeletonBox.x - camX, SkeletonBox.y - camY - 4,SkeletonBox.w ,SkeletonBox.h};
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(attack)
        {
                current_clip = &Attack_clip[attack_frame / 12];
                current_frame = ATTACK_FRAMES;
                attack_frame++;
                if(attack_frame == 6 * 12)
                {
                        Mix_PlayChannel(1, skeSound[ATTACK_SOUND_], 0);
                }
                Mix_VolumeChunk(skeSound[ATTACK_SOUND_], 32);
                if(attack_frame == (current_frame - 1) * 12 && CheckCollision(PlayerBox, SkeletonAttackBox)) isAttacking = true;
                else isAttacking = false;
                if(attack_frame >= current_frame * 12)
                {
                        attack_frame = 0;
                        attack = false;
                }
                SkeletonAttackBox.x = x_pos + ((FlipType == SDL_FLIP_NONE) ? -8 : -48);
                SkeletonAttackBox.y = y_pos - 7;
                SkeletonAttackBox.w = current_clip->w / 2;
                SkeletonAttackBox.h = current_clip->h / 2;

                SDL_Rect RenderQuad = {SkeletonAttackBox.x - camX, SkeletonAttackBox.y - camY, SkeletonAttackBox.w, SkeletonAttackBox.h};
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else if(isWalking)
        {
                current_clip = &Walk_clip[walk_frame / 10];
                current_frame = WALK_FRAMES;
//                if(walk_frame == 0)
//                {
//                        Mix_PlayChannel(-1, skeSound[WALK_SOUND_], 0);
//                }
                walk_frame++;
                if(walk_frame >= current_frame * 10) walk_frame = 0;
                SkeletonBox.w = current_clip->w / 2;
                SkeletonBox.h = current_clip->h / 2;
                SDL_Rect RenderQuad = {SkeletonBox.x - camX, SkeletonBox.y - camY, SkeletonBox.w , SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
        else
        {
                current_clip = &Idle_clip[idle_frame / 10];
                current_frame = IDLE_FRAMES;
                idle_frame++;
                if(idle_frame >= current_frame * 10) idle_frame = 0;
                SkeletonBox.w = current_clip->w / 2;
                SkeletonBox.h = current_clip->h / 2;
                SDL_Rect RenderQuad = {SkeletonBox.x - camX, SkeletonBox.y - camY, SkeletonBox.w, SkeletonBox.h };
                SDL_RenderCopyEx(screen, SkeTexture, current_clip, &RenderQuad, 0.0, NULL, FlipType);
        }
}

void Skeleton::RenderHP(SDL_Renderer* screen, SDL_Texture* SkeletonTexture, int camX, int camY)
{
        if(isDead) return;
        if(!isDead)
        {
                SDL_Rect* current_clip = &HP_clip[HP];
                SDL_Rect renderQuad = {SkeletonBox.x - camX, SkeletonBox.y - camY - 14, current_clip->w / 2, current_clip->h / 2};
                SDL_RenderCopyEx(screen, SkeletonTexture, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }
}

SkeletonArmy::SkeletonArmy()
{
        skeleton.push_back(Skeleton(13*64, 2*64));
        skeleton.push_back(Skeleton(13*64, 3*64));
        skeleton.push_back(Skeleton(13*64, 4*64));
        skeleton.push_back(Skeleton(8*64, 9*64));
        skeleton.push_back(Skeleton(10*64, 9*64));
        skeleton.push_back(Skeleton(12*64, 9*64));
        skeleton.push_back(Skeleton(3*64, 14*64));
        skeleton.push_back(Skeleton(4*64, 14*64));
        skeleton.push_back(Skeleton(13*64, 15*64));
        skeleton.push_back(Skeleton(12*64, 16*64));
        skeleton.push_back(Skeleton(11*64, 17*64));
        skeleton.push_back(Skeleton(19*64, 1*64));
        skeleton.push_back(Skeleton(19*64, 6*64));
        skeleton.push_back(Skeleton(19*64, 11*64));
        skeleton.push_back(Skeleton(27*64, 17*64));
        skeleton.push_back(Skeleton(33*64, 16*64));
        skeleton.push_back(Skeleton(39*64, 17*64));
        skeleton.push_back(Skeleton(29*64, 6*64));
        skeleton.push_back(Skeleton(31*64, 8*64));
        skeleton.push_back(Skeleton(33*64, 10*64));
        skeleton.push_back(Skeleton(33*64, 6*64));
        skeleton.push_back(Skeleton(29*64, 10*64));
        skeleton.push_back(Skeleton(32*64, 2*64));
        skeleton.push_back(Skeleton(34*64, 2*64));
        skeleton.push_back(Skeleton(42*64, 8*64));
        skeleton.push_back(Skeleton(42*64, 16*64));
        skeleton.push_back(Skeleton(40*64, 16*64));
        skeleton.push_back(Skeleton(41*64, 17*64));
        skeleton.push_back(Skeleton(42*64, 11*64));
        skeleton.push_back(Skeleton(50*64, 4*64));
        skeleton.push_back(Skeleton(50*64, 9*64));
        skeleton.push_back(Skeleton(50*64, 14*64));
        skeleton.push_back(Skeleton(57*64, 0*64));
        skeleton.push_back(Skeleton(65*64, 0*64));
        skeleton.push_back(Skeleton(60*64, 9*64));
        skeleton.push_back(Skeleton(60*64, 13*64));
        skeleton.push_back(Skeleton(60*64, 17*64));
        skeleton.push_back(Skeleton(68*64, 17*64));
        skeleton.push_back(Skeleton(81*64, 6*64));
        skeleton.push_back(Skeleton(81*64, 8*64));
        skeleton.push_back(Skeleton(81*64, 10*64));
        skeleton.push_back(Skeleton(81*64, 12*64));
        skeleton.push_back(Skeleton(85*64, 6*64));
        skeleton.push_back(Skeleton(85*64, 8*64));
        skeleton.push_back(Skeleton(85*64, 10*64));
        skeleton.push_back(Skeleton(85*64, 12*64));
        skeleton.push_back(Skeleton(83*64, 9*64));
        skeleton.push_back(Skeleton(73*64, 2*64));
        skeleton.push_back(Skeleton(76*64, 0*64));
        skeleton.push_back(Skeleton(79*64, 2*64));
        skeleton.push_back(Skeleton(82*64, 0*64));
        skeleton.push_back(Skeleton(85*64, 2*64));
        skeleton.push_back(Skeleton(75*64, 15*64));
        skeleton.push_back(Skeleton(75*64, 17*64));
        skeleton.push_back(Skeleton(79*64, 15*64));
        skeleton.push_back(Skeleton(79*64, 17*64));
        skeleton.push_back(Skeleton(83*64, 15*64));
        skeleton.push_back(Skeleton(83*64, 17*64));
        skeleton.push_back(Skeleton(91*64, 9*64));
        skeleton.push_back(Skeleton(91*64, 1*64));
        skeleton.push_back(Skeleton(96*64, 1*64));
        skeleton.push_back(Skeleton(96*64, 3*64));
        skeleton.push_back(Skeleton(96*64, 10*64));
        skeleton.push_back(Skeleton(93*64, 16*64));
        skeleton.push_back(Skeleton(96*64, 16*64));
        skeleton.push_back(Skeleton(103*64, 9*64));
        skeleton.push_back(Skeleton(103*64, 11*64));
        skeleton.push_back(Skeleton(108*64, 6*64));
        skeleton.push_back(Skeleton(113*64, 6*64));
        skeleton.push_back(Skeleton(108*64, 8*64));
        skeleton.push_back(Skeleton(113*64, 8*64));
        skeleton.push_back(Skeleton(108*64, 10*64));
        skeleton.push_back(Skeleton(113*64, 10*64));
        skeleton.push_back(Skeleton(108*64, 12*64));
        skeleton.push_back(Skeleton(113*64, 12*64));
        skeleton.push_back(Skeleton(108*64, 14*64));
        skeleton.push_back(Skeleton(113*64, 14*64));
        skeleton.push_back(Skeleton(110*64, 6*64));
        skeleton.push_back(Skeleton(111*64, 14*64));
        skeleton.push_back(Skeleton(130*64, 12*64));
        skeleton.push_back(Skeleton(132*64, 11*64));
        skeleton.push_back(Skeleton(134*64, 10*64));
        skeleton.push_back(Skeleton(136*64, 9*64));
        skeleton.push_back(Skeleton(138*64, 8*64));
        skeleton.push_back(Skeleton(145*64, 1*64));
        skeleton.push_back(Skeleton(145*64, 3*64));
        skeleton.push_back(Skeleton(130*64, 17*64));
        skeleton.push_back(Skeleton(132*64, 17*64));
        skeleton.push_back(Skeleton(134*64, 17*64));
        skeleton.push_back(Skeleton(151*64, 16*64));
        skeleton.push_back(Skeleton(155*64, 15*64));
        skeleton.push_back(Skeleton(155*64, 17*64));
        skeleton.push_back(Skeleton(155*64, 1*64));
        skeleton.push_back(Skeleton(155*64, 3*64));
        skeleton.push_back(Skeleton(165*64, 8*64));
        skeleton.push_back(Skeleton(165*64, 10*64));
        skeleton.push_back(Skeleton(165*64, 1*64));
        skeleton.push_back(Skeleton(165*64, 17*64));
        skeleton.push_back(Skeleton(171*64, 15*64));
        skeleton.push_back(Skeleton(171*64, 17*64));
        skeleton.push_back(Skeleton(175*64, 0*64));
        skeleton.push_back(Skeleton(177*64, 1*64));
        skeleton.push_back(Skeleton(179*64, 2*64));
        skeleton.push_back(Skeleton(179*64, 8*64));
        skeleton.push_back(Skeleton(180*64, 8*64));
        skeleton.push_back(Skeleton(178*64, 10*64));
        skeleton.push_back(Skeleton(181*64, 10*64));
        skeleton.push_back(Skeleton(177*64, 12*64));
        skeleton.push_back(Skeleton(182*64, 12*64));
        skeleton.push_back(Skeleton(176*64, 14*64));
        skeleton.push_back(Skeleton(183*64, 14*64));
        skeleton.push_back(Skeleton(195*64, 9*64));
        skeleton.push_back(Skeleton(198*64, 9*64));
        skeleton.push_back(Skeleton(201*64, 9*64));
        skeleton.push_back(Skeleton(204*64, 9*64));
        skeleton.push_back(Skeleton(199*64, 1*64));
        skeleton.push_back(Skeleton(199*64, 4*64));
        skeleton.push_back(Skeleton(194*64, 15*64));
        skeleton.push_back(Skeleton(194*64, 17*64));
        skeleton.push_back(Skeleton(201*64, 17*64));
        skeleton.push_back(Skeleton(206*64, 5*64));
        skeleton.push_back(Skeleton(209*64, 5*64));
        skeleton.push_back(Skeleton(212*64, 5*64));
        skeleton.push_back(Skeleton(210*64, 15*64));
        skeleton.push_back(Skeleton(210*64, 17*64));
        skeleton.push_back(Skeleton(214*64, 15*64));
        skeleton.push_back(Skeleton(214*64, 17*64));
        skeleton.push_back(Skeleton(218*64, 5*64));
        skeleton.push_back(Skeleton(222*64, 5*64));
        skeleton.push_back(Skeleton(225*64, 11*64));
        skeleton.push_back(Skeleton(227*64, 11*64));
        skeleton.push_back(Skeleton(220*64, 7*64));
        skeleton.push_back(Skeleton(10*64, 23*64));
        skeleton.push_back(Skeleton(10*64, 25*64));
        skeleton.push_back(Skeleton(12*64, 23*64));
        skeleton.push_back(Skeleton(12*64, 25*64));
        skeleton.push_back(Skeleton(5*64, 31*64));
        skeleton.push_back(Skeleton(7*64, 31*64));
        skeleton.push_back(Skeleton(9*64, 31*64));
        skeleton.push_back(Skeleton(11*64, 31*64));
        skeleton.push_back(Skeleton(7*64, 35*64));
        skeleton.push_back(Skeleton(7*64, 37*64));
        skeleton.push_back(Skeleton(10*64, 23*64));
        skeleton.push_back(Skeleton(9*64, 36*64));
        skeleton.push_back(Skeleton(23*64, 33*64));
        skeleton.push_back(Skeleton(25*64, 33*64));
        skeleton.push_back(Skeleton(27*64, 33*64));
        skeleton.push_back(Skeleton(29*64, 33*64));
        skeleton.push_back(Skeleton(31*64, 33*64));
        skeleton.push_back(Skeleton(33*64, 33*64));
        skeleton.push_back(Skeleton(35*64, 33*64));
        skeleton.push_back(Skeleton(37*64, 33*64));
        skeleton.push_back(Skeleton(39*64, 33*64));
        skeleton.push_back(Skeleton(37*64, 21*64));
        skeleton.push_back(Skeleton(37*64, 23*64));
        skeleton.push_back(Skeleton(37*64, 25*64));
        skeleton.push_back(Skeleton(40*64, 21*64));
        skeleton.push_back(Skeleton(40*64, 23*64));
        skeleton.push_back(Skeleton(40*64, 25*64));
        skeleton.push_back(Skeleton(22*64, 23*64));
        skeleton.push_back(Skeleton(22*64, 25*64));
        skeleton.push_back(Skeleton(47*64, 32*64));
        skeleton.push_back(Skeleton(47*64, 36*64));
        skeleton.push_back(Skeleton(45*64, 34*64));
        skeleton.push_back(Skeleton(58*64, 32*64));
        skeleton.push_back(Skeleton(58*64, 36*64));
        skeleton.push_back(Skeleton(56*64, 34*64));
        skeleton.push_back(Skeleton(69*64, 32*64));
        skeleton.push_back(Skeleton(69*64, 36*64));
        skeleton.push_back(Skeleton(67*64, 34*64));
        skeleton.push_back(Skeleton(71*64, 24*64));
        skeleton.push_back(Skeleton(75*64, 24*64));
        skeleton.push_back(Skeleton(83*64, 24*64));
        skeleton.push_back(Skeleton(81*64, 34*64));
        skeleton.push_back(Skeleton(84*64, 34*64));
        skeleton.push_back(Skeleton(88*64, 35*64));
        skeleton.push_back(Skeleton(90*64, 35*64));
        skeleton.push_back(Skeleton(88*64, 37*64));
        skeleton.push_back(Skeleton(90*64, 37*64));
        skeleton.push_back(Skeleton(99*64, 22*64));
        skeleton.push_back(Skeleton(99*64, 26*64));
        skeleton.push_back(Skeleton(105*64, 25*64));
        skeleton.push_back(Skeleton(105*64, 29*64));
        skeleton.push_back(Skeleton(97*64, 37*64));
        skeleton.push_back(Skeleton(100*64, 37*64));
        skeleton.push_back(Skeleton(103*64, 37*64));
        skeleton.push_back(Skeleton(106*64, 37*64));
        skeleton.push_back(Skeleton(109*64, 37*64));
        skeleton.push_back(Skeleton(112*64, 37*64));
        skeleton.push_back(Skeleton(115*64, 37*64));
        skeleton.push_back(Skeleton(89*64, 19*64));
        skeleton.push_back(Skeleton(89*64, 22*64));
        skeleton.push_back(Skeleton(89*64, 25*64));
        skeleton.push_back(Skeleton(89*64, 28*64));
        skeleton.push_back(Skeleton(112*64, 22*64));
        skeleton.push_back(Skeleton(112*64, 26*64));
        skeleton.push_back(Skeleton(116*64, 35*64));
        skeleton.push_back(Skeleton(118*64, 36*64));
        skeleton.push_back(Skeleton(120*64, 37*64));
        skeleton.push_back(Skeleton(116*64, 37*64));
        skeleton.push_back(Skeleton(120*64, 35*64));
        skeleton.push_back(Skeleton(118*64, 32*64));
        skeleton.push_back(Skeleton(118*64, 29*64));
        skeleton.push_back(Skeleton(118*64, 26*64));
        skeleton.push_back(Skeleton(118*64, 23*64));
        skeleton.push_back(Skeleton(121*64, 23*64));
        skeleton.push_back(Skeleton(124*64, 23*64));
        skeleton.push_back(Skeleton(127*64, 23*64));
        skeleton.push_back(Skeleton(130*64, 23*64));
        skeleton.push_back(Skeleton(125*64, 32*64));
        skeleton.push_back(Skeleton(128*64, 32*64));
        skeleton.push_back(Skeleton(131*64, 32*64));
        skeleton.push_back(Skeleton(135*64, 28*64));
        skeleton.push_back(Skeleton(137*64, 28*64));
        skeleton.push_back(Skeleton(139*64, 28*64));
        skeleton.push_back(Skeleton(141*64, 28*64));
        skeleton.push_back(Skeleton(143*64, 28*64));
        skeleton.push_back(Skeleton(135*64, 30*64));
        skeleton.push_back(Skeleton(137*64, 30*64));
        skeleton.push_back(Skeleton(139*64, 30*64));
        skeleton.push_back(Skeleton(141*64, 30*64));
        skeleton.push_back(Skeleton(143*64, 30*64));
        skeleton.push_back(Skeleton(139*64, 35*64));
        skeleton.push_back(Skeleton(139*64, 37*64));
        skeleton.push_back(Skeleton(141*64, 36*64));
        skeleton.push_back(Skeleton(143*64, 35*64));
        skeleton.push_back(Skeleton(143*64, 37*64));
        skeleton.push_back(Skeleton(145*64, 36*64));
        skeleton.push_back(Skeleton(76*64, 29*64));
        skeleton.push_back(Skeleton(78*64, 29*64));
        skeleton.push_back(Skeleton(80*64, 29*64));
        skeleton.push_back(Skeleton(133*64, 23*64));
        skeleton.push_back(Skeleton(137*64, 23*64));
        skeleton.push_back(Skeleton(141*64, 23*64));
        skeleton.push_back(Skeleton(145*64, 23*64));
        skeleton.push_back(Skeleton(146*64, 29*64));
        skeleton.push_back(Skeleton(148*64, 29*64));
        skeleton.push_back(Skeleton(150*64, 29*64));
        skeleton.push_back(Skeleton(154*64, 22*64));
        skeleton.push_back(Skeleton(156*64, 22*64));
        skeleton.push_back(Skeleton(154*64, 35*64));
        skeleton.push_back(Skeleton(156*64, 35*64));
        skeleton.push_back(Skeleton(155*64, 27*64));
        skeleton.push_back(Skeleton(155*64, 29*64));
        skeleton.push_back(Skeleton(160*64, 30*64));
        skeleton.push_back(Skeleton(162*64, 31*64));
        skeleton.push_back(Skeleton(164*64, 30*64));
        skeleton.push_back(Skeleton(167*64, 28*64));
        skeleton.push_back(Skeleton(167*64, 25*64));
        skeleton.push_back(Skeleton(167*64, 22*64));
        skeleton.push_back(Skeleton(172*64, 24*64));
        skeleton.push_back(Skeleton(173*64, 24*64));
        skeleton.push_back(Skeleton(171*64, 29*64));
        skeleton.push_back(Skeleton(174*64, 29*64));
        skeleton.push_back(Skeleton(172*64, 34*64));
        skeleton.push_back(Skeleton(173*64, 34*64));
        skeleton.push_back(Skeleton(187*64, 20*64));
        skeleton.push_back(Skeleton(187*64, 22*64));
        skeleton.push_back(Skeleton(185*64, 20*64));
        skeleton.push_back(Skeleton(185*64, 22*64));
        skeleton.push_back(Skeleton(183*64, 20*64));
        skeleton.push_back(Skeleton(183*64, 22*64));
        skeleton.push_back(Skeleton(181*64, 20*64));
        skeleton.push_back(Skeleton(181*64, 22*64));
        skeleton.push_back(Skeleton(179*64, 20*64));
        skeleton.push_back(Skeleton(179*64, 22*64));
        skeleton.push_back(Skeleton(177*64, 26*64));
        skeleton.push_back(Skeleton(183*64, 26*64));
        skeleton.push_back(Skeleton(190*64, 26*64));
        skeleton.push_back(Skeleton(179*64, 32*64));
        skeleton.push_back(Skeleton(182*64, 32*64));
        skeleton.push_back(Skeleton(186*64, 32*64));
        skeleton.push_back(Skeleton(189*64, 35*64));
        skeleton.push_back(Skeleton(189*64, 37*64));
        skeleton.push_back(Skeleton(192*64, 22*64));
        skeleton.push_back(Skeleton(192*64, 31*64));
        skeleton.push_back(Skeleton(197*64, 34*64));
        skeleton.push_back(Skeleton(198*64, 30*64));
        skeleton.push_back(Skeleton(197*64, 26*64));
        skeleton.push_back(Skeleton(201*64, 22*64));
        skeleton.push_back(Skeleton(204*64, 22*64));
        skeleton.push_back(Skeleton(204*64, 29*64));
        skeleton.push_back(Skeleton(204*64, 34*64));
        skeleton.push_back(Skeleton(210*64, 27*64));
        skeleton.push_back(Skeleton(220*64, 27*64));
        skeleton.push_back(Skeleton(215*64, 27*64));
        skeleton.push_back(Skeleton(207*64, 37*64));
        skeleton.push_back(Skeleton(210*64, 37*64));
        skeleton.push_back(Skeleton(210*64, 32*64));
        skeleton.push_back(Skeleton(214*64, 30*64));
        skeleton.push_back(Skeleton(214*64, 32*64));
        skeleton.push_back(Skeleton(217*64, 30*64));
        skeleton.push_back(Skeleton(217*64, 32*64));
        skeleton.push_back(Skeleton(220*64, 30*64));
        skeleton.push_back(Skeleton(220*64, 32*64));
        skeleton.push_back(Skeleton(217*64, 37*64));
        skeleton.push_back(Skeleton(221*64, 37*64));
        skeleton.push_back(Skeleton(228*64, 29*64));
        skeleton.push_back(Skeleton(228*64, 34*64));
        skeleton.push_back(Skeleton(233*64, 37*64));
        skeleton.push_back(Skeleton(237*64, 37*64));
        skeleton.push_back(Skeleton(240*64, 37*64));
        skeleton.push_back(Skeleton(245*64, 32*64));
        skeleton.push_back(Skeleton(247*64, 32*64));
        skeleton.push_back(Skeleton(245*64, 26*64));
        skeleton.push_back(Skeleton(247*64, 26*64));
        skeleton.push_back(Skeleton(244*64, 22*64));
        skeleton.push_back(Skeleton(240*64, 22*64));
        skeleton.push_back(Skeleton(241*64, 30*64));
        skeleton.push_back(Skeleton(234*64, 30*64));
        skeleton.push_back(Skeleton(237*64, 32*64));
        skeleton.push_back(Skeleton(238*64, 32*64));
        skeleton.push_back(Skeleton(222*64, 20*64));
        skeleton.push_back(Skeleton(222*64, 22*64));
        skeleton.push_back(Skeleton(215*64, 20*64));
        skeleton.push_back(Skeleton(215*64, 22*64));
        skeleton.push_back(Skeleton(220*64, 16*64));
        skeleton.push_back(Skeleton(222*64, 16*64));
        skeleton.push_back(Skeleton(224*64, 16*64));
        skeleton.push_back(Skeleton(226*64, 19*64));
}

SkeletonArmy::~SkeletonArmy()
{

}

void SkeletonArmy::set_clips()
{
        for(int i = 0; i < (int)skeleton.size(); i++)
        {
                skeleton[i].set_clips();
        }
}

void SkeletonArmy::Move(SDL_Rect PlayerBox ,SDL_Rect PlayerAttackBox, int camX, int camY, Map& map_data, bool PlayerIsDead, bool PlayerIsAttack)
{
        for(int i = 0; i < (int)skeleton.size(); i++)
        {
                skeleton[i].Move(PlayerBox, PlayerAttackBox, camX, camY, map_data, PlayerIsDead, PlayerIsAttack);
        }
}

void SkeletonArmy::Render(SDL_Renderer* screen, SDL_Texture* SkeTexture, SDL_Rect PlayerBox,  SDL_Rect PlayerAttackBox, bool PlayerIsAttack, bool PlayerIsDead, int camX, int camY, Mix_Chunk *skeSound[])
{
        for(int i = 0; i < (int)skeleton.size(); i++)
        {
                skeleton[i].Render(screen, SkeTexture,PlayerBox, PlayerAttackBox, PlayerIsAttack, PlayerIsDead, camX, camY, skeSound);
        }
}
void SkeletonArmy::RenderHP(SDL_Renderer* screen, SDL_Texture* SkeletonTexture, int camX, int camY)
{
        for(int i = 0; i < (int)skeleton.size(); i++)
        {
                skeleton[i].RenderHP(screen, SkeletonTexture, camX, camY);
        }
}

bool SkeletonArmy::getAttackStatus()
{
        for(int i = 0; i < (int)skeleton.size(); i++)
        {
                if(skeleton[i].getAttackStatus()) return true;
        }
        return false;
}
