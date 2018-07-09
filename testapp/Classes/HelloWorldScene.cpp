//
//  HelloWorldScene.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#include <platform/CCApplication.h>
#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "AdjustTesting/TestLib2dx.h"

USING_NS_CC;

Scene *TestApp::createScene() {
    return TestApp::create();
}

void TestApp::initTestLibrary() {
    // TestLib2dx(std::string baseUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters)) {
    std::string baseUrl = "https://192.168.8.68:8443";
    std::string gdprUrl = "https://192.168.8.68:8443";
    void (*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters) = &TestApp::executeCommnad;

    this->testLibrary = new TestLib2dx(baseUrl, executeCommandCallback);

    this->adjustCommandExecutor = new AdjustCommandExecutor(this->testLibrary, baseUrl, gdprUrl);
}

void TestApp::executeCommnad(std::string className, std::string methodName, std::string jsonParameters) {
    CCLOG(" >>>>>> EXECUTING COMMAND: " + className + "." + methodName + " <<<<<<<");
    Command *command = new Command(className, methodName, jsonParameters);
    this->adjustCommandExecutor->executeCommnad(command);
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
    testLibrary->startTestSession("cocos2dx4.14.0@android4.14.0");
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
