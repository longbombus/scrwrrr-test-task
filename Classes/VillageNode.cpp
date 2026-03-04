#include <cmath>

#include "EmissiveMaterial.h"
#include "VillageNode.h"
#include "CameraLayer.h"

USING_NS_CC;

static std::string const k_houseModelPath = "house/house_mesh.c3b";
static std::string const k_houseTexturePath = "house/base_color.png";
static std::string const k_houseEmissiveTexturePath = "house/emission.png";


bool VillageNode::init()
{
    if (!Node::init())
        return false;

    _houseMaterial = EmissiveMaterial::getInstance("house");
    _houseMaterial->setEmissiveTexture(k_houseEmissiveTexturePath);
    _houseMaterial->setLightDirection(Vec3(1,1,1));
    _houseMaterial->setNightColor(Color4F(.1f, .0f, .2f, 1));
    
    return true;
}

void VillageNode::regenerateQuater(Vec3 const & position, float houseOffset, float houseScale, size_t sideStreetsCount, size_t streetSize)
{
    this->removeAllChildren();
    
    spawnQuarter(position, houseOffset, houseScale, sideStreetsCount, streetSize);
}

void VillageNode::spawnQuarter(Vec3 const & position, float houseOffset, float houseScale, size_t sideStreetsCount, size_t streetSize)
{
    Vec3 streatSize = Vec3(
        houseOffset * streetSize,
        0,
        houseOffset * streetSize
    );
    
    Vec3 startPosition = position - streatSize * ((sideStreetsCount - 1) * 0.5f);
    
    for (size_t z = 0; z < sideStreetsCount; ++z)
    {
        for (size_t x = 0; x < sideStreetsCount; ++x)
        {
            float streetYaw;
            switch (RandomHelper::random_int(0, 3))
            {
                case 0: streetYaw = M_PI_4; break;
                case 1: streetYaw = -M_PI_4; break;
                case 2: streetYaw = M_PI_4 * 3; break;
                case 3: streetYaw = -M_PI_4 * 3; break;
            }
            spawnStreet(startPosition + Vec3(streatSize.x * x, 0, streatSize.z * z), houseOffset, houseScale, streetYaw, streetSize);
        }
    }
}

void VillageNode::spawnStreet(Vec3 const & position, float houseOffset, float houseScale, float yaw, size_t size)
{
    Vec3 const direction = Vec3(std::sinf(yaw), 0, std::cosf(yaw));
    Vec3 const startPosition = position - direction * (houseOffset * (size - 1) * 0.5f);
    
    for (size_t i = 0; i < size; ++i)
    {
        spawnHouse(startPosition + direction * (houseOffset * i), houseScale, yaw);
    }
}

void VillageNode::spawnHouse(Vec3 const & position, float scale, float yaw)
{
    auto * house = Sprite3D::create(k_houseModelPath);
    if (!house)
        return;
    
    house->setCameraMask(CameraLayer::World);
    house->setPosition3D(Vec3(position.x, 0, position.z));
    house->setRotation3D(Vec3(0, CC_RADIANS_TO_DEGREES(yaw), 0));
    house->setScale(scale);
    
    house->setMaterial(_houseMaterial);
    
    this->addChild(house);
}
