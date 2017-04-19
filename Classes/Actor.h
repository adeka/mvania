#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "Level.h"
#include "TileObject.h"
#include "cocos2d.h"
#include "SAT.h"

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
    bool hasContactPeek;

    bool isJumping;
    float jumpVel;
    float jumpHeight;
    bool forceFalling;

    float gravity;
    float maxFallSpeed;

    float yVel;

    float moveSpeed;
    float friction;

    int direction;
    float dt;
    float step;
    double currentTime;
    double accumulator;
    double lastTickTime;

    float playerWidth;
    float playerHeight;

    DrawNode * drawNode;

    Vec2 moveVector;
    Vec2 velocity;

    Sprite * sprite;
    Level * level;
    TileObject * currentTile;

    void jump();
    void stopJump();
    void moveLeft();
    void moveRight();
    void checkMapCollisions();
    void calculatePosition();
    void SATCollision();
    void fall();

    vector<TileObject* > getBoundingTiles(int size, string layer);
    int coordToIndex(int x, int y);

    SAT sat;
    polygon collider;

    void update(float delta);
    void fixedUpdate();
    double getCurrentTimeInSeconds();
    bool rectIntersect(float x, float y, float oWidth, float oHeight, float xTwo, float yTwo, float oTwoWidth, float oTwoHeight);
    map<string, bool> checkCollision(TileObject * tile);
};
#endif
