#pragma once

#include <type_traits>
#include "cocos2d.h"

template <typename TMaterial>
class SharedMaterial
{
public:
    static TMaterial * getInstance(std::string const & name)
    {
        auto && instanceIt = _instances.find(name);
        if (instanceIt != _instances.end())
            return instanceIt->second;
        
        auto * const instance = static_cast<TMaterial *>(TMaterial::createWithShaderName(TMaterial::getName()));
        instance->retain();
        _instances.insert({name, instance});
        return instance;
    }
    
    static typename std::unordered_map<std::string, TMaterial *>::iterator instancesBegin()
    {
        return _instances.begin();
    }
    
    static typename std::unordered_map<std::string, TMaterial *>::iterator instancesEnd()
    {
        return _instances.end();
    }
    
private:
    static std::unordered_map<std::string, TMaterial *> _instances;
};

template <typename TMaterial>
std::unordered_map<std::string, TMaterial *> SharedMaterial<TMaterial>::_instances;
