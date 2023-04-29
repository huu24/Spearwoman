#include "Player.h"

Player::Player()
{
        HP = 5;
        ENERGY = 3;
        attack1_frame = attack2_frame = idle_frame = takehit_frame = run_frame = death_frame = 0;
        VelX = VelY = 0.0;
        xPos = 235 * TILE_SIZE;
        yPos = 500.0;
        map_x = map_y = 0;
        input_type.left = input_type.right = input_type.up = input_type.down = input_type.attack1 = input_type.attack2 = input_type.take_hit
        = input_type.death = isAttacking  = isWalking = isAttacked = dead = false;
        FlipType = SDL_FLIP_NONE;
        PlayerAttackBox.w = PlayerAttackBox.h = 0;
}

Player::~Player()
{

}

void Player::set_clips()
{
        int x = 0;
        for(int i = 0; i < IDLE_FRAMES; i++)
        {
                Idle_clip[i] = {x, 0, 32*8, 48*8};
                x += 32*8;
        }
        x = 0;
        for(int i = 0; i < WALK_FRAMES; i++)
        {
                Walk_clip[i] = {x, 49*8, 32*8, 48*8};
                x += 32*8;
        }
        x = 0;
        for(int i = 0; i < ATTACK1_FRAMES; i++)
        {
                Attack1_clip[i] = {x, 97*8, 80*8, 48*8};
                x += 80*8;
        }
        x = 0;
        for(int i = 0; i < ATTACK2_FRAMES; i++)
        {
                Attack2_clip[i] = {x, 144*8, 80*8, 48*8};
                x += 80*8;
        }
        x = 0;
        for(int i = 0; i < TAKEHIT_FRAMES; i++)
        {
                Takehit_clip[i] = {x, 193*8, 48*8, 48*8};
                x += 48*8;
        }
        x = 0;
        for(int i = 0; i < DEATH_FRAMES; i++)
        {
                Death_clip[i] = {x, 241*8, 48*8, 48*8};
                x += 48*8;
        }
        x = 0;
        for(int i = 1; i <= 5; i++)
        {
                HP_clip[i] = {x, 348*8, 49*8, 8*8};
                x += 49*8;
        }
        x = 0;
        for(int i = 0; i < 4; i++)
        {
                Energy_clip[i] = {x, 356*8, 48*8, 9*8};
                x += 48*8;
        }
        x = 0;
        PlayerBox.h = 96;
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
        if(dead || isAttacked || input_type.attack1 || input_type.attack2) return;
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

        xPos += VelX;
        yPos += VelY;
        CollisionWithMap(map_data);
        SetCamera(map_data);

        if(xPos <= 0)
        {
                xPos = 0;
        }
        else if(xPos + PlayerBox.w > map_data.max_x_)
        {
                xPos = map_data.max_x_ - PlayerBox.w;
        }
        if(yPos < 0)
        {
                yPos = 0;
        }
        else if(yPos + PlayerBox.h > map_data.max_y_)
        {
                yPos = map_data.max_y_ - PlayerBox.h;
        }

        PlayerBox.x = xPos;
        PlayerBox.y = yPos;
}

void Player::CollisionWithMap(Map& map_data)
{
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check horizontal

        int min_height = min(TILE_SIZE, PlayerBox.h);

        x1 = (xPos) / TILE_SIZE;
        x2 = (xPos + PlayerBox.w) / TILE_SIZE;

        y1 = (yPos + PlayerBox.h - min_height) / TILE_SIZE;
        y2 = (yPos + PlayerBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelX > 0)
                {
                        if(map_data.TileType[y1][x2] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                xPos -= VelX;
                        }
                }
                else if(VelX < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y2][x1] >= 4)
                        {
                                xPos -= VelX;
                        }
                }
        }

        //check_vertical
        x1 = xPos / TILE_SIZE;
        x2 = (xPos + PlayerBox.w) / TILE_SIZE;

        y1 = (yPos + PlayerBox.h - min_height) / TILE_SIZE;
        y2 = (yPos + PlayerBox.h) / TILE_SIZE;

        if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
        {
                if(VelY > 0)
                {
                        if(map_data.TileType[y2][x1] >= 4 || map_data.TileType[y2][x2] >= 4)
                        {
                                yPos -= VelY;
                        }
                }
                else if(VelY < 0)
                {
                        if(map_data.TileType[y1][x1] >= 4 || map_data.TileType[y1][x2] >= 4)
                        {
                                yPos -= VelY;
                        }
                }
        }
}

void Player::SetCamera(Map& map_data)
{
        map_data.current_x_pos = (xPos) - SCREEN_WIDTH / 2;
        map_data.current_y_pos = (yPos) - SCREEN_HEIGHT / 2;

        if(map_data.current_x_pos < 0) map_data.current_x_pos = 0;
        if(map_data.current_x_pos + SCREEN_WIDTH > map_data.max_x_) map_data.current_x_pos = map_data.max_x_ -  SCREEN_WIDTH;

        if(map_data.current_y_pos < 0) map_data.current_y_pos = 0;
        if(map_data.current_y_pos + SCREEN_HEIGHT > map_data.max_y_) map_data.current_y_pos = map_data.max_y_ - SCREEN_HEIGHT;

        map_x = map_data.current_x_pos;
        map_y = map_data.current_y_pos;
}

void Player::RenderPlayer(SDL_Renderer* screen, SDL_Texture* mPlayerTexture, bool SkeletonIsAttacking, bool bomb, bool BossIsAttacking)
{
        if(SkeletonIsAttacking || bomb || BossIsAttacking)
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

                PlayerBox.w = current_clip->w / 4;
                PlayerBox.h = current_clip->h / 4;

                takehit_frame++;
                if(takehit_frame >= current_frame * 30)
                {
                        takehit_frame = 0;
                        isAttacked = false;
                }
                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else if(dead)
        {
                current_frame = DEATH_FRAMES;
                current_clip = &Death_clip[death_frame / 30];

                PlayerBox.w = current_clip->w / 4;
                PlayerBox.h = current_clip->h / 4;

                death_frame++;
                if(death_frame >= current_frame * 30) death_frame = (current_frame - 1) * 60;
                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
        else if(input_type.attack1)
        {
                current_frame = ATTACK1_FRAMES;
                current_clip = &Attack1_clip[attack1_frame / 30];

                PlayerAttackBox.x = xPos + ((FlipType == SDL_FLIP_NONE) ? -16 * 2 : - 30 * 2);
                PlayerAttackBox.y = yPos;
                PlayerAttackBox.w = current_clip->w / 4;
                PlayerAttackBox.h = current_clip->h / 4;

                attack1_frame++;
                if(attack1_frame == 1)
                {
                        isAttacking = true;
                        --ENERGY;
                }
                else isAttacking = false;
                if(attack1_frame >= current_frame * 30)
                {
                        attack1_frame = 0;
                        input_type.attack1 = false;
                }
                        SDL_Rect renderQuad = {PlayerAttackBox.x - map_x, PlayerAttackBox.y - map_y, PlayerAttackBox.w, PlayerAttackBox.h};
                        SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);
                        SDL_RenderDrawRect(screen, &renderQuad);
        }
        else if(input_type.attack2)
        {
                current_frame = ATTACK2_FRAMES;
                current_clip = &Attack2_clip[attack2_frame/ 30];

                PlayerAttackBox.x = xPos + ((FlipType == SDL_FLIP_NONE) ? - 4 * 2 : - 44 * 2);
                PlayerAttackBox.y = yPos;
                PlayerAttackBox.w = current_clip->w / 4;
                PlayerAttackBox.h = current_clip->h / 4;

                attack2_frame++;
                if(attack2_frame == 1 || attack2_frame == 60)
                {
                        isAttacking = true;
                        --ENERGY;
                }
                else isAttacking = false;

                if(attack2_frame >= current_frame * 30)
                {
                        attack2_frame = 0;
                        input_type.attack2 = false;
                }
                SDL_Rect renderQuad = {PlayerAttackBox.x - map_x, PlayerAttackBox.y - map_y, PlayerAttackBox.w, PlayerAttackBox.h};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);
                SDL_RenderDrawRect(screen, &renderQuad);

        }
        else if(isWalking)
        {
                current_frame = WALK_FRAMES;
                current_clip = &Walk_clip[run_frame / 30];

                PlayerBox.w = current_clip->w / 4;
                PlayerBox.h = current_clip->h / 4;

                run_frame++;
                if(run_frame >= current_frame * 30) run_frame = 0;

                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);

        }
        else
        {
                current_frame = IDLE_FRAMES;
                current_clip = &Idle_clip[idle_frame / 30];

                PlayerBox.w = current_clip->w / 4;
                PlayerBox.h = current_clip->h / 4;

                idle_frame++;
                if(idle_frame >= current_frame * 30) idle_frame = 0;

                SDL_Rect renderQuad = {PlayerBox.x - map_x, PlayerBox.y - map_y, PlayerBox.w, PlayerBox.h};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, FlipType);
        }
}

void Player::RenderHP(SDL_Renderer* screen, SDL_Texture* mPlayerTexture)
{
        if(dead) return;
        if(ENERGY <= 0)
        {
                ENERGY = 0;
        }

                SDL_Rect* current_clip;
                current_clip = &HP_clip[HP];
                SDL_Rect renderQuad = {10, 10, current_clip->w / 2, current_clip->h / 2};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);

                SDL_Rect* current_clip1;
                current_clip1 = &Energy_clip[ENERGY];
                SDL_Rect renderQuad1 = {10, 50, 480 / 2, 90 / 2};
                SDL_RenderCopyEx(screen, mPlayerTexture, current_clip1, &renderQuad1, 0.0, NULL, SDL_FLIP_NONE);
//        }
}
