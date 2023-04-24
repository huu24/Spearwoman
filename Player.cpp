#include "Player.h"

Player::Player()
{
        HP = 5;
        attack1_frame = attack2_frame = idle_frame = takehit_frame = run_frame = death_frame = 0;
        VelX = VelY = 0;
        x_pos = 0;
        y_pos = 500;
        map_x = map_y = 0;
        input_type.left = input_type.right = input_type.up = input_type.down = input_type.attack1 = input_type.attack2 = input_type.take_hit
        = input_type.death = isAttacking  = isWalking = isAttacked = dead = false;
        FlipType = SDL_FLIP_NONE;
        PlayerAttackBox.w = PlayerAttackBox.h = 0;
}

Player::~Player()
{

}

bool Player::CheckCollision(SDL_Rect& a, SDL_Rect& b)
{
        int x, y, u, v;
        x = max(a.x, b.x);
        y = max(a.y, b.y);
        u = min(a.x + a.w, b.x + b.w);
        v = min(a.y + a.h, b.y + b.h);
        if (x < u && y < v) return true;
        return false;
}

bool Player::LoadImg(string path, SDL_Renderer* screen)
{
        bool res = BaseObject::LoadImg(path, screen);
        return res;
}

void Player::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0, 320, 480};
                x += 320;
        }
        x = 0;
        for(int i = 0; i < WALK_FRAMES; i++)
        {
                Walk_clip[i] = {x, 490, 320, 480};
                x += 320;
        }
        x = 0;
        for(int i = 0; i < ATTACK1_FRAMES; i++)
        {
                Attack1_clip[i] = {x, 970, 800, 480};
                x += 800;
        }
        x = 0;
        for(int i = 0; i < ATTACK2_FRAMES; i++)
        {
                Attack2_clip[i] = {x, 1440, 800, 480};
                x += 800;
        }
        PlayerAttackBox.w = 0;
        PlayerAttackBox.h = 0;
        x = 0;
        for(int i = 0; i < TAKEHIT_FRAMES; i++)
        {
                Takehit_clip[i] = {x, 1930, 480, 480};
                x += 480;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 2410, 480, 480};
                x += 480;
        }
        x = 0;
        for(int i = 1; i <= 5; i++)
        {
                HP_clip[i] = {x, 3480, 490, 80};
                x += 490;
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
        else if(events.type == SDL_KEYUP && events.key.repeat == 0)
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
        isWalking = true;
        if(input_type.left)
        {
                VelX = -PlayerSpeed;
        }
        else if(input_type.right)
        {
                VelX = PlayerSpeed;
        }
        else
        {
                VelX = 0;
        }
        if(input_type.up)
        {
                VelY = -PlayerSpeed;
        }
        else if(input_type.down)
        {
                VelY = PlayerSpeed;
        }
        else
        {
                VelY = 0;
        }
        if(VelX  == 0 && VelY == 0) isWalking = false;

        x_pos += VelX;
        y_pos += VelY;

        PlayerBox.x = x_pos;
        PlayerBox.y = y_pos;

        PlayerAttackBox.x = x_pos;
        PlayerAttackBox.y = y_pos;

        CollisionWithMap(map_data);
        SetCamera(map_data);
}

void Player::CollisionWithMap(Map& map_data)
{
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check horizontal

        int min_height = min(TILE_SIZE, PlayerBox.h);

        x1 = (x_pos) / TILE_SIZE;
        x2 = (x_pos + PlayerBox.w) / TILE_SIZE;

        y1 = (y_pos + PlayerBox.h - min_height) / TILE_SIZE;
        y2 = (y_pos + PlayerBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelX > 0)
                {
                        if(map_data.TileType[y1][x2] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                x_pos -= VelX;
                        }
                }
                else if(VelX < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y2][x1] >= 4)
                        {
                                x_pos -= VelX;
                        }
                }
        }

        //check_vertical
        x1 = x_pos / TILE_SIZE;
        x2 = (x_pos + PlayerBox.w) / TILE_SIZE;

        y1 = (y_pos + PlayerBox.h - min_height) / TILE_SIZE;
        y2 = (y_pos + PlayerBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelY > 0)
                {
                        if(map_data.TileType[y2][x1] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                y_pos -= VelY;
                        }
                }
                else if(VelY < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y1][x2] >= 4)
                        {
                                y_pos -= VelY;
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
        map_data.current_x_pos = (x_pos) - SCREEN_WIDTH / 2;
        map_data.current_y_pos = (y_pos) - SCREEN_HEIGHT / 2;

        if(map_data.current_x_pos < 0) map_data.current_x_pos = 0;
        if(map_data.current_x_pos + SCREEN_WIDTH > map_data.max_x_) map_data.current_x_pos = map_data.max_x_ -  SCREEN_WIDTH;

        if(map_data.current_y_pos < 0) map_data.current_y_pos = 0;
        if(map_data.current_y_pos + SCREEN_HEIGHT > map_data.max_y_) map_data.current_y_pos = map_data.max_y_ - SCREEN_HEIGHT;

        map_x = map_data.current_x_pos;
        map_y = map_data.current_y_pos;
}

void Player::RenderPlayer(SDL_Renderer* des, bool SkeletonIsAttacking, bool bomb)
{
        if(SkeletonIsAttacking || bomb)
        {
                isAttacked = true;
                --HP;
        }
        if(HP <= 0) dead = true;

        SDL_Rect* current_clip;
        int current_frame;

        if(isAttacked)
        {
                isWalking = false;
                current_frame = TAKEHIT_FRAMES;
                current_clip = &Takehit_clip[takehit_frame / 30];

                PlayerBox.w = current_clip->w / 5;
                PlayerBox.h = current_clip->h / 5;

                takehit_frame++;
                if(takehit_frame >= current_frame * 30)
                {
                        takehit_frame = 0;
                        isAttacked = false;
                }
                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else if(dead)
        {
                current_frame = DEATH_FRAMES;
                current_clip = &Death_clip[death_frame / 30];

                PlayerBox.w = current_clip->w / 5;
                PlayerBox.h = current_clip->h / 5;

                death_frame++;
                if(death_frame >= current_frame * 30) death_frame = (current_frame - 1) * 60;
                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else if(input_type.attack1)
        {
                current_frame = ATTACK1_FRAMES;
                current_clip = &Attack1_clip[attack1_frame / 30];

                PlayerBox.w = current_clip->w / 5;
                PlayerBox.h = current_clip->h / 5;

                PlayerAttackBox.x = x_pos + ((FlipType == SDL_FLIP_NONE) ? -16 * 2 : - 30 * 2);
                PlayerAttackBox.y = y_pos;
                PlayerAttackBox.w = current_clip->w / 5;
                PlayerAttackBox.h = current_clip->h / 5;

                attack1_frame++;
                if(attack1_frame == 1)
                {
                        isAttacking = true;
                }
                else isAttacking = false;
                if(attack1_frame >= current_frame * 30)
                {
                        attack1_frame = 0;
                        input_type.attack1 = false;
                }
                if(FlipType == SDL_FLIP_HORIZONTAL)
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 30 * 2 - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                        SDL_RenderDrawRect(des, &renderQuad);
                }
                else
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 16 * 2 - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                        SDL_RenderDrawRect(des, &renderQuad);
                }
        }
        else if(input_type.attack2)
        {
                current_frame = ATTACK2_FRAMES;
                current_clip = &Attack2_clip[attack2_frame/ 30];

                PlayerBox.w = current_clip->w / 5;
                PlayerBox.h = current_clip->h / 5;

                PlayerAttackBox.x = x_pos + ((FlipType == SDL_FLIP_NONE) ? - 4 * 2 : - 44 * 2);
                PlayerAttackBox.y = y_pos;
                PlayerAttackBox.w = current_clip->w / 5;
                PlayerAttackBox.h = current_clip->h / 5;

                attack2_frame++;
                if(attack2_frame == 1) isAttacking = true;
                else isAttacking = false;

                if(attack2_frame >= current_frame * 30)
                {
                        attack2_frame = 0;
                        input_type.attack2 = false;
                }

                if(FlipType == SDL_FLIP_HORIZONTAL)
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 44 * 2 - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                }
                else
                {
                        SDL_Rect renderQuad = {PlayerBox.x - 4 * 2 - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
                }
        }
        else if(isWalking)
        {
                current_frame = WALK_FRAMES;
                current_clip = &Walk_clip[run_frame / 30];

                PlayerBox.w = current_clip->w / 5;
                PlayerBox.h = current_clip->h / 5;

                run_frame++;
                if(run_frame >= current_frame * 30) run_frame = 0;

                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);

        }
        else
        {
                current_frame = IDLE_FRAMES;
                current_clip = &Idle_clip[idle_frame / 30];

                PlayerBox.w = current_clip->w / 5;
                PlayerBox.h = current_clip->h / 5;

                idle_frame++;
                if(idle_frame >= current_frame * 30) idle_frame = 0;

                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
}

void Player::RenderHP(SDL_Renderer* des)
{
        if(!dead)
        {
                SDL_Rect* current_clip;
                current_clip = &HP_clip[HP];
                SDL_Rect renderQuad = {10, 10, current_clip->w / 2, current_clip->h / 2};
                SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        }
}
