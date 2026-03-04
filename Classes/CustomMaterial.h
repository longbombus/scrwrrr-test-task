#pragma once

#include "cocos2d.h"

class CustomMaterial : public cocos2d::Material
{
public:
    static CustomMaterial * createWithShaderName(std::string const & shaderName);
    
protected:
    bool tryGetUniformInfo(std::string const & attributeName, cocos2d::backend::ProgramState * & programState, cocos2d::backend::UniformLocation & uniformLocation) const;
};
