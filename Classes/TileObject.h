#ifndef __TILEOBJECT_H__
#define __TILEOBJECT_H__

#include "cocos2d.h"
USING_NS_CC;

class TileObject : public Node {
    public:
        TileObject(Sprite * sprite, int id);
        Sprite * sprite;
        int id;
};
#endif
