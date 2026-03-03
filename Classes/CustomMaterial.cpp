#include "CustomMaterial.h"

#include "cocos2d.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/ProgramState.h"

USING_NS_CC;

CustomMaterial * CustomMaterial::createWithShaderName(std::string const & shaderName)
{
    auto * const device = backend::Device::getInstance();
    auto * const fu = FileUtils::getInstance();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    auto const && vertPath = cocos2d::StringUtils::format("shaders/%s-mtl.vert", shaderName.c_str());
    auto const && fragPath = cocos2d::StringUtils::format("shaders/%s-mtl.frag", shaderName.c_str());
#else
    auto const && vertPath = cocos2d::StringUtils::format("shaders/%s-glsl.vert", shaderName.c_str());
    auto const && fragPath = cocos2d::StringUtils::format("shaders/%s-glsl.frag", shaderName.c_str());
#endif
    
    auto const && vertFullPath = fu->fullPathForFilename(vertPath);
    auto const && fragFullPath = fu->fullPathForFilename(fragPath);
    
    auto * const program = device->newProgram(fu->getStringFromFile(vertFullPath), fu->getStringFromFile(fragFullPath));
    
    auto * const programState = new backend::ProgramState(program);
    
    auto * const mat = new CustomMaterial();
    if (mat && mat->initWithProgramState(programState))
    {
        mat->autorelease();
        return mat;
    }
    
    delete mat;
    delete programState;
    return nullptr;
}
