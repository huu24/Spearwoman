#include "game_map.h"

void GameMap::LoadFileMap(const string& name)
{
    std::ifstream file(name.c_str());

    if (file)
    {
        game_map_.max_x_ = 0;
        game_map_.max_y_ = 0;
        for (int i = 0; i < MAX_MAP_Y; i++)
        {
            for (int j = 0; j < MAX_MAP_X; j++)
            {
                file >> game_map_.TileType[i][j];
                int value = game_map_.TileType[i][j];
                if (value > -1)
                {
                    if (j > game_map_.max_x_)
                    {
                        game_map_.max_x_ = j;  //cap nhat gia tri lon nhat cua x
                    }
                    if (i > game_map_.max_y_)
                    {
                        game_map_.max_y_ = i;  // cap nhat gia tri lon nhat cua y
                    }
                }
            }
        }
    }
    else
    {
        cout << "Can not read file!\n";
        return;
    }

    // kich thuoc ban do
    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    // vi tri bat dau
    game_map_.current_x_pos = 0;
    game_map_.current_y_pos = 0;

    file.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    string file_img;

    for(int i = 0; i < MAX_TILES; i++)
    {
        file_img = "map\\" + to_string(i) + ".png";
        ifstream file(file_img, ios::binary);
        if(!file.is_open())
        {
            continue;
        }
        file.close();

        tile_map[i].LoadImg(file_img, screen);  // tai hinh anh va luu vao mang tile_map
    }
}

void GameMap::RenderMap(SDL_Renderer* screen)
{
    //tinh toan vi tri ban dau cua ban do tren cua so game
    int map_x = game_map_.current_x_pos / TILE_SIZE;
    int x1 = (game_map_.current_x_pos % TILE_SIZE) * (-1);
    int x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    int map_y = game_map_.current_y_pos / TILE_SIZE;
    int y1 = (game_map_.current_y_pos % TILE_SIZE) * (-1);
    int y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    // render tung o len ban do
    for(int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.current_x_pos / TILE_SIZE;
        for(int j = x1; j < x2; j += TILE_SIZE)
        {
            // lay gia tri o hien tai
            int value = game_map_.TileType[map_y][map_x];

            if(value > -1)
            {
                // dat vi tri va render len man hinh
                tile_map[value].SetRect(j, i);
                tile_map[value].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
