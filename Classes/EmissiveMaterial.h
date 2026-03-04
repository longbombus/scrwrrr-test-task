#pragma once

#include "SharedMaterial.h"
#include "CustomMaterial.h"

class EmissiveMaterial : public SharedMaterial<EmissiveMaterial>, public CustomMaterial
{
public:
    static std::string const & getName();
    
    void setEmissiveTexture(std::string const & imagePath);
    void setEmissiveTexture(cocos2d::Texture2D const * texture);
    
    void setLightDirection(cocos2d::Vec3 const & direction);
    void setNightColor(cocos2d::Color4F const & nightColor);
    void setDayNightFactor(float dayNightFactor);
};
