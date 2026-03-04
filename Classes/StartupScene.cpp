#include "StartupScene.h"

#include "CameraLayer.h"
#include "VillageNode.h"

USING_NS_CC;

static Vec3 const k_mouseSensitivity = Vec3(-0.2f, -0.2f, 1);
static int const k_minStreetSize = 2;
static int const k_maxStreetSize = 10;
static int const k_initialStreetSize = 3;
static int const k_minStreetsCount = 1;
static int const k_maxStreetsCount = 10;
static int const k_initialStreetsCount = 5;

StartupScene::StartupScene() noexcept
    : _streetsCount(k_initialStreetsCount)
    , _streetSize(k_initialStreetSize)
{
}

Scene * StartupScene::createScene()
{
    return StartupScene::create();
}

bool StartupScene::init()
{
    if (!Scene::init())
        return false;
    
    initWorld();
    initUI();
    initInput();
    
    return true;
}

void StartupScene::initWorld()
{
    _cameraNode = OrbitCameraNode::create();
    _cameraNode->setDistance(100);
    _cameraNode->setLookAngle(-45, 0);
    this->addChild(_cameraNode);
    
    _villageNode = VillageNode::create();
    this->addChild(_villageNode);
    
    updateVillage();
}

void StartupScene::initUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto * const hintLabel = Label::createWithTTF(
        "Move mouse = rotate\nMouse wheel = zoom",
        "fonts/Marker Felt.ttf",
        16
    );
    hintLabel->setCameraMask(CameraLayer::UI);
    
    if (hintLabel)
    {
        hintLabel->setPosition(Vec2(
            origin.x + visibleSize.width * .5f,
            origin.y + visibleSize.height - hintLabel->getContentSize().height
        ));

        this->addChild(hintLabel, 1);
    }
    else
        cocos2d::log("Hint label was not created");
}

void StartupScene::initInput()
{
    auto * const keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = std::bind(&StartupScene::updateKeyboardKeyPress, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    auto * const mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = std::bind(&StartupScene::updateMouseButton, this, std::placeholders::_1);
    mouseListener->onMouseMove = std::bind(&StartupScene::updateMouseMove, this, std::placeholders::_1);
    mouseListener->onMouseScroll = std::bind(&StartupScene::updateMouseScroll, this, std::placeholders::_1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void StartupScene::updateVillage()
{
    _villageNode->regenerateQuater(Vec3::ZERO, 5, 0.001f, _streetsCount, _streetSize);
}

void StartupScene::updateKeyboardKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_LEFT_BRACKET:
            _streetSize = std::max(_streetSize - 1, k_minStreetSize);
            updateVillage();
            break;
            
        case EventKeyboard::KeyCode::KEY_RIGHT_BRACKET:
            _streetSize = std::min(_streetSize + 1, k_maxStreetSize);
            updateVillage();
            break;
            
        case EventKeyboard::KeyCode::KEY_MINUS:
            _streetsCount = std::max(_streetsCount - 1, k_minStreetsCount);
            updateVillage();
            break;
            
        case EventKeyboard::KeyCode::KEY_EQUAL:
            _streetsCount = std::min(_streetsCount + 1, k_maxStreetsCount);
            updateVillage();
            break;
            
        default:
            break;
    }
}

void StartupScene::updateMouseButton(cocos2d::EventMouse * event)
{
    _lastMousePosition = event->getLocation();
}

void StartupScene::updateMouseMove(EventMouse * event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_UNSET)
        return;
    
    Vec2 const currentMousePosition = event->getLocation();
    Vec2 const delta = currentMousePosition - _lastMousePosition;
    _lastMousePosition = currentMousePosition;
    
    Vec2 const & lookAngle = _cameraNode->getLookAngle();
    _cameraNode->setLookAngle(lookAngle.x + delta.y * k_mouseSensitivity.y, lookAngle.y + delta.x * k_mouseSensitivity.x);
}

void StartupScene::updateMouseScroll(EventMouse * event)
{
    float const scrollDelta = event->getScrollY();
    float const distance = _cameraNode->getDistance();
    _cameraNode->setDistance(distance + scrollDelta * k_mouseSensitivity.z);
}
