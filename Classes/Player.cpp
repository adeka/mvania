#include "Player.h"
USING_NS_CC;

Player::Player(float x, float y, Level * level) : Actor(x,y,level)
{
    this->addEventListener(this);
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        this->onKeyReleased(keyCode, event);
        if(keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
            this->stopJump();
        }
    };
}

void Player::update(float delta) {
    Actor::update(delta);
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
        Actor::moveRight();
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
        Actor::moveLeft();
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE)) {
        if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
            Actor::fall();
        } else {
            Actor::jump();
        }
    }
}
// void Player::o nKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
//     CCLOG("AYYY");
// }
 
