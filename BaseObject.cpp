#include "BaseObject.h"

BaseObject::BaseObject()
{
        p_object_ = NULL;
        mBox.x = 0;
        mBox.y = 0;
        mBox.w = 0;
        mBox.h = 0;
}
BaseObject::~BaseObject()
{
        Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
        SDL_Texture* new_texture = NULL;
        SDL_Surface* load_surface = IMG_Load(path.c_str());
        if(load_surface != NULL)
        {
                SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 7, 7, 7));
                new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
                if(new_texture != NULL)
                {
                        mBox.w = load_surface->w;
                        mBox.h = load_surface->h;
                }
                SDL_FreeSurface(load_surface);
        }
        p_object_ = new_texture;
        return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, SDL_Rect* clip)
{
        SDL_Rect renderquad = {mBox.x, mBox.y, mBox.w, mBox.h};
        SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
        if(p_object_ != NULL)
        {
                SDL_DestroyTexture(p_object_);
                p_object_ = NULL;
                mBox.w = 0;
                mBox.h = 0;
        }
}

bool BaseObject::CheckCollision(SDL_Rect& a, SDL_Rect& b)
{
        int x, y, u, v;
        x = max(a.x, b.x);
        y = max(a.y, b.y);
        u = min(a.x + a.w, b.x + b.w);
        v = min(a.y + a.h, b.y + b.h);
        if (x < u && y < v) return true;
        return false;
}
