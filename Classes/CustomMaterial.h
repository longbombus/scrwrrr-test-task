#pragma once

#include "cocos2d.h"

class CustomMaterial : public cocos2d::Material
{
public:
    static CustomMaterial * createWithShaderName(std::string const & shaderName);
};
