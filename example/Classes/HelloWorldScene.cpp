#include <platform/CCApplication.h>
#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "Adjust/Adjust2dx.h"
#include "Adjust/AdjustEvent2dx.h"

USING_NS_CC;

Scene *HelloWorld::createScene() {
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Create a Label to identify the sample
    auto label = Label::create();

    label->setString("Adjust Cocos2dx Examples app");
    label->setSystemFontSize(19);
    label->setTextColor(Color4B::BLUE);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    /////////////////////////////
    // 3. add main menu
    auto mainmenu = Menu::create();
    int index = 2;
    int offset = 35;
    int divide = 20;

    // Track Event
    auto position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Track Event", position,
               CC_CALLBACK_1(HelloWorld::onTrackEvent, this));

    // Track Revenue Event
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Track Revenue Event", position,
               CC_CALLBACK_1(HelloWorld::onTrackRevenueEvent, this));

    // Track Callback Event
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Track Callback Event", position,
               CC_CALLBACK_1(HelloWorld::onTrackCallbackEvent, this));


    // Track Partner Event
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Track Partner Event", position,
               CC_CALLBACK_1(HelloWorld::onTrackPartnerEvent, this));

    // Enable offline mode
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Enable Offline Mode", position,
               CC_CALLBACK_1(HelloWorld::onEnableOfflineMode, this));

    // Disable offline mode
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Disable Offline Mode", position,
               CC_CALLBACK_1(HelloWorld::onDisableOfflineMode, this));

    // Enable SDK
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Enable SDK", position, CC_CALLBACK_1(HelloWorld::onEnableSdk, this));

    // Disable SDK
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Disable SDK", position, CC_CALLBACK_1(HelloWorld::onDisableSdk, this));

    // is Sdk Enabled
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Is SDK Enabled?", position,
               CC_CALLBACK_1(HelloWorld::onIsSdkEnabled, this));

    // Send Push Token
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Send Push Token", position,
               CC_CALLBACK_1(HelloWorld::onSendPushToken, this));

    // Get IDs
    position =
            Vec2(origin.x + visibleSize.width / 2,
                 origin.y + visibleSize.height - label->getContentSize().height
                 + offset
                 - divide * (++index));
    makeButton(mainmenu, "Get IDs", position, CC_CALLBACK_1(HelloWorld::onGetIds, this));

    // Add main menu to screen
    mainmenu->setPosition(Vec2::ZERO);
    this->addChild(mainmenu, 1);
    return true;
}

void HelloWorld::makeButton(Menu *menu, std::string title, Vec2 position,
                            const ccMenuCallback &callback) {
    auto itemlabel = Label::create();
    itemlabel->setString(title);
    itemlabel->setSystemFontSize(15);

    auto menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback(callback);

    menuItem->setPosition(position);

    menu->addChild(menuItem, 2);
}

void HelloWorld::onTrackEvent(cocos2d::Ref *pSender) {
    auto adjustEvent = AdjustEvent2dx("g3mfiw");
    Adjust2dx::trackEvent(adjustEvent);

}

void HelloWorld::onTrackRevenueEvent(cocos2d::Ref *pSender) {
    auto adjustEvent = AdjustEvent2dx("a4fd35");

    adjustEvent.setRevenue(10.0, "USD");
    adjustEvent.setTransactionId("DUMMY_TRANSACTION_ID");

    Adjust2dx::trackEvent(adjustEvent);

}

void HelloWorld::onTrackCallbackEvent(cocos2d::Ref *pSender) {
    auto adjustEvent = AdjustEvent2dx("34vgg9");

    adjustEvent.addCallbackParameter("DUMMY_KEY_1", "DUMMY_VALUE_1");
    adjustEvent.addCallbackParameter("DUMMY_KEY_2", "DUMMY_VALUE_2");

    Adjust2dx::trackEvent(adjustEvent);

}

void HelloWorld::onTrackPartnerEvent(cocos2d::Ref *pSender) {
    auto adjustEvent = AdjustEvent2dx("w788qs");

    adjustEvent.addPartnerParameter("DUMMY_KEY_1", "DUMMY_VALUE_1");
    adjustEvent.addPartnerParameter("DUMMY_KEY_2", "DUMMY_VALUE_2");

    Adjust2dx::trackEvent(adjustEvent);

}

void HelloWorld::onEnableOfflineMode(cocos2d::Ref *pSender) {
    Adjust2dx::setOfflineMode(true);
}

void HelloWorld::onDisableOfflineMode(cocos2d::Ref *pSender) {
    Adjust2dx::setOfflineMode(false);
}

void HelloWorld::onEnableSdk(cocos2d::Ref *pSender) {
    Adjust2dx::setEnabled(true);
}

void HelloWorld::onDisableSdk(cocos2d::Ref *pSender) {
    Adjust2dx::setEnabled(false);
}

void HelloWorld::onIsSdkEnabled(cocos2d::Ref *pSender) {
    if (Adjust2dx::isEnabled()) {
        CCLOG(">>> SDK is enabled");
    } else {
        CCLOG(">>> SDK is disabled");
    }
}

void HelloWorld::onSendPushToken(cocos2d::Ref *pSender) {
    Adjust2dx::setDeviceToken("bunny_foo_foo");
}

void HelloWorld::onGetIds(cocos2d::Ref *pSender) {
    CCLOG(">>> Adid = %s", Adjust2dx::getAdid().c_str());

    Adjust2dx::getGoogleAdId([](std::string adId) {
        CCLOG(">>> Google Ad Id = %s", adId.c_str());
    });

    CCLOG(">>> Amazon Ad Id = %s", Adjust2dx::getAmazonAdId().c_str());
    CCLOG(">>> Get IDFA = %s", Adjust2dx::getIdfa().c_str());

    auto attribution = Adjust2dx::getAttribution();
    CCLOG(">>> Attribution:");
    CCLOG("Tracker token = %s", attribution.getTrackerToken().c_str());
    CCLOG("Tracker name = %s", attribution.getTrackerName().c_str());
    CCLOG("Network = %s", attribution.getNetwork().c_str());
    CCLOG("Campaign = %s", attribution.getCampaign().c_str());
    CCLOG("Adgroup = %s", attribution.getAdgroup().c_str());
    CCLOG("Creative = %s", attribution.getCreative().c_str());
    CCLOG("Click label = %s", attribution.getClickLabel().c_str());
    CCLOG("Adid = %s", attribution.getAdid().c_str());
}
