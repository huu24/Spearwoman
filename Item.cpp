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
        SDL_Rect* current_clip = &Key_clip[frame / 14];
        frame++;
        if(frame >= KEY_FRAMES * 14) frame = 0;
        SDL_Rect renderQuad = {KeyBox.x - camX, KeyBox.y - camY, KeyBox.w, KeyBox.h};
        SDL_RenderCopyEx(screen, mKeyTexture, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

AllKeys::AllKeys()
{
        Keys.push_back(Key(42*64, 18*64));
        Keys.push_back(Key(111*64, 11*64));
        Keys.push_back(Key(214*64, 6*64));
        Keys.push_back(Key(143*64, 29*64));
        Keys.push_back(Key(230*64, 26*64));
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

bool AllKeys::touchKeys()
{
        for(int i = 0; i < Keys.size(); i++)
        {
                if(Keys[i].touchKeys()) return true;
        }
        return false;
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

        SDL_Rect renderQuad = {HpBox.x - camX, HpBox.y - camY, HpBox.w , HpBox.h };
        SDL_RenderCopyEx(screen, mHPTexture, &current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

AllHps::AllHps()
{
        HPs.push_back(HP(31*64, 3*64));
        HPs.push_back(HP(111*64, 9*64));
        HPs.push_back(HP(228*64, 9*64));
        HPs.push_back(HP(139*64, 29*64));
        HPs.push_back(HP(89*64, 34*64));

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

bool AllHps::touchBloodJars()
{
        for(int i = 0; i < HPs.size(); i++)
        {
                if(HPs[i].touchBloodJars()) return true;
        }
        return false;
}

void AllHps::RenderHP(SDL_Renderer* screen, SDL_Texture* mHPTexture, int camX, int camY)
{
        for(int i = 0; i < HPs.size(); i++)
        {
                HPs[i].RenderHP(screen, mHPTexture, camX, camY);
        }
}

Door::Door()
{
        DoorBox.x = 229 * 64;
        DoorBox.y = 8 * 64;
        DoorBox.w = 64;
        DoorBox.h = 128;
        open = false;
}

Door::~Door()
{

}

void Door::set_clips()
{
        int x = 0;
        for(int i = 0; i < DOOR_FRAMES; i++)
        {
                Door_clip[i] = {x, 0, 128, 128};
                x += 128;
        }
        x = 0;
}

void Door::Check(SDL_Rect PlayerBox, int NumberOfKeys)
{
        if(BaseObject::CheckCollision(PlayerBox, DoorBox) && NumberOfKeys == 5)
        {
                open = true;
        }
}

void Door::RenderDoor(SDL_Renderer* screen, SDL_Texture* mDoorTexture, int camX, int camY)
{
        int doorStatus;
        if(open) doorStatus = 1;
        else doorStatus = 0;
        SDL_Rect* current_clip = &Door_clip[doorStatus];
        SDL_Rect renderQuad = {DoorBox.x - camX, DoorBox.y - camY, DoorBox.w, DoorBox.h};
        SDL_RenderCopyEx(screen, mDoorTexture, current_clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}
