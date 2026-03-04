#pragma once

#include "EmissiveMaterial.h"

USING_NS_CC;

static std::string const k_materialName = "emissive";
static std::string const k_emissiveTextureUniformName = "u_emissive";
static std::string const k_lightDirectionUniformName = "u_lightDirection";

std::string const & EmissiveMaterial::getName()
{
    return k_materialName;
}

void EmissiveMaterial::setEmissiveTexture(std::string const & imagePath)
{
    auto texture = Director::getInstance()->getTextureCache()->addImage(imagePath);
    if (texture)
        setEmissiveTexture(texture);
}

void EmissiveMaterial::setEmissiveTexture(Texture2D const * texture)
{
    backend::ProgramState * state;
    backend::UniformLocation location;
    
    if (!tryGetUniformInfo(k_emissiveTextureUniformName, state, location))
    {
        cocos2d::log("EmissiveMaterial: %s uniform is not found in shader %s", k_emissiveTextureUniformName.c_str(), k_materialName.c_str());
        return;
    }
    
    state->setTexture(location, 0, texture->getBackendTexture());
}

void EmissiveMaterial::setLightDirection(Vec3 const & direction)
{
    backend::ProgramState * state;
    backend::UniformLocation location;
    
    if (!tryGetUniformInfo(k_lightDirectionUniformName, state, location))
    {
        cocos2d::log("EmissiveMaterial: %s uniform is not found in shader %s", k_lightDirectionUniformName.c_str(), k_materialName.c_str());
        return;
    }
    
    state->setUniform(location, &direction, sizeof(direction));
}
