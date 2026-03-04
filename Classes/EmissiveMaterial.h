#pragma once

#include "SharedMaterial.h"
#include "CustomMaterial.h"

class EmissiveMaterial : public SharedMaterial<EmissiveMaterial>, public CustomMaterial
{
public:
    static std::string const & getName();
    
    void SetEmissiveTexture(std::string const & imagePath);
    void SetEmissiveTexture(cocos2d::Texture2D const * texture);
};
