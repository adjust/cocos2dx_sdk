//
//  HelloWorldScene.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#include <platform/CCApplication.h>
#include "HelloWorldScene.h"
#include "AppDelegate.h"

USING_NS_CC;

#define COCOS2D_DEBUG 1

Scene *TestApp::createScene() {
    return TestApp::create();
}

static std::string baseUrl = "https://192.168.8.118:8443";
static std::string gdprUrl = "https://192.168.8.118:8443";
static AdjustCommandExecutor *commandExecutorInstance = new AdjustCommandExecutor(baseUrl, gdprUrl);

void TestApp::initTestLibrary() {
    auto func = [](std::string className, std::string methodName, std::string jsonParameters) {
        CCLOG(">>>>>> EXECUTING COMMAND: %s.%s <<<<<<", className.c_str(), methodName.c_str());
        Command *command = new Command(className, methodName, jsonParameters);
        commandExecutorInstance->executeCommand(command);
    };

    this->testLibrary = new TestLib2dx(baseUrl, func);
}

// on "init" you need to initialize your instance
bool TestApp::init() {
    //////////////////////////////
    // super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Create a Label to identify the sample
    auto label = Label::create();

    label->setString("Adjust Cocos2dx Test App");
    label->setSystemFontSize(19);
    label->setTextColor(Color4B::BLUE);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    /////////////////////////////
    // add main menu
    auto mainMenu = Menu::create();
    int index = 2;
    int offset = 35;
    int divide = 20;

    // Start test session
    auto position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainMenu, "Start Test Session", position, CC_CALLBACK_1(TestApp::onStartTestSession, this));

    // create and initialize Test Library Wrapper
    TestApp::initTestLibrary();

    // Add main menu to screen
    mainMenu->setPosition(Vec2::ZERO);
    this->addChild(mainMenu, 1);
    return true;
}

void TestApp::onStartTestSession(cocos2d::Ref *pSender) {
    CCLOG(">>> Start test session called! <<<");

    // call testLib.startTestSession
    this->testLibrary->startTestSession("cocos2d-x4.14.0@android4.14.0");
}

void TestApp::makeButton(Menu *menu, std::string title, Vec2 position, const ccMenuCallback &callback) {
    auto itemlabel = Label::create();
    itemlabel->setString(title);
    itemlabel->setSystemFontSize(15);

    auto menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback(callback);

    menuItem->setPosition(position);

    menu->addChild(menuItem, 2);
}
