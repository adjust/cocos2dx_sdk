//
//  AdjustThirdPartySharing2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 10th September 2021.
//  Copyright © 2021-Present Adjust GmbH. All rights reserved.
//

#include "AdjustThirdPartySharing2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustThirdPartySharing2dx::initThirdPartySharing() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustThirdPartySharing", "<init>", "(Ljava/lang/Boolean;)V")) {
        return;
    }

    jclass jclsAdjustThirdPartySharing = jmiInit.env->FindClass("com/adjust/sdk/AdjustThirdPartySharing");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustThirdPartySharing, "<init>", "(Ljava/lang/Boolean;)V");
    // jclass jclsBoolean = jmiInit.env->FindClass("java/lang/Boolean");
    // jmethodID jmidValueOf = jmiInit.env->GetStaticMethodID(jclsBoolean, "valueOf", "(Z)Ljava/lang/Boolean;");
    // jobject jIsEnabled = jmiInit.env->CallStaticObjectMethod(jclsBoolean, jmidValueOf, isEnabled);
    thirdPartySharing = jmiInit.env->NewObject(jclsAdjustThirdPartySharing, jmidInit, nullptr);
    // jmiInit.env->DeleteLocalRef(jIsEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    thirdPartySharing = ADJThirdPartySharing2dx();
    isThirdPartySharingSet = true;
#endif
}

void AdjustThirdPartySharing2dx::initThirdPartySharing(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustThirdPartySharing", "<init>", "(Ljava/lang/Boolean;)V")) {
        return;
    }

    jclass jclsAdjustThirdPartySharing = jmiInit.env->FindClass("com/adjust/sdk/AdjustThirdPartySharing");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustThirdPartySharing, "<init>", "(Ljava/lang/Boolean;)V");
    jclass jclsBoolean = jmiInit.env->FindClass("java/lang/Boolean");
    jmethodID jmidValueOf = jmiInit.env->GetStaticMethodID(jclsBoolean, "valueOf", "(Z)Ljava/lang/Boolean;");
    jobject jIsEnabled = jmiInit.env->CallStaticObjectMethod(jclsBoolean, jmidValueOf, isEnabled);
    thirdPartySharing = jmiInit.env->NewObject(jclsAdjustThirdPartySharing, jmidInit, jIsEnabled);
    jmiInit.env->DeleteLocalRef(jIsEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    thirdPartySharing = ADJThirdPartySharing2dx(isEnabled);
    isThirdPartySharingSet = true;
#endif
}

void AdjustThirdPartySharing2dx::addGranularOption(std::string partnerName, std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (thirdPartySharing == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddGranularOption;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddGranularOption, "com/adjust/sdk/AdjustThirdPartySharing", "addGranularOption", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jPartnerName = jmiAddGranularOption.env->NewStringUTF(partnerName.c_str());
    jstring jKey = jmiAddGranularOption.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddGranularOption.env->NewStringUTF(value.c_str());
    jmiAddGranularOption.env->CallVoidMethod(thirdPartySharing, jmiAddGranularOption.methodID, jPartnerName, jKey, jValue);
    jmiAddGranularOption.env->DeleteLocalRef(jPartnerName);
    jmiAddGranularOption.env->DeleteLocalRef(jKey);
    jmiAddGranularOption.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isThirdPartySharingSet) {
        thirdPartySharing.addGranularOption(partnerName, key, value);
    }
#endif
}

void AdjustThirdPartySharing2dx::addPartnerSharingSetting(std::string partnerName, std::string key, bool value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (thirdPartySharing == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddPartnerSharingSetting;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddPartnerSharingSetting, "com/adjust/sdk/AdjustThirdPartySharing", "addPartnerSharingSetting", "(Ljava/lang/String;Ljava/lang/String;Z)V")) {
        return;
    }

    jstring jPartnerName = jmiAddPartnerSharingSetting.env->NewStringUTF(partnerName.c_str());
    jstring jKey = jmiAddPartnerSharingSetting.env->NewStringUTF(key.c_str());
    jmiAddPartnerSharingSetting.env->CallVoidMethod(thirdPartySharing, jmiAddPartnerSharingSetting.methodID, jPartnerName, jKey, value);
    jmiAddPartnerSharingSetting.env->DeleteLocalRef(jPartnerName);
    jmiAddPartnerSharingSetting.env->DeleteLocalRef(jKey);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isThirdPartySharingSet) {
        thirdPartySharing.addPartnerSharingSetting(partnerName, key, value);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustThirdPartySharing2dx::getThirdPartySharing() {
    return thirdPartySharing;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJThirdPartySharing2dx AdjustThirdPartySharing2dx::getThirdPartySharing() {
    return thirdPartySharing;
}
#endif
