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
        bool touchKeys() {return collide;}
        void RenderKey(SDL_Renderer* screen, SDL_Texture* mKeyTexture, SDL_Rect PlayerBox , int camX, int camY);

private:
        int KEY_FRAMES = 12;
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
        bool touchKeys();
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
        bool touchBloodJars() {return collide;}
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
        bool touchBloodJars();
        void RenderHP(SDL_Renderer* screen, SDL_Texture* mHPTexture, int camX, int camY);
private:
        vector <HP> HPs;
};

class Door : public BaseObject
{
public:
        Door();
        ~Door();

        void set_clips();
        void Check(SDL_Rect PlayerBox, int NumberOfKeys);
        bool DoorOpen() {return open;}
        SDL_Rect GetDoorBox() {return DoorBox;}
        void RenderDoor(SDL_Renderer* screen, SDL_Texture* mDoorTexture, int camX, int camY);
private:
        int DOOR_FRAMES = 2;
        bool open;
        SDL_Rect DoorBox;
        SDL_Rect Door_clip[2];
};

#endif // ITEM_H
