#include "Item.h"

Key::Key(float x, float y)
{
        collide = false;
        KeyBox.x = x;
        KeyBox.y = y;
        KeyBox.w = 48;
        KeyBox.h = 48;
        frame = 0;
        yourkeys = 0;
}

Key::~Key()
{

}

void Key::set_clips()
{
        int x = 0;
        for(int i = 0; i < KEY_FRAMES; i++)
        {
                Key_clip[i] = {x, 0, 32, 32};
                x += 32;
        }
        x = 0;
}

void Key::Check(SDL_Rect PlayerBox)
{
        if(BaseObject::CheckCollision(PlayerBox, KeyBox))
        {
                collide = true;
        }
        else collide = false;
}


void Key::RenderKey(SDL_Renderer* screen, SDL_Texture* mKeyTexture, SDL_Rect PlayerBox , int camX, int camY)
{
        if(collide)
        {
                KeyBox.x = KeyBox.y = KeyBox.w = KeyBox.h = 0;
                yourkeys++;
                return;
        }
        SDL_Rect* current_clip = &Key_clip[frame / 60];
        frame++;
        if(frame >= KEY_FRAMES * 60) frame = 0;
        SDL_Rect renderQuad = {KeyBox.x - camX, KeyBox.y - camY, KeyBox.w, KeyBox.h};
        SDL_RenderCopyEx(screen, mKeyTexture, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
        SDL_RenderDrawRect(screen, &renderQuad);
}

AllKeys::AllKeys()
{
        Keys.push_back(Key(500, 100));
        Keys.push_back(Key(300, 200));
        Keys.push_back(Key(200, 300));
}

AllKeys::~AllKeys()
{

}

void AllKeys::set_clips()
{
        for(int i = 0; i < Keys.size(); i++)
        {
                Keys[i].set_clips();
        }
}
void AllKeys::Check(SDL_Rect Playerbox)
{
        for(int i = 0; i < Keys.size(); i++)
        {
                Keys[i].Check(Playerbox);
        }
}

int AllKeys::countkeys()
{
        int tmp = 0;
        for(int i = 0; i < Keys.size(); i++)
        {
                tmp += Keys[i].countkeys();
        }
        return tmp;
}

void AllKeys::RenderKey(SDL_Renderer* screen, SDL_Texture* mKeyTexture, SDL_Rect PlayerBox , int camX, int camY)
{
        for(int i = 0; i < Keys.size(); i++)
        {
                Keys[i].RenderKey(screen, mKeyTexture, PlayerBox, camX, camY);
        }
}


HP::HP(float x, float y)
{
        HpBox.x = x;
        HpBox.y = y;
        HpBox.w = 40;
        HpBox.h = 52;
        YourBloodJars = 0;
        collide =  false;
}

HP::~HP()
{

}

void HP::Check(SDL_Rect PlayerBox)
{
        if(BaseObject::CheckCollision(PlayerBox, HpBox))
        {
                collide = true;
        }
        else collide = false;
}

void HP::RenderHP(SDL_Renderer* screen, SDL_Texture* mHPTexture, int camX, int camY)
{
        if(collide)
        {
                ++YourBloodJars;
                HpBox.x = HpBox.y = HpBox.w = HpBox.h = 0;
                return;
        }
        SDL_Rect current_clip = {0, 0, 40, 52};

        SDL_Rect renderQuad = {HpBox.x - camX, HpBox.y - camY, HpBox.w * 2 / 3, HpBox.h * 2 / 3};
        SDL_RenderCopyEx(screen, mHPTexture, &current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

AllHps::AllHps()
{
        HPs.push_back(HP(300, 400));
        HPs.push_back(HP(400, 500));
        HPs.push_back(HP(500, 600));
}

AllHps::~AllHps()
{

}

void AllHps::Check(SDL_Rect PlayerBox)
{
        for(int i = 0; i < HPs.size(); i++)
        {
                HPs[i].Check(PlayerBox);
        }
}

int AllHps::countBloodJars()
{
        int tmp = 0;
        for(int i = 0; i < HPs.size(); i++)
        {
                tmp += HPs[i].countBloodJars();
        }
        return tmp;
}

void AllHps::RenderHP(SDL_Renderer* screen, SDL_Texture* mHPTexture, int camX, int camY)
{
        for(int i = 0; i < HPs.size(); i++)
        {
                HPs[i].RenderHP(screen, mHPTexture, camX, camY);
        }
}
