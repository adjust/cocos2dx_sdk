//
//  HelloWorldScene.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018-Present Adjust GmbH. All rights reserved.
//

#include <platform/CCApplication.h>
#include "HelloWorldScene.h"
#include "AppDelegate.h"

USING_NS_CC;

#define COCOS2D_DEBUG 1

Scene *TestApp::createScene() {
    return TestApp::create();
}

static std::string serverIp = "192.168.86.227";
static std::string controlUrl = "ws://" + serverIp + ":1987";
static TestLib2dx *testLibrary;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static std::string urlOverwrite = "http://" + serverIp + ":8080";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static std::string urlOverwrite = "https://" + serverIp + ":8443";
#endif

static AdjustCommandExecutor *commandExecutorInstance = new AdjustCommandExecutor(urlOverwrite);

void TestApp::initTestLibrary() {
    auto func = [](std::string className, std::string methodName, std::string jsonParameters) {
        CCLOG("[AdjustTest]: Executing command: %s.%s", className.c_str(), methodName.c_str());
        Command *command = new Command(className, methodName, jsonParameters);
        commandExecutorInstance->executeCommand(command);
    };

    testLibrary = new TestLib2dx(urlOverwrite, controlUrl, func);
}

bool TestApp::init() {
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

    // Position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // Add the label as a child to this layer
    this->addChild(label, 1);

    // Add main menu
    auto mainMenu = Menu::create();
    int index = 2;
    int offset = 35;
    int divide = 20;

    // Start test session
    auto position = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height + offset - divide * (++index));
    makeButton(mainMenu, "Start Test Session", position, CC_CALLBACK_1(TestApp::onStartTestSession, this));

    // Create and initialize test library wrapper
    TestApp::initTestLibrary();
    
    CCLOG("[AdjustTest]: Start test session called!");
    // testLibrary->addTestDirectory("purchase-verification");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary->startTestSession("cocos2d-x5.4.0@ios5.4.0");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Adjust2dx::getSdkVersion([] (std::string sdkVersion) {
        testLibrary->startTestSession(sdkVersion);
    });
#endif

    // Add main menu to screen
    mainMenu->setPosition(Vec2::ZERO);
    this->addChild(mainMenu, 1);
    return true;
}

void TestApp::onStartTestSession(cocos2d::Ref *pSender) {
    CCLOG("[AdjustTest]: Start test session called!");
    Adjust2dx::getSdkVersion([] (std::string sdkVersion) {
        testLibrary->startTestSession(sdkVersion);
    });
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
