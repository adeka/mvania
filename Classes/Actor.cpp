#include "Actor.h"

const float kSecondsPerUpdate = 1.0f / 60.0f;

Actor::Actor(float x, float y, Level * level) {
    moveVector = Vec2(1.0f,0.0f);
    velocity = Vec2(0.0f,0.0f);

    gravity = 22.5f;
    friction = 0.0;
    direction = 1;

    dt = 0.0f;
    step = 0.01f;

    isJumping = false;
    jumpVel = 0.0f;
    jumpHeight = 5.5f;

    moveSpeed = 1.75f;

    forceFalling = false;
    maxFallSpeed = -7.0f;

    playerWidth = 16.0f;
    playerHeight = 24.0f;

    sprite = Sprite::create("assets/alucard.png");
    this->addChild(sprite);
    sprite->setPosition(8.0f,24.0f);

    this->setPosition(x, y);
    this->level = level;

    drawNode = DrawNode::create();
    level->addChild(drawNode);

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
    drawNode->clear();
    calculatePosition();
    dt += step;
    SATCollision();

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
    float newYVel = fmax((jumpVel - gravity * dt), maxFallSpeed);
    this->setPosition(pos.x + velocity.x, pos.y + newYVel + velocity.y);
    yVel = newYVel;
    velocity = Vec2(0,0);
}

void Actor::SATCollision() {
    this->hasContactBelow = false;
    this->hasContactAbove = false;
    this->hasContactToTheLeft = false;
    this->hasContactToTheRight = false;
    map<string, bool> contacts;

    auto boundingTiles = this->getBoundingTiles(3, "wall");

    // for (auto& tile : boundingTiles)
    // {
    //     auto p1 = Vec2(tile->minX, tile->minY);
    //     auto p2 = Vec2(tile->minX, tile->maxY);
    //     auto p3 = Vec2(tile->maxX, tile->maxY);
    //     auto p4 = Vec2(tile->maxX, tile->minY);
    //     Vec2 vertices[] = { p1, p2, p3, p4 };
    //     drawNode->drawPolygon(vertices, 4, Color4F(0.0f,1.0f,0.0f,0.25f), 0.5f, Color4F(0.0f,1.0f,0.0f,0.5f));
    // }

    for (auto& tile : boundingTiles)
    {
        contacts = checkCollision(tile);
        if(contacts["down"]) {
            moveVector = tile->moveVector;
            // CCLOG("%f, %f", moveVector.x, moveVector.y);
            this->hasContactBelow = true;
            jumpVel = 0.0f;
            isJumping = false;
            dt = 0.0f;
            this->setPosition(this->getPosition().x, tile->getTop(this->getPosition().x + playerWidth/2.0f));
            break;
        } else {
            moveVector = Vec2(1,0);
        }

        // if(contacts["up"]) {
        //     this->hasContactAbove = true;
        //     dt = 0.0f;
        //     jumpVel = 0.0f;
        // }
        if(contacts["left"]) {
            this->hasContactToTheLeft = true;
        }
        if(contacts["right"]) {
            this->hasContactToTheRight = true;
        }
        if(contacts["up"]) {
          this->hasContactAbove = true;
        }
    }

    // for (auto& tile : level->tileMap["oneway"])
                                      // {
    //     contacts = checkCollision(tile);
    //     if(contacts["down"] && !contacts["up"] && !contacts["left"] && !contacts["right"] && !forceFalling) {
    //         this->hasContactBelow = true;
    //         jumpVel = 0.0f;
    //         isJumping = false;
    //         dt = 0.0f;
    //     }
    // }
}

int Actor::coordToIndex(int x, int y) {
    return ((y-1) * level->MAPWIDTH) + x;
}

vector<TileObject *> Actor::getBoundingTiles(int size, string layer) {
    vector<TileObject *> boundingTiles;

    //player grid x,y position
    int x = floor(this->getPosition().x / 16.0f);
    int y = level->MAPHEIGHT - floor(this->getPosition().y / 16.0f);
    // CCLOG("%f, %f, %i, %i",
    //     this->getPosition().x,
    //     this->getPosition().y,
    //     gridX, gridY
    // );

    // create bounding box
    for (int yOff = 0; yOff < size * 2 + 1; yOff++)
    {
        for (int xOff = 0; xOff < size * 2; xOff++)
        {
            int index = coordToIndex(x - 2 + xOff, y - 4 + yOff);
            auto tile = level->tileMap[layer][index];
            if(tile) {
                boundingTiles.push_back(tile);
            }
        }
    }
    return boundingTiles;
}

void Actor::checkMapCollisions() { }

map<string, bool> Actor::checkCollision(TileObject * tile) {
    float x = this->getPosition().x + playerWidth/2.0f;
    float y = this->getPosition().y;
    float dirOffset = 5.0f;
    float heightOffset = 8.0f;
    float upOffset = 5.0f;
    // if(isJumping) {
    //     heightOffset = 0.0f;
    // }
    float width = 0.1f;
    float height = playerHeight;
    // float aroundSize = 32.0f;

    polygon colliderDown = sat.Polygon(4,
        sat.v(x + velocity.x, y),
        sat.v(x + velocity.x, y + height),
        sat.v(x + velocity.x + width, y + height),
        sat.v(x + velocity.x + width, y)
    );

    float x2 = this->getPosition().x + playerWidth/2.0f - 16.0f;
    // float y2 = this->getPosition().y - 16.0f;
    // polygon colliderAround= sat.Polygon(4,
    //     sat.v(x2, y2),
    //     sat.v(x2, y2 + aroundSize),
    //     sat.v(x2 + aroundSize, y2 + aroundSize),
    //     sat.v(x2 + aroundSize, y2)
    // );

    polygon colliderRight = sat.Polygon(4,
        sat.v(x + velocity.x + dirOffset, y + heightOffset),
        sat.v(x + velocity.x + dirOffset, y + heightOffset + height),
        sat.v(x + velocity.x + dirOffset + width, y + heightOffset + height),
        sat.v(x + velocity.x + dirOffset + width, y + heightOffset)
    );
    polygon colliderLeft = sat.Polygon(4,
        sat.v(x + velocity.x - dirOffset, y + heightOffset),
        sat.v(x + velocity.x - dirOffset, y + heightOffset + height),
        sat.v(x + velocity.x - dirOffset + width, y + heightOffset + height),
        sat.v(x + velocity.x - dirOffset + width, y + heightOffset)
    );
    polygon colliderUp = sat.Polygon(4,
        sat.v(x + velocity.x, y + upOffset),
        sat.v(x + velocity.x, y + height + upOffset),
        sat.v(x + velocity.x + width, y + height + upOffset),
        sat.v(x + velocity.x + width, y + upOffset)
    );

    float yOff = 3.0f;
    float peekSize = 1.0f;
    float peekDistance = 5.0f;

    //pee and move vector
    // Vec2 mv = Vec2(moveVector.x, moveVector.y) * moveSpeed * peekDistance * direction;

    //peek verts
    // auto p1 = Vec2(x + mv.x, y + mv.y + yOff);
    // auto p2 = Vec2(x + mv.x, y + mv.y + peekSize + yOff);
    // auto p3 = Vec2(x + mv.x + peekSize, y + mv.y + peekSize + yOff);
    // auto p4 = Vec2(x + mv.x + peekSize, y + mv.y + yOff);

    //peek poly
    // polygon peek = sat.Polygon(4,
    //     sat.v(p1.x, p1.y),
    //     sat.v(p2.x, p2.y),
    //     sat.v(p3.x, p3.y),
    //     sat.v(p4.x, p4.y)
    // );


    //peek rect
    // Vec2 vertices[] = { p1, p2, p3, p4 };

    //draw peek nodes
    // drawNode->drawPolygon(vertices, 4, Color4F(1.0f,1.0f,1.0f,1), 1, Color4F(0.5f,1.0f,1.0f,1));
    // drawNode->drawSegment(Vec2(x, y - yOff), Vec2(x + mv.x, y + mv.y - yOff), 1, Color4F(0.0f,1.0f,1.0f,1));

    //colliding bools
    bool collidingDown = sat.sat(colliderDown, tile->collider);
    bool collidingLeft = sat.sat(colliderLeft, tile->collider);
    bool collidingRight = sat.sat(colliderRight, tile->collider);
    bool collidingUp = sat.sat(colliderUp, tile->collider);

    // bool collidingPeek = sat.sat(peek, tile->collider);
    // bool collidingAround = sat.sat(colliderAround, tile->collider);

    map<string, bool> contacts = {
        {"down", collidingDown},
        {"up", collidingUp},
        {"left", collidingLeft},
        {"right", collidingRight},
        {"peek", false},
        {"around", false}
    };

    return contacts;
}
void Actor::moveRight() {
    if (!this->hasContactToTheRight) {
        direction = 1;
        velocity = Vec2(moveVector.x, moveVector.y) * moveSpeed * direction;
    }
}

void Actor::moveLeft() {
    if (!this->hasContactToTheLeft) {
        direction = -1;
        velocity = Vec2(moveVector.x, moveVector.y) * moveSpeed * direction;
     }
}
void Actor::jump() {
    if (!this->isJumping && !this->hasContactAbove && this->hasContactBelow) {
        this->isJumping = true;
        moveVector.y = 0.0f;
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
