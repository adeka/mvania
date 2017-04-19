#ifndef __TILEOBJECT_H__
#define __TILEOBJECT_H__

#include "cocos2d.h"
#include "SAT.h"
USING_NS_CC;

class TileObject : public Node {
    public:
        TileObject(Sprite * sprite, int tx, int y, int id);
        Sprite * sprite;
        int id;
        polygon collider;
        SAT sat;
        Vec2 moveVector;
        float minX;
        float minY;
        float maxX;
        float maxY;

        int x;
        int y;
        
        float tileSize;
        float base;

        float getTop(float x);
};
#endif
