#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void onTrackEvent(cocos2d::Ref *pSender);

    void onTrackRevenueEvent(cocos2d::Ref *pSender);

    void onTrackCallbackEvent(cocos2d::Ref *pSender);

    void onTrackPartnerEvent(cocos2d::Ref *pSender);

    void onEnableOfflineMode(cocos2d::Ref *pSender);

    void onDisableOfflineMode(cocos2d::Ref *pSender);

    void onEnableSdk(cocos2d::Ref *pSender);

    void onDisableSdk(cocos2d::Ref *pSender);

    void onIsSdkEnabled(cocos2d::Ref *pSender);

    void onSendPushToken(cocos2d::Ref *pSender);

    void onGetIds(cocos2d::Ref *pSender);

    void makeButton(cocos2d::Menu *menu, std::string title, cocos2d::Vec2 position,
                    const cocos2d::ccMenuCallback &callback);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
