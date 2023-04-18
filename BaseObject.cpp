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
                SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
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
//void BaseObject::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
//{
//	//Set rendering space and render to screen
//	SDL_Rect renderQuad = {mBox.x, mBox.y, mBox.w, mBox.h};
//
//	//Set clip rendering dimensions
//	if( clip != NULL )
//	{
//		renderQuad.w = clip->w;
//		renderQuad.h = clip->h;
//	}
//
//	//Render to screen
//	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );

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
