#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

#define TILE_SIZE 64

#define MAX_MAP_X 250
#define MAX_MAP_Y 40

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 0;
const int COLOR_KEY_B = 0;

const int RENDER_DRAW_COLOR = 255;

const int QUIT_STATE = 0;
const int PLAY_STATE = 1;
const int GUIDE_STATE = 2;
const int AGAIN_STATE = 3;
const int MENU_STATE = 4;
const int PAUSE_MENU_STATE = 5;
const int GAME_OVER_MENU_STATE = 6;

const int SCREEN_FPS = 120;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

enum OtherSoundEffect
{
    SELECT_BUTTON_SOUND,
    BOOM_SOUND,
    TOTAL_OTHER_SOUND_EFFECT
};

enum BossSoundEffect
{
        Attack_Sound,
        Walk_Sound,
        TakeHit_Sound,
        Total_Boss_Sound_Effect
};

enum SkeletonSoundEffect
{
        ATTACK_SOUND_,
        WALK_SOUND_,
        DEATH_SOUND_,
        BOOM_SOUND_,
        TOTAL_SKELETON_SOUND
};

enum PlayerSoundEffect
{
    ATTACK_SOUND,
    WALK_SOUND,
    TAKE_HIT_SOUND,
    HEALING_SOUND,
    DEATH_SOUND,
    PAUSE_SOUND,
    GET_KEY_SOUND,
    TOTAL_PLAYER_SOUND_EFFECT
};

struct Map
{
        int current_x_pos;
        int current_y_pos;

        int max_x_;
        int max_y_;

        int TileType[MAX_MAP_Y][MAX_MAP_X];
        string file_name_;

};

struct Input
{
        bool left, right, up, down,  attack1, attack2, attack3, take_hit, death;
};

#endif // COMMON_FUNCTION_H_


