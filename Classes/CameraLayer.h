#pragma once

#include "cocos2d.h"

class CameraLayer
{
public:
    static unsigned short constexpr UI = (unsigned short)cocos2d::CameraFlag::DEFAULT;
    static unsigned short constexpr World = (unsigned short)cocos2d::CameraFlag::USER1;
    
    static cocos2d::CameraFlag constexpr UIFlag = cocos2d::CameraFlag::DEFAULT;
    static cocos2d::CameraFlag constexpr WorldFlag = cocos2d::CameraFlag::USER1;
};
