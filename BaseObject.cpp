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

bool BaseObject::LoadImg(string path, SDL_Renderer* screen)
{
        SDL_Texture* new_texture = NULL;
        SDL_Surface* load_surface = IMG_Load(path.c_str());
        if(load_surface != NULL)
        {
                SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 10, 10, 10));
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

void BaseObject::renderText(SDL_Renderer* screen, const char *text, TTF_Font *font, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
        SDL_Color textColor = {r, g, b, a};
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
        if (textSurface == NULL)
        {
                printf("Failed to create text surface, error: %s\n", TTF_GetError());
                return;
        }
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
        if (textTexture == NULL)
        {
                printf("Failed to create texture, error: %s\n", SDL_GetError());
                return;
        }
        SDL_Rect textRect = {x, y, 0, 0};
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h); // lấy kích thước của texture
        SDL_RenderCopy(screen, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
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
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;

        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;

        if( bottomA <= topB )
        {
                return false;
        }

        if( topA >= bottomB )
        {
                return false;
        }

        if( rightA <= leftB )
        {
                return false;
        }

        if( leftA >= rightB )
        {
                return false;
        }

    return true;
}
