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

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 0;
const int COLOR_KEY_B = 0;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE 64

#define MAX_MAP_X 250
#define MAX_MAP_Y 40

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


