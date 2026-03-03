#pragma once

#include "cocos2d.h"

template <typename TMaterial>
class SharedMaterial
{
public:
    static TMaterial * getInstance()
    {
        if (_instance)
            return _instance;
        
        _instance = static_cast<TMaterial *>(TMaterial::createWithShaderName(TMaterial::getName()));
        _instance->retain();
        return _instance;
    }
    
private:
    static TMaterial * _instance;
};

template <typename TMaterial>
TMaterial * SharedMaterial<TMaterial>::_instance = nullptr;
