#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class InputManager {
    public:
        EventListenerKeyboard * eventListener;
        InputManager();
        bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
        double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
        void addEventListener(Node * node);
        void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    private:
        map<EventKeyboard::KeyCode, chrono::high_resolution_clock::time_point> keys;
};
#endif
