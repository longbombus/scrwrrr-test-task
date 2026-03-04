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
    , _dayHour(12)
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
    
    updateVillage();
    updateDayTime();
    updateHint();
    
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
}

void StartupScene::initUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _hintLabel = Label::createWithTTF(
        std::string(),
        "fonts/arial.ttf",
        12
    );
    if (_hintLabel)
    {
        _hintLabel->setCameraMask(CameraLayer::UI);
        _hintLabel->setPosition(Vec2(
            origin.x + visibleSize.width * .5f,
            origin.y + visibleSize.height
        ));
        _hintLabel->setAnchorPoint(Vec2(0.5f, 1.f));

        this->addChild(_hintLabel, 1);
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

void StartupScene::updateDayTime()
{
    auto * const material = _villageNode->getHouseMaterial();
    material->setDayNightFactor(std::abs(_dayHour - 12) / 12.f);
}

void StartupScene::updateHint()
{
    if (!_hintLabel)
        return;
    
    _hintLabel->setString(StringUtils::format(
        "Use mouse to rotate and zoom\nStreets %dx%d (use keys: - =)\nHouses %d (use keys: [ ])\nTime %02d:00 (use keys: < >)",
        _streetsCount, _streetsCount,
        _streetSize,
        _dayHour
    ));
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
            
        case EventKeyboard::KeyCode::KEY_COMMA:
            _dayHour = (_dayHour + 23) % 24;
            updateDayTime();
            break;
            
        case EventKeyboard::KeyCode::KEY_PERIOD:
            _dayHour = (_dayHour + 1) % 24;
            updateDayTime();
            break;
            
        default:
            return;
    }
    
    updateHint();
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
