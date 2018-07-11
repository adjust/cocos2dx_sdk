//
//  HelloWorldScene.h
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#ifndef __TESTAPP_SCENE_H__
#define __TESTAPP_SCENE_H__

#include "cocos2d.h"
#include "AdjustTesting/TestLib2dx.h"
#include "AdjustCommandExecutor.h"

class TestApp : public cocos2d::Scene {
private:
    TestLib2dx *testLibrary;
    void initTestLibrary();

public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void onStartTestSession(cocos2d::Ref *pSender);

    void makeButton(cocos2d::Menu *menu, std::string title, cocos2d::Vec2 position,
                    const cocos2d::ccMenuCallback &callback);

    CREATE_FUNC(TestApp);
};

#endif // __TESTAPP_SCENE_H__
