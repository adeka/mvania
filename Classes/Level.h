#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "TileObject.h"
#include "cocos2d.h"
using namespace std;

USING_NS_CC;

class Level : public Node {
public:
    Level();
    void prepareLayers();
    void createTiles(CCTMXLayer* layer);
    void addObjects();
    void update(float dt);
    TMXTiledMap * tmx;
    map<string, vector<TileObject *>> tileMap;
private:

};

#endif
