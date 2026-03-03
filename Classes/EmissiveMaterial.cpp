#pragma once

#include "EmissiveMaterial.h"

USING_NS_CC;

static std::string const materialName = "emissive";

std::string const & EmissiveMaterial::getName()
{
    return materialName;
}
