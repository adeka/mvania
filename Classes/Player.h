#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Level.h"
#include "Actor.h"
#include "InputManager.h"
#include "cocos2d.h"
#include "InputManager.h"

using namespace std;
USING_NS_CC;

class Player : public Actor, public InputManager
{
  public:
    Player(float x, float y, Level * level);
    void update(float delta);
    InputManager * im;
};

#endif
