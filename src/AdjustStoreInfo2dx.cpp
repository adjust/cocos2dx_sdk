//
//  AdjustStoreInfo2dx.cpp
//  Adjust SDK
//
//  Created by Ugljesa Erceg (@uerceg) on 5th June 2025.
//  Copyright © 2025-Present Adjust GmbH. All rights reserved.
//

#include "AdjustStoreInfo2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustStoreInfo2dx::initStoreInfo(std::string storeName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustStoreInfo", "<init>", "(Ljava/lang/String;)V")) {
        return;
    }

    jclass jclsAdjustStoreInfo = jmiInit.env->FindClass("com/adjust/sdk/AdjustStoreInfo");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustStoreInfo, "<init>", "(Ljava/lang/String;)V");
    jstring jStoreName = jmiInit.env->NewStringUTF(storeName.c_str());
    storeInfo = jmiInit.env->NewObject(jclsAdjustStoreInfo, jmidInit, jStoreName);

    jmiInit.env->DeleteLocalRef(jStoreName);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    storeInfo = ADJStoreInfo2dx(storeName);
    isStoreInfoSet = true;
#endif
}

void AdjustStoreInfo2dx::setStoreAppId(std::string storeAppId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetStore;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetStore, "com/adjust/sdk/AdjustStoreInfo", "setStoreAppId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jStoreAppId = jmiSetStore.env->NewStringUTF(storeAppId.c_str());
    jmiSetStore.env->CallVoidMethod(storeInfo, jmiSetStore.methodID, jStoreAppId);

    jmiSetStore.env->DeleteLocalRef(jStoreAppId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isStoreInfoSet) {
        storeInfo.setStoreAppId(storeAppId);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustStoreInfo2dx::getStoreInfo() {
    return storeInfo;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJStoreInfo2dx AdjustStoreInfo2dx::getStoreInfo() {
    return storeInfo;
}
#endif
