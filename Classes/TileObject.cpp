#include "TileObject.h"

TileObject::TileObject(Sprite * sprite, int id) {
    this->setPosition(sprite->getPosition().x, sprite->getPosition().y);
    this->sprite = sprite;
    this->id = id;
}
