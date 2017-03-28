#include "Actor.h"

#include <algorithm>

const float kSecondsPerUpdate = 1.0f / 60.0f;

Actor::Actor(float x, float y, Level * level) {
    onSlope = false;
    storedY = 0.0f;

    gravity = 22.5f;
    friction = 0.0;
    xVel = 0.0f;
    yVel = 0.0f;
    dt = 0.0f;
    maxFallSpeed = -7.0f;
    step = 0.01f;
    isJumping = false;
    jumpVel = 0.0f;
    jumpHeight = 5.5f;
    moveSpeed = 1.75f;
    forceFalling = false;
    yOffset = 0.0f;

    playerWidth = 16.0f;
    playerHeight = 24.0f;

    sprite = Sprite::create("assets/alucard.png");
    this->addChild(sprite);
    sprite->setPosition(8.0f,24.0f);

    this->setPosition(x, y);
    this->level = level;

    this->scheduleUpdate();
}
void Actor::update(float delta) {
    // get current time double
    currentTime = getCurrentTimeInSeconds();
    if (!lastTickTime)
    lastTickTime = currentTime;

    // determine the amount of time elapsed since our last update
    double frameTime = currentTime - lastTickTime;
    accumulator += frameTime;

    // update the world with the same seconds per update
    while (accumulator > kSecondsPerUpdate)
    {
        accumulator -= kSecondsPerUpdate;

        // perform a single step of the physics simulation
        this->fixedUpdate();
    }
    lastTickTime = currentTime;
}

void Actor::fixedUpdate() {
    calculatePosition();
    dt += step;
    checkMapCollisions();
    if(this->isJumping && !this->hasContactAbove) {
        jumpVel = min(jumpVel += .65f, jumpHeight);
    } else {
        isJumping = false;
    }
    forceFalling = false;
}
void Actor::calculatePosition() {
    //calculate positions
    Vec2 pos = this->getPosition();
    float newYVel = max((jumpVel - gravity * dt), maxFallSpeed);
    if (!onSlope) {
        this->setPosition(pos.x + xVel, pos.y + newYVel);
    } else {
        // CCLOG("%f", storedY);
        // CCLOG("%f", yOffset);
        this->setPosition(pos.x + xVel, storedY + yOffset);
    }
    yVel = newYVel;
    xVel*= friction;
}

void Actor::checkMapCollisions() {
    this->hasContactBelow = false;
    this->hasContactAbove = false;
    this->hasContactToTheLeft = false;
    this->hasContactToTheRight = false;
    //collisions
    // onSlope = false;

    map<string, bool> contacts;
    for (auto& tile : level->tileMap["wall"])
    {
        float tileSize = 16.0f;
        float thisX = this->getPosition().x; // + 8.0f;
        float thisY = this->getPosition().y;
        contacts = checkCollision(tile->getPosition().x, tile->getPosition().y, tileSize, tileSize);
        if(tile->id == 46){
            // if(contacts["down"] || contacts["up"] || contacts["left"] || contacts["right"]){
            // if(contacts["down"]){
            if (rectIntersect(thisX, thisY + yVel,
                              playerWidth, playerHeight,
                              tile->getPosition().x, tile->getPosition().y,
                              tileSize, tileSize)
            ) {
                // && thisY <= tile->getPosition().y + tileSize - 3.0f
                if(!onSlope) {
                    storedY = tile->getPosition().y;
                    currentTile = tile;
                    // CCLOG("contact with slope");
                    onSlope = true;

                    // moveSpeed = 1.75f / sqrt(2.0f);
                }
                if(onSlope && tile == currentTile){
                    float diff = max(thisX - tile->getPosition().x, 0.0f);
                    float ratio = diff / tileSize;//- 0.3125f;
                    float value = (ratio - 1.0f) * -1.0f;
                    yOffset = value * tileSize;

                    CCLOG("%f", value);
                    // CCLOG("SLOPING");

                    // if(value >= 1.0f || value <= 0.16f){
                    //     onSlope = false;
                    //     CCLOG("END OF SLOPE");
                    //     currentTile = NULL;
                    // }
                }



                // if(value >= 1.0f){
                //     onSlope = false;
                //
                // }
                // CCLOG("%f", ratio);



                // if (rectIntersect(thisX, thisY + yVel,
                //                   playerWidth, playerHeight,
                //                   tile->getPosition().x, tile->getPosition().y,
                //                   tileSize, yOffset)
                // ) {
                //     this->hasContactBelow = true;
                //     jumpVel = 0.0f;
                //     isJumping = false;
                //     dt = 0.0f;
                //     storedY = 120.0f;
                //
                //     moveSpeed = 1.75f / sqrt(2.0f);
                //     gravity = 50.0f;
                // }
            } else if(tile == currentTile) {
                currentTile = NULL;
                yOffset = 0.0f;
                onSlope = false;
            }
        }
        if(tile->id == 4 && !onSlope){
            if(contacts["down"]) {
                moveSpeed = 1.75f;
                // CCLOG("%i", tile->id);
                this->hasContactBelow = true;
                jumpVel = 0.0f;
                isJumping = false;
                dt = 0.0f;
                yOffset = 0.0f;
                onSlope = false;
            }
            if(contacts["up"]) {
                moveSpeed = 1.75f;
                this->hasContactAbove = true;
                dt = 0.0f;
                jumpVel = 0.0f;
                onSlope = false;
            }
            if(contacts["left"]) {
                moveSpeed = 1.75f;
                this->hasContactToTheLeft = true;
                xVel = 0.0f;
                onSlope = false;
            }
            if(contacts["right"]) {
                moveSpeed = 1.75f;
                this->hasContactToTheRight = true;
                xVel = 0.0f;
                onSlope = false;
            }
        }
    }
    for (auto& tile : level->tileMap["oneway"])
    {
        float tileSize = 16.0f;
        contacts = checkCollision(tile->getPosition().x, tile->getPosition().y, tileSize, tileSize);
        if(contacts["down"] && !contacts["up"] && !contacts["left"] && !contacts["right"] && !forceFalling) {
            this->hasContactBelow = true;
            jumpVel = 0.0f;
            isJumping = false;
            dt = 0.0f;
        }
    }
}
map<string, bool> Actor::checkCollision(float tileX, float tileY, float tileWidth, float tileHeight) {
    float dirOffset = 5.0f;
    float thisX = this->getPosition().x;
    float thisY = this->getPosition().y;
    float heightOffset = 0.3f;
    map<string, bool> contacts = {
        {"down", false},
        {"up", false},
        {"left", false},
        {"right", false}
    };
    if (rectIntersect(thisX, thisY + yVel, playerWidth, playerHeight, tileX, tileY, tileWidth, tileHeight)) {
        contacts["down"] = true;
    }
    if (rectIntersect(thisX, thisY + playerHeight + jumpVel*2.0f, playerWidth, playerHeight/1.5f, tileX, tileY, tileWidth, tileHeight)) {
        contacts["up"] = true;
    }
    if (rectIntersect(thisX + xVel - dirOffset, thisY + heightOffset, playerWidth, playerHeight*2, tileX, tileY, tileWidth, tileHeight)) {
        contacts["left"] = true;
    }
    if (rectIntersect(thisX + xVel + dirOffset, thisY + heightOffset, playerWidth, playerHeight*2, tileX, tileY, tileWidth, tileHeight)) {
        contacts["right"] = true;
    }
    return contacts;
}
void Actor::moveRight() {
    if (!this->hasContactToTheRight) {
        xVel = moveSpeed;
    }
}

void Actor::moveLeft() {
    if (!this->hasContactToTheLeft) {
        xVel = -moveSpeed;
    }
}
void Actor::jump() {
    this->onSlope = false;

    if (!this->isJumping && !this->hasContactAbove && this->hasContactBelow) {
        this->isJumping = true;
        jumpVel++;
    }
}

void Actor::fall() {
    this->forceFalling = true;
}
void Actor::stopJump() {
    if(this->isJumping) {
        this->isJumping = false;
    }
}
bool Actor::rectIntersect(float x, float y, float oWidth, float oHeight, float xTwo, float yTwo, float oTwoWidth, float oTwoHeight)
{
    if( floor(x+oWidth) < xTwo || x > floor(xTwo+oTwoWidth) ) return false;
    if( floor(y+oHeight) < yTwo || y > floor(yTwo+oTwoHeight) ) return false;
    return true;
}

double Actor::getCurrentTimeInSeconds()
{
    static struct timeval currentTime;
    gettimeofday(&currentTime, nullptr);
    return (currentTime.tv_sec) + (currentTime.tv_usec / 1000000.0);
}
