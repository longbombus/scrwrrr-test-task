#include "cocos2d.h"

class OrbitCameraNode : public cocos2d::Node
{
public:
    CREATE_FUNC(OrbitCameraNode);
    
    bool init() override;
    
    float getDistance() const;
    void setDistance(float distance);
    
    cocos2d::Vec2 const & getLookAngle() const;
    void setLookAngle(float pitch, float yaw);
    
    
private:
    void updateCamera();
    
private:
    float _distance;
    cocos2d::Vec2 _lookAngles;
    cocos2d::Camera * _camera;
};
