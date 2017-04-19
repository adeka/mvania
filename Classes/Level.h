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

    static const int MAPWIDTH = 128;
    static const int MAPHEIGHT = 50;
    static const int MAPSIZE = MAPWIDTH * MAPHEIGHT;

    // vector<TileObject *> testTiles;
    //either use vector or dont use NEW
    // TileObject * tiles[MAPSIZE];
    // int intz[MAPSIZE];

private:

};

#endif
