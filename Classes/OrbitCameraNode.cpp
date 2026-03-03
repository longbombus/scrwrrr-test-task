#include "OrbitCameraNode.h"

USING_NS_CC;

static float constexpr k_cameraFov = 60;
static float constexpr k_cameraNearPlane = 1;
static float constexpr k_cameraFarPlane = 1000;
static float constexpr k_minDistance = 10;
static float constexpr k_maxDistance = 500;
static float constexpr k_minPitch = -90;
static float constexpr k_maxPitch = 0;
static float constexpr k_yawRange = 360;


bool OrbitCameraNode::init()
{
    if (!Node::init())
        return false;
    
    _distance = 100;
    
    _camera = Camera::createPerspective(k_cameraFov, 1, k_cameraNearPlane, k_cameraFarPlane);
    this->addChild(_camera);
    return true;
}

float OrbitCameraNode::getDistance() const
{
    return _distance;
}

void OrbitCameraNode::setDistance(float distance)
{
    _distance = cocos2d::clampf(distance, k_minDistance, k_maxDistance);
    
    updateCamera();
}

Vec2 const & OrbitCameraNode::getLookAngle() const
{
    return _lookAngles;
}

void OrbitCameraNode::setLookAngle(float pitch, float yaw)
{
    pitch = cocos2d::clampf(pitch, k_minPitch, k_maxPitch);
    
    _lookAngles = Vec2(pitch, yaw);
    _camera->setRotation3D(Vec3(pitch, yaw, 0));
    
    updateCamera();
}


void OrbitCameraNode::updateCamera()
{
    Vec3 forward;
    _camera->getNodeToWorldTransform().getForwardVector(&forward);
    _camera->setPosition3D(-forward * _distance);
}
