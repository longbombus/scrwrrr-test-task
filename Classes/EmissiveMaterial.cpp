#pragma once

#include "EmissiveMaterial.h"

USING_NS_CC;

static std::string const materialName = "emissive";

std::string const & EmissiveMaterial::getName()
{
    return materialName;
}

void EmissiveMaterial::SetEmissiveTexture(std::string const & imagePath)
{
    auto texture = Director::getInstance()->getTextureCache()->addImage(imagePath);
    if (texture)
        SetEmissiveTexture(texture);
}

void EmissiveMaterial::SetEmissiveTexture(Texture2D const * texture)
{
    auto * const technique = this->getTechnique();
    auto * const pass = technique->getPassByIndex(0);
    auto * const programState = pass->getProgramState();
    auto const && emissiveLocation = programState->getUniformLocation("u_emissive");
    
    programState->setTexture(emissiveLocation, 0, texture->getBackendTexture());
}
