#include "CustomMaterial.h"

#include "cocos2d.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/ProgramState.h"

USING_NS_CC;

CustomMaterial * CustomMaterial::createWithShaderName(std::string const & shaderName)
{
    auto * const device = backend::Device::getInstance();
    auto * const fu = FileUtils::getInstance();
    
    auto const && vertPath = cocos2d::StringUtils::format("shaders/%s.vert", shaderName.c_str());
    auto const && fragPath = cocos2d::StringUtils::format("shaders/%s.frag", shaderName.c_str());
    
    auto const && vertFullPath = fu->fullPathForFilename(vertPath);
    auto const && fragFullPath = fu->fullPathForFilename(fragPath);
    
    auto const && vertCode = fu->getStringFromFile(vertPath);
    auto const && fragCode = fu->getStringFromFile(fragPath);
    
    auto * const program = device->newProgram(vertCode, fragCode);
    
    auto * const programState = new backend::ProgramState(program);
    
    auto * const mat = new CustomMaterial();
    if (mat && mat->initWithProgramState(programState))
    {
        mat->setName(shaderName);
        mat->autorelease();
        return mat;
    }
    
    delete mat;
    delete programState;
    return nullptr;
}
