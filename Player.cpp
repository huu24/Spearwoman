#include "Player.h"

Player::Player()
{
        HP = 5;
        attack1_frame = attack2_frame = idle_frame = takehit_frame = run_frame = death_frame = 0;
        VelX = 0;
        VelY = 0;
        x_pos = 0;
        y_pos = 0;
        width_frame = 0;
        height_frame = 0;
        map_x = 0;
        map_y = 0;
        input_type.left = false;
        input_type.right = false;
        input_type.up = false;
        input_type.down = false;
        input_type.attack1 = false;
        input_type.attack2 = false;
        input_type.take_hit = false;
        input_type.death = false;
        isAttacking = isAttacked = false;
        dead = false;
        FlipType = SDL_FLIP_NONE;
}

Player::~Player()
{

}

bool Player::CheckCollision(SDL_Rect& a, SDL_Rect& b)
{
        int x, y, u, v;
        x = std::max(a.x, b.x);
        y = std::max(a.y, b.y);
        u = std::min(a.x + a.w, b.x + b.w);
        v = std::min(a.y + a.h, b.y + b.h);
        if (x < u && y < v)
                return true;
        return false;
}

bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
        bool res = BaseObject::LoadImg(path, screen);

        return res;
}

void Player::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0, 32, 48};
                x += 32;
        }
        x = 0;
        for(int i = 0; i < WALK_FRAMES; i++)
        {
                Walk_clip[i] = {x, 49, 32, 48};
                x += 32;
        }
        x = 0;
        for(int i = 0; i < ATTACK1_FRAMES; i++)
        {
                Attack1_clip[i] = {x, 97, 80, 48};
                x += 80;
        }
        x = 0;
        for(int i = 0; i < ATTACK2_FRAMES; i++)
        {
                Attack2_clip[i] = {x, 144, 80, 48};
                x += 80;
        }
        PlayerAttackBox.w = 80;
        PlayerAttackBox.h = 48;
        x = 0;
        for(int i = 0; i < TAKEHIT_FRAMES; i++)
        {
                Takehit_clip[i] = {x, 193, 48, 48};
                x += 48;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 241, 48, 48};
                x += 48;
        }
        x = 0;
        for(int i = 1; i <= 5; i++)
        {
                HP_clip[i] = {x, 348, 49, 8};
                x += 49;
        }
        x = 0;
}

void Player::Handle(SDL_Event events)
{
        if(events.type == SDL_KEYDOWN && events.key.repeat == 0)
        {
                switch(events.key.keysym.sym)
                {
                case SDLK_RIGHT:
                        input_type.right = true;
                        input_type.left = false;
                        FlipType = SDL_FLIP_NONE;
                        break;
                case SDLK_LEFT:
                        input_type.left = true;
                        input_type.right = false;
                        FlipType = SDL_FLIP_HORIZONTAL;
                        break;
                case SDLK_UP:
                        input_type.up = true;
                        break;
                case SDLK_DOWN:
                        input_type.down = true;
                        break;
                case SDLK_k:
                        input_type.attack1 = true;
                        break;
                case SDLK_l:
                        input_type.attack2 = true;
                        break;
                }
        }
        else if(events.type == SDL_KEYUP)
        {
                switch(events.key.keysym.sym)
                {
                case SDLK_RIGHT:
                        input_type.right = false;
                        break;
                case SDLK_LEFT:
                        input_type.left = false;
                        break;
                case SDLK_UP:
                        input_type.up = false;
                        break;
                case SDLK_DOWN:
                        input_type.down = false;
                        break;
                }
        }
}
void Player::Move(Map& map_data)
{
        if(input_type.left)
        {
                VelX = -PlayerSpeed;
        }
        else if(input_type.right)
        {
                VelX = PlayerSpeed;
        }
        else VelX = 0;
        if(input_type.up)
        {
                VelY = -PlayerSpeed;
        }
        else if(input_type.down)
        {
                VelY = PlayerSpeed;
        }
        else VelY = 0;

        x_pos += VelX;
        y_pos += VelY;

        CollisionWithMap(map_data);
        SetCamera(map_data);
}

void Player::CollisionWithMap(Map& map_data)
{
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check horizontal
        x1 = (x_pos + VelX) / TILE_SIZE;
        x2 = (x_pos + VelX + PlayerBox.w - 1) / TILE_SIZE;

        y1 = y_pos / TILE_SIZE;
        y2 = (y_pos + PlayerBox.h - 1) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelX > 0)
                {
                        if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
                        {
                                x_pos = x2 * TILE_SIZE;
                                x_pos -= PlayerBox.w + 1;
                                VelX = 0;
                        }
                }
                else if(VelX < 0)
                {
                        if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
                        {
                                x_pos = (x1 + 1) * TILE_SIZE;
                                VelX = 0;
                        }
                }
        }

        //check_vertical
        x1 = x_pos / TILE_SIZE;
        x2 = (x_pos + PlayerBox.w) / TILE_SIZE;

        y1 = (y_pos + VelY) / TILE_SIZE;
        y2 = (y_pos + VelY + PlayerBox.h - 1) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelY > 0)
                {
                        if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
                        {
                                y_pos = y2 * TILE_SIZE;
                                y_pos -= (PlayerBox.h+1);
                                VelY = 0;
                        }
                }
                else if(VelY < 0)
                {
                        if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
                        {
                                y_pos = (y1+1) * TILE_SIZE;
                                VelY = 0;
                        }
                }
        }

        if(x_pos < 0)
        {
                x_pos = 0;
        }
        else if(x_pos + PlayerBox.w > map_data.max_x_)
        {
                x_pos = map_data.max_x_ - PlayerBox.w;
        }

        if(y_pos < 0)
        {
                y_pos = 0;
        }
        else if(y_pos + PlayerBox.h > map_data.max_y_)
        {
                y_pos = map_data.max_y_ - PlayerBox.h;
        }
}

void Player::SetCamera(Map& map_data)
{
        map_data.start_x_ = (x_pos) - SCREEN_WIDTH / 2;
        map_data.start_y_ = (y_pos) - SCREEN_HEIGHT / 2;

        if(map_data.start_x_ < 0) map_data.start_x_ = 0;
        if(map_data.start_x_ + SCREEN_WIDTH > map_data.max_x_) map_data.start_x_ = map_data.max_x_ -  SCREEN_WIDTH;

        if(map_data.start_y_ < 0) map_data.start_y_ = 0;
        if(map_data.start_y_ + SCREEN_HEIGHT > map_data.max_y_) map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
}

void Player::RenderPlayer(SDL_Renderer* des, bool SkeletonIsAttacking)
{
        if(SkeletonIsAttacking)
        {
                isAttacked = true;
                --HP;
        }
        PlayerBox.x = x_pos - map_x;
        PlayerBox.y = y_pos - map_y;

        PlayerAttackBox.x = x_pos;
        PlayerAttackBox.y = y_pos;

        SDL_Rect* current_clip;
        int current_frame;

        if(input_type.left || input_type.right || input_type.up || input_type.down )
        {
                current_frame = WALK_FRAMES;
                current_clip = &Walk_clip[run_frame / 16];

                PlayerBox.w = current_clip->w;
                PlayerBox.h = current_clip->h;

                run_frame++;
                if(run_frame >= current_frame * 16) run_frame = 0;

                SDL_Rect renderQuad = {PlayerBox.x, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else if(input_type.attack1)
        {
                current_frame = ATTACK1_FRAMES;
                current_clip = &Attack1_clip[attack1_frame / 32];

                PlayerBox.w = current_clip->w;
                PlayerBox.h = current_clip->h;

                PlayerAttackBox.x = x_pos + ((FlipType == SDL_FLIP_NONE) ? -16 : - 30);
                PlayerAttackBox.y = y_pos;
                PlayerAttackBox.w = current_clip->w;
                PlayerAttackBox.h = current_clip->h;

                attack1_frame++;
                if(attack1_frame == 1)
                {
                        isAttacking = true;
                }
                else isAttacking = false;
                if(attack1_frame >= current_frame * 32)
                {
                        attack1_frame = 0;
                        input_type.attack1 = false;
                }
                if(FlipType == SDL_FLIP_HORIZONTAL)
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 30, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                }
                else
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 16, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                }
        }
        else if(input_type.attack2)
        {
                current_frame = ATTACK2_FRAMES;
                current_clip = &Attack2_clip[attack2_frame/ 16];

                PlayerBox.w = current_clip->w;
                PlayerBox.h = current_clip->h;

                PlayerAttackBox.x = x_pos;
                PlayerAttackBox.y = y_pos;

                PlayerAttackBox.x = x_pos + ((FlipType == SDL_FLIP_NONE) ? 10 : - 40);
                PlayerAttackBox.y = y_pos;
                PlayerAttackBox.w = current_clip->w;
                PlayerAttackBox.h = current_clip->h;

                attack2_frame++;
                if(attack2_frame == 1) isAttacking = true;
                else isAttacking = false;

                if(attack2_frame >= current_frame * 16)
                {
                        attack2_frame = 0;
                        input_type.attack2 = false;
                }

                if(FlipType == SDL_FLIP_HORIZONTAL)
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 44, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                }
                else
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 4, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                }
        }
        else if(isAttacked)
        {
                current_frame = TAKEHIT_FRAMES;
                current_clip = &Takehit_clip[takehit_frame / 30];

                PlayerBox.w = current_clip->w;
                PlayerBox.h = current_clip->h;

                takehit_frame++;
                if(takehit_frame >= current_frame * 30)
                {
                        takehit_frame = 0;
                        isAttacked = false;
                }
                SDL_Rect renderQuad = {PlayerBox.x, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else if(HP == 0)
        {
                dead = true;
                current_frame = DEATH_FRAMES;
                current_clip = &Death_clip[death_frame / 60];

                PlayerBox.w = current_clip->w;
                PlayerBox.h = current_clip->h;

                death_frame++;
                if(death_frame >= current_frame * 60) death_frame = (current_frame - 1) * 60;
                SDL_Rect renderQuad = {PlayerBox.x, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else
        {
                current_frame = IDLE_FRAMES;
                current_clip = &Idle_clip[idle_frame / 16];

                PlayerBox.w = current_clip->w;
                PlayerBox.h = current_clip->h;

                idle_frame++;
                if(idle_frame >= current_frame * 16) idle_frame = 0;

                SDL_Rect renderQuad = {PlayerBox.x, PlayerBox.y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
}


void Player::RenderHP(SDL_Renderer* des)
{
        if(!dead)
        {
                SDL_Rect* current_clip;
                current_clip = &HP_clip[HP];
                SDL_Rect renderQuad = {10, 10, current_clip->w * 5, current_clip->h * 5};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }

}
