#include "TileObject.h"

TileObject::TileObject(Sprite * sprite, int x, int y, int id) {
    this->setPosition(sprite->getPosition().x, sprite->getPosition().y);
    this->sprite = sprite;
    this->id = id;

    minX = this->sprite->getBoundingBox().getMinX();
    minY = this->sprite->getBoundingBox().getMinY();
    maxX = this->sprite->getBoundingBox().getMaxX();
    maxY = this->sprite->getBoundingBox().getMaxY();

    this->x = x;
    this->y = y;

    tileSize = 16.0f;
    base = tileSize;

    moveVector = Vec2(1.0f,0.0f);
    //45
    if(id == 46 || id == 68) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,maxY),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-1.0f);
        base = tileSize;
    }
    //45
    else if(id == 45 || id == 66) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(maxX,maxY),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,1.0f);
        base = 0;
    }
    //////////////////////////////////////////////
    //30-60-90 RIGHT
    else if(id == 35) {
        collider = sat.Polygon(4,
            sat.v(minX,minY),
            sat.v(minX,maxY),
            sat.v(maxX,minY + tileSize/2.0f),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-0.5f);
    }
    //30-60-90 RIGHT
    else if(id == 36) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + tileSize/2.0f),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-0.5f);
        base = tileSize / 2.0f;
    }
    //////////////////////////////////////////////
    //30-60-90 LEFT
    else if(id == 33) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(maxX,minY + tileSize/2.0f),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,0.5f);
        base = 0;
    }
    // 30-60-90 LEFT
    else if(id == 34) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + tileSize/2.0f),
            sat.v(maxX,maxY),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,0.5f);
        base = tileSize / 2.0f;
    }
    //ONE WAY Tile
    else if(id == 52) {
        collider = sat.Polygon(4,
            sat.v(minX,maxY - 1.0f),
            sat.v(minX,maxY),
            sat.v(maxX,maxY),
            sat.v(maxX,maxY - 1.0f)
        );
    }
    //////////////////////////////////////////////
    //SUPER LONG LEFT
    else if(id == 13) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(maxX,minY + (tileSize * (1.0f / 4.0f)) ),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,0.25f);
        base = 0;
    }
    else if(id == 14) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (1.0f / 4.0f))),
            sat.v(maxX,minY + (tileSize * (2.0f / 4.0f))),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,0.25f);
        base = tileSize * (1.0f / 4.0f);
    }
    else if(id == 15) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (2.0f / 4.0f))),
            sat.v(maxX,minY + (tileSize * (3.0f / 4.0f))),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,0.25f);
        base = tileSize * (2.0f / 4.0f);
    }
    else if(id == 16) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (3.0f / 4.0f))),
            sat.v(maxX,minY + (tileSize * (4.0f / 4.0f))),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,0.25f);
        base = tileSize * (3.0f / 4.0f);
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    //SUPER LONG RIGHT
    else if(id == 21) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (4.0f / 4.0f))),
            sat.v(maxX,minY + (tileSize * (3.0f / 4.0f)) ),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-0.25f);
        base = tileSize;
    }
    else if(id == 22) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (3.0f / 4.0f))),
            sat.v(maxX,minY + (tileSize * (2.0f / 4.0f)) ),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-0.25f);
        base = tileSize * (3.0f / 4.0f);
    }
    else if(id == 23) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (2.0f / 4.0f))),
            sat.v(maxX,minY + (tileSize * (1.0f / 4.0f)) ),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-0.25f);
        base = tileSize * (2.0f / 4.0f);
    }
    else if(id == 24) {
        collider = sat.Polygon(3,
            sat.v(minX,minY),
            sat.v(minX,minY + (tileSize * (1.0f / 4.0f)) ),
            sat.v(maxX,minY)
        );
        moveVector = Vec2(1.0f,-0.25f);
        base = tileSize * (1.0f / 4.0f);
    }
    //////////////////////////////////////////////
    //DEFAULT BLOCK
    else {
        collider = sat.Polygon(4,
            sat.v(minX,minY),
            sat.v(minX,maxY),
            sat.v(maxX,maxY),
            sat.v(maxX,minY)
        );
    }
    //set tile base height below triangle
}

float TileObject::getTop(float x) {
    float diff = fmax(x - this->getPosition().x, 0.0f);
    float ratio = diff / tileSize;//- 0.3125f;
    float value = ratio; //(ratio - 1.0f) * -1.0f;
    float slope = moveVector.y / moveVector.x;
    float yOffset = (value * slope) * tileSize;
    return this->getPosition().y + base + yOffset;
}
