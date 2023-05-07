#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMap :  public BaseObject
{
public:
        TileMap() {;};
        ~TileMap() {;}
};

class GameMap
{
public:
        GameMap() {;}
        ~GameMap() {;}

        void LoadFileMap(const string& name);
        void LoadTiles(SDL_Renderer* screen);
        void RenderMap(SDL_Renderer* screen);
        Map getMap() {return game_map_;};
        void SetMap(Map& map_data ) {game_map_ = map_data;};

private:
        Map game_map_;
        TileMap tile_map[MAX_TILES];
        SDL_Rect TileBox;
};

#endif // GAME_MAP_H
