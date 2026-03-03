#pragma once

#include "cocos2d.h"

#include "OrbitCameraNode.h"
#include "VillageNode.h"

class StartupScene : public cocos2d::Scene
{
public:
    StartupScene() noexcept;
    
    CREATE_FUNC(StartupScene);
    
    static cocos2d::Scene * createScene();

    virtual bool init();
    
private:
    void initWorld();
    void initUI();
    void initInput();
    
    void updateVillage();
    
    void updateKeyboardKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateMouseButton(cocos2d::EventMouse * event);
    void updateMouseMove(cocos2d::EventMouse * event);
    void updateMouseScroll(cocos2d::EventMouse * event);
    
private:
    int _streetSize;
    int _streetsCount;
    cocos2d::Vec2 _lastMousePosition;
    OrbitCameraNode * _cameraNode;
    VillageNode * _villageNode;
};
