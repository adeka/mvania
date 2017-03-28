#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "InputManager.h"
#include "Level.h"
#include "Player.h"
#include "cocos2d.h"
USING_NS_CC;

class Game : public cocos2d::Layer {
    public:
        static cocos2d::Scene* scene();
        Sprite * sprite;
        Level * level;
        cocos2d::Label * label;
        Player * player;
        Vec2 origin;
        Point * center;
        Size visibleSize;

        virtual bool init() override;
        void menuCloseCallback(Ref* sender);
        virtual void update(float delta) override;
        void fixedUpdate();

        CREATE_FUNC(Game);
    private:

};

#endif // __HELLOWORLD_SCENE_H__
