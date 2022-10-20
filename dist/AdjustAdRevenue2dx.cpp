//
//  AdjustAdRevenue2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 14th October 2022.
//  Copyright © 2022-Present Adjust GmbH. All rights reserved.
//

#include "AdjustAdRevenue2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustAdRevenue2dx::initAdRevenue(std::string source) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustAdRevenue", "<init>", "(Ljava/lang/String;)V")) {
        return;
    }

    jclass jclsAdjustAdRevenue = jmiInit.env->FindClass("com/adjust/sdk/AdjustAdRevenue");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustAdRevenue, "<init>", "(Ljava/lang/String;)V");
    jstring jSource = jmiInit.env->NewStringUTF(source.c_str());
    adRevenue = jmiInit.env->NewObject(jclsAdjustAdRevenue, jmidInit, jSource);
    jmiInit.env->DeleteLocalRef(jSource);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    adRevenue = ADJAdRevenue2dx(source);
    isAdRevenueSet = true;
#endif
}

void AdjustAdRevenue2dx::setRevenue(double amount, std::string currency) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetRevenue;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetRevenue, "com/adjust/sdk/AdjustAdRevenue", "setRevenue", "(Ljava/lang/Double;Ljava/lang/String;)V")) {
        return;
    }

    jclass clsDouble = jmiSetRevenue.env->FindClass("java/lang/Double");
    jmethodID midInit = jmiSetRevenue.env->GetMethodID(clsDouble, "<init>", "(D)V");
    jobject jRevenue = jmiSetRevenue.env->NewObject( clsDouble, midInit, amount);
    jstring jCurrency = jmiSetRevenue.env->NewStringUTF(currency.c_str());
    jmiSetRevenue.env->CallVoidMethod(adRevenue, jmiSetRevenue.methodID, jRevenue, jCurrency);
    jmiSetRevenue.env->DeleteLocalRef(jCurrency);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.setRevenue(amount, currency);
    }
#endif
}

void AdjustAdRevenue2dx::setAdImpressionsCount(int adImpressionsCount) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.setAdImpressionsCount(adImpressionsCount);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetAdImpressionsCount;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetAdImpressionsCount, "com/adjust/sdk/AdjustAdRevenue", "setAdImpressionsCount", "(Ljava/lang/Integer;)V")) {
        return;
    }

    jclass clsInteger = jmiSetAdImpressionsCount.env->FindClass("java/lang/Integer");
    jmethodID midInit = jmiSetAdImpressionsCount.env->GetMethodID(clsInteger, "<init>", "(I)V");
    jobject jAdImpressionsCount = jmiSetAdImpressionsCount.env->NewObject( clsInteger, midInit, adImpressionsCount);
    jmiSetAdImpressionsCount.env->CallVoidMethod(adRevenue, jmiSetAdImpressionsCount.methodID, jAdImpressionsCount);
#endif
}

void AdjustAdRevenue2dx::setAdRevenueNetwork(std::string adRevenueNetwork) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.setAdRevenueNetwork(adRevenueNetwork);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetAdRevenueNetwork;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetAdRevenueNetwork, "com/adjust/sdk/AdjustAdRevenue", "setAdRevenueNetwork", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jAdRevenueNetwork = jmiSetAdRevenueNetwork.env->NewStringUTF(adRevenueNetwork.c_str());
    jmiSetAdRevenueNetwork.env->CallVoidMethod(adRevenue, jmiSetAdRevenueNetwork.methodID, jAdRevenueNetwork);
    jmiSetAdRevenueNetwork.env->DeleteLocalRef(jAdRevenueNetwork);
#endif
}

void AdjustAdRevenue2dx::setAdRevenueUnit(std::string adRevenueUnit) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.setAdRevenueUnit(adRevenueUnit);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetAdRevenueUnit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetAdRevenueUnit, "com/adjust/sdk/AdjustAdRevenue", "setAdRevenueUnit", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jAdRevenueUnit = jmiSetAdRevenueUnit.env->NewStringUTF(adRevenueUnit.c_str());
    jmiSetAdRevenueUnit.env->CallVoidMethod(adRevenue, jmiSetAdRevenueUnit.methodID, jAdRevenueUnit);
    jmiSetAdRevenueUnit.env->DeleteLocalRef(jAdRevenueUnit);
#endif
}

void AdjustAdRevenue2dx::setAdRevenuePlacement(std::string adRevenuePlacement) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.setAdRevenuePlacement(adRevenuePlacement);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetAdRevenuePlacement;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetAdRevenuePlacement, "com/adjust/sdk/AdjustAdRevenue", "setAdRevenuePlacement", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jAdRevenuePlacement = jmiSetAdRevenuePlacement.env->NewStringUTF(adRevenuePlacement.c_str());
    jmiSetAdRevenuePlacement.env->CallVoidMethod(adRevenue, jmiSetAdRevenuePlacement.methodID, jAdRevenuePlacement);
    jmiSetAdRevenuePlacement.env->DeleteLocalRef(jAdRevenuePlacement);
#endif
}

void AdjustAdRevenue2dx::addCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddCallbackParameter;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddCallbackParameter, "com/adjust/sdk/AdjustAdRevenue", "addCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddCallbackParameter.env->NewStringUTF(value.c_str());
    jmiAddCallbackParameter.env->CallVoidMethod(adRevenue, jmiAddCallbackParameter.methodID, jKey, jValue);
    jmiAddCallbackParameter.env->DeleteLocalRef(jKey);
    jmiAddCallbackParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.addCallbackParameter(key, value);
    }
#endif
}

void AdjustAdRevenue2dx::addPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (adRevenue == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddPartnerParameter;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddPartnerParameter, "com/adjust/sdk/AdjustAdRevenue", "addPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddPartnerParameter.env->NewStringUTF(value.c_str());
    jmiAddPartnerParameter.env->CallVoidMethod(adRevenue, jmiAddPartnerParameter.methodID, jKey, jValue);
    jmiAddPartnerParameter.env->DeleteLocalRef(jKey);
    jmiAddPartnerParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isAdRevenueSet) {
        adRevenue.addPartnerParameter(key, value);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustAdRevenue2dx::getAdRevenue() {
    return adRevenue;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJAdRevenue2dx AdjustAdRevenue2dx::getAdRevenue() {
    return adRevenue;
}
#endif
