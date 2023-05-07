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
        void renderText(SDL_Renderer* screen,const char *text, TTF_Font *font, int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);
        bool CheckCollision(SDL_Rect& a, SDL_Rect& b);
        void Free();
private:
        SDL_Texture* p_object_;
        SDL_Rect mBox;
};

#endif // BASE_OBJECT_H_

