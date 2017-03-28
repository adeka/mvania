#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "Level.h"
#include "TileObject.h"
#include "cocos2d.h"

#include <string>
#include <vector>
USING_NS_CC;

class Actor : public Node
{
public:
    Actor(float x, float y, Level * level);
    ~Actor(){};

    bool hasContactAbove;
    bool hasContactToTheLeft;
    bool hasContactToTheRight;
    bool hasContactBelow;

    bool isJumping;
    float jumpVel;
    float jumpHeight;
    bool forceFalling;
    float yOffset;

    float gravity;
    float maxFallSpeed;

    float xVel;
    float yVel;

    float moveSpeed;
    float friction;

    float dt;
    float step;
    double currentTime;
    double accumulator;
    double lastTickTime;

    bool onSlope;
    float storedY;

    float playerWidth;
    float playerHeight;

    Sprite * sprite;
    Level * level;
    TileObject * currentTile;

    void jump();
    void stopJump();
    void moveLeft();
    void moveRight();
    void checkMapCollisions();
    void calculatePosition();
    void fall();

    void update(float delta);
    void fixedUpdate();
    double getCurrentTimeInSeconds();
    bool rectIntersect(float x, float y, float oWidth, float oHeight, float xTwo, float yTwo, float oTwoWidth, float oTwoHeight);
    map<string, bool> checkCollision(float tileX, float tileY, float tileWidth, float tileHeight);
};
#endif
