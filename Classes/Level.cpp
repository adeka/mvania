#include "Level.h"
USING_NS_CC;

Level::Level(void) {
    tmx = TMXTiledMap::create("Tilemaps/debug.tmx");
    prepareLayers();
    this->addChild(tmx);
}

void Level::update(float dt)
{
}

void Level::prepareLayers()
{
    for (auto& object : this->tmx->getChildren())
    {
        auto layer = dynamic_cast<TMXLayer*>(object);
        if (layer != nullptr)
        this->createTiles(layer);
    }
}

void Level::createTiles(CCTMXLayer* layer)
{
    Size layerSize = layer->getLayerSize();
    string layerName = layer->getLayerName();
    vector<TileObject *> tiles;
    for (int y = 0; y < layerSize.height; y++)
    {
        for (int x = 0; x < layerSize.width; x++)
        {
            Sprite * tileSprite = layer->getTileAt(Point(x, y));
            int id = layer->getTileGIDAt(Point(x, y));
            if (tileSprite) {
                TileObject * tile = new TileObject(tileSprite, x, y, id);
                tiles.push_back(tile);
            } else {
                tiles.push_back(nullptr);
            }
        }
    }
    tileMap[layerName] = tiles;
}

void Level::addObjects()
{
    // // loop over the object groups in this tmx file
    // auto objectGroups = tmx->getObjectGroups();
    // for (auto& objectGroup : objectGroups)
    // {
    //     auto objects = objectGroup->getObjects();
    //     for (auto& object : objects)
    //     {
    //         auto properties = object.asValueMap();
    //         auto type = properties.at("type");
    //         if (!type.isNull())
    //         {
    //             this->addObject(type.asString().c_str(), properties);
    //             this->objectCount++;
    //         }
    //     }
    // }
}
