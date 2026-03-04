#pragma once

#include "cocos2d.h"
#include "EmissiveMaterial.h"

class VillageNode : public cocos2d::Node
{
public:
    CREATE_FUNC(VillageNode);
    
    bool init() override;
    
    void regenerateQuater(cocos2d::Vec3 const & position, float houseOffset, float houseScale, size_t sideStreetsCount, size_t streetSize);
    
    EmissiveMaterial * getHouseMaterial() const { return _houseMaterial; }
    
private:
    void spawnQuarter(cocos2d::Vec3 const & position, float houseOffset, float houseScale, size_t sideStreetsCount, size_t streetSize);
    void spawnStreet(cocos2d::Vec3 const & position, float houseOffset, float houseScale, float yaw, size_t size);
    void spawnHouse(cocos2d::Vec3 const & position, float scale, float yaw);
    
private:
    EmissiveMaterial * _houseMaterial;
};
