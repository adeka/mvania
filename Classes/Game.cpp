#include "Game.h"
#include <string>
#include <algorithm>
using namespace std;

USING_NS_CC;

Scene* Game::scene()
{
    auto scene = Scene::create();
    Game *layer = Game::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    if ( !Layer::init() ) { return false; }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    center = new Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    float playfield_width = visibleSize.width * 20.0;
	float playfield_height = visibleSize.height * 20.0;

    level = new Level();
    this->addChild(level);

    player = new Player(80.0f, 100.0f, level);
    this->addChild(player);

    this->scheduleUpdate();
    //last thing this function should do
    return true;
}

void Game::update(float delta) {
    Node::update(delta);
    this->setPosition(center->x - player->getPosition().x, center->y - player->getPosition().y);
}

void Game::fixedUpdate() {
    //move the screen
    // CCLOG("%f", accumulator);
    // CCLOG("%i", player->hasContactBelow);
    // CCLOG("%i", player->hasContactToTheLeft);
}
//close menu callback function
void Game::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    #endif
}
