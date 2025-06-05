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
    // cocos2d::JniMethodInfo jmiInit;
    // if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustDeeplink", "<init>", "(Landroid/net/Uri;)V")) {
    //     return;
    // }

    // jclass jcUri = jmiInit.env->FindClass("android/net/Uri");
    // jmethodID midParse = jmiInit.env->GetStaticMethodID(jcUri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    // jstring jDeeplinkStr = jmiInit.env->NewStringUTF(deeplinkStr.c_str());
    // jobject jUri = jmiInit.env->CallStaticObjectMethod(jcUri, midParse, jDeeplinkStr);

    // jclass jclsAdjustDeeplink = jmiInit.env->FindClass("com/adjust/sdk/AdjustDeeplink");
    // jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustDeeplink, "<init>", "(Landroid/net/Uri;)V");

    // deeplink = jmiInit.env->NewObject(jclsAdjustDeeplink, jmidInit, jUri);

    // jmiInit.env->DeleteLocalRef(jDeeplinkStr);
    // jmiInit.env->DeleteLocalRef(jUri);
    // TBD
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    storeInfo = ADJStoreInfo2dx(storeName);
    isStoreInfoSet = true;
#endif
}

void AdjustStoreInfo2dx::setStoreAppId(std::string storeAppId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // TBD
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
