#ifndef ITEM_H
#define ITEM_H

#include "CommonFunc.h"
#include "BaseObject.h"

class Key : public BaseObject
{
public:
        Key(float x, float y);
        ~Key();

        void set_clips();
        void Check( SDL_Rect PlayerBox);
        int countkeys() {return yourkeys;}
        void RenderKey(SDL_Renderer* screen, SDL_Texture* mKeyTexture, SDL_Rect PlayerBox , int camX, int camY);

private:
        const int KEY_FRAMES = 12;
        SDL_Rect Key_clip[12];
        SDL_Rect KeyBox;
        int frame;
        float x_pos, y_pos;
        bool collide;
        int yourkeys;
};

class AllKeys
{
public:
        AllKeys();
        ~AllKeys();

        void set_clips();
        void Check(SDL_Rect PlayerBox);
        int countkeys();
        void RenderKey(SDL_Renderer* screen, SDL_Texture* mKeyTexture, SDL_Rect PlayerBox, int camX, int camY);
private:
        vector <Key> Keys;
};

class HP : public BaseObject
{
public:
        HP(float x, float y);
        ~HP();

        void Check(SDL_Rect PlayerBox);
        int countBloodJars() {return YourBloodJars;}
        void RenderHP(SDL_Renderer* screen, SDL_Texture* mHPTexture, int camX, int camY);

private:
        SDL_Rect HpBox;
        float x_pos, y_pos;
        int YourBloodJars;
        bool collide;
};

class AllHps
{
public:
        AllHps();
        ~AllHps();

        void Check(SDL_Rect PlayerBox);
        int countBloodJars();
        void RenderHP(SDL_Renderer* screen, SDL_Texture* mHPTexture, int camX, int camY);
private:
        vector <HP> HPs;
};

#endif // ITEM_H
