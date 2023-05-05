#include "game_map.h"

void GameMap::LoadFileMap(const string& name)
{
        std::ifstream file(name.c_str()); // mở file với tên được truyền vào hàm

        if (file)   // nếu file mở thành công
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
                                                game_map_.max_x_ = j;
                                        }
                                        if (i > game_map_.max_y_)
                                        {
                                                game_map_.max_y_ = i;
                                        }
                                }
                        }
                }
        }
        else
        {
                std::cout << "Can not read file!\n";
                return;
        }

        // tính toán kích thước của bản đồ dựa trên số lượng ô vuông
        game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
        game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

        // thiết lập vị trí bắt đầu của bản đồ
        game_map_.current_x_pos = 0;
        game_map_.current_y_pos = 0;

        // gán tên file cho biến file_name_
        game_map_.file_name_ = name;

        file.close(); // đóng file
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

                tile_mat[i].LoadImg(file_img, screen);
        }
}

void GameMap::RenderMap(SDL_Renderer* screen)
{
        // tinh vi tri ban dau cua map tren cua so game(o thu may)
        int map_x = game_map_.current_x_pos / TILE_SIZE;
        int x1 = (game_map_.current_x_pos % TILE_SIZE) * (-1);
        int x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
        int map_y = game_map_.current_y_pos / TILE_SIZE;
        int y1 = (game_map_.current_y_pos % TILE_SIZE) * (-1);
        int y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

        // render tung o TileType len cua so game
        for(int i = y1; i < y2; i += TILE_SIZE)
        {
                map_x = game_map_.current_x_pos / TILE_SIZE;
                for(int j = x1; j < x2; j += TILE_SIZE)
                {
                //lay gia tri cua o TileType tai vi tri hien tai tren map
                int value = game_map_.TileType[map_y][map_x];

                //neu o TileType co gia tri > 0 (tuc la o TileType khong rong)
                if(value > -1)
                {
                        //dat vi tri va render len cua so game
                        tile_mat[value].SetRect(j, i);
                        tile_mat[value].Render(screen);
                }
                map_x++;
                }
                map_y++;
        }
}
