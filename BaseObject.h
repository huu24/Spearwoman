#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "CommonFunc.h"

class BaseObject
{
public:
        BaseObject();
        ~BaseObject();

        void SetRect(const int& x, const int& y) {mBox.x = x, mBox.y = y;}
        SDL_Rect GetRect() const {return mBox;}
        SDL_Texture* GetTexture() const {return p_object_;}

        virtual bool LoadImg(string path, SDL_Renderer* screen);
        void Render(SDL_Renderer* des, SDL_Rect* clip = NULL);
        void gRender(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
        bool CheckCollision(SDL_Rect& a, SDL_Rect& b);
        void Free();
protected:
        SDL_Texture* p_object_;
        SDL_Rect mBox;
};

#endif // BASE_OBJECT_H_

