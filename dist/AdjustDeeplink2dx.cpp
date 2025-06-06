//
//  AdjustDeeplink2dx.h
//  Adjust SDK
//
//  Created by Pedro Silva (@nonelse) on 30th August 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#include "AdjustDeeplink2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustDeeplink2dx::initDeeplink(std::string deeplinkStr) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustDeeplink", "<init>", "(Landroid/net/Uri;)V")) {
        return;
    }

    jclass jcUri = jmiInit.env->FindClass("android/net/Uri");
    jmethodID midParse = jmiInit.env->GetStaticMethodID(jcUri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jstring jDeeplinkStr = jmiInit.env->NewStringUTF(deeplinkStr.c_str());
    jobject jUri = jmiInit.env->CallStaticObjectMethod(jcUri, midParse, jDeeplinkStr);

    jclass jclsAdjustDeeplink = jmiInit.env->FindClass("com/adjust/sdk/AdjustDeeplink");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustDeeplink, "<init>", "(Landroid/net/Uri;)V");
    deeplink = jmiInit.env->NewObject(jclsAdjustDeeplink, jmidInit, jUri);

    jmiInit.env->DeleteLocalRef(jDeeplinkStr);
    jmiInit.env->DeleteLocalRef(jUri);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    deeplink = ADJDeeplink2dx(deeplinkStr);
    isDeeplinkSet = true;
#endif
}

void AdjustDeeplink2dx::setReferrer(std::string referrer) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (deeplink == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetReferrer;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetReferrer, "com/adjust/sdk/AdjustDeeplink", "setReferrer", "(Landroid/net/Uri;)V")) {
        return;
    }

    jclass jcUri = jmiSetReferrer.env->FindClass("android/net/Uri");
    jmethodID midParse = jmiSetReferrer.env->GetStaticMethodID(jcUri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jstring jReferrerStr = jmiSetReferrer.env->NewStringUTF(referrer.c_str());
    jobject jReferrerUri = jmiSetReferrer.env->CallStaticObjectMethod(jcUri, midParse, jReferrerStr);
    jmiSetReferrer.env->CallVoidMethod(deeplink, jmiSetReferrer.methodID, jReferrerUri);

    jmiSetReferrer.env->DeleteLocalRef(jReferrerStr);
    jmiSetReferrer.env->DeleteLocalRef(jReferrerUri);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isDeeplinkSet) {
        deeplink.setReferrer(referrer);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustDeeplink2dx::getDeeplink() {
    return deeplink;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJDeeplink2dx AdjustDeeplink2dx::getDeeplink() {
    return deeplink;
}
#endif
