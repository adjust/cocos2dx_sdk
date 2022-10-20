//
//  TestConnectionOptions2dx.cpp
//  Adjust SDK
//
//  Created by Ugljesa Erceg (@uerceg) on 14th September 2021.
//  Copyright © 2021 Adjust GmbH. All rights reserved.
//

#include "cocos2d.h"
#include "TestConnectionOptions2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif

void TestConnectionOptions2dx::setTestConnectionOptions() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetTestConnectionOptions;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetTestConnectionOptions, "com/adjust/test_options/TestConnectionOptions", "setTestConnectionOptions", "()V")) {
        return;
    }

    jmiSetTestConnectionOptions.env->CallStaticVoidMethod(jmiSetTestConnectionOptions.classID, jmiSetTestConnectionOptions.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
}