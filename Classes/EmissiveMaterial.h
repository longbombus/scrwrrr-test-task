#pragma once

#include "SharedMaterial.h"
#include "CustomMaterial.h"

class EmissiveMaterial : public SharedMaterial<EmissiveMaterial>, public CustomMaterial
{
public:
    static std::string const & getName();
};
