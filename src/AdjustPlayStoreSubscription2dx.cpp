//
//  AdjustPlayStoreSubscription2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 12th June 2020.
//  Copyright © 2015-2020 Adjust GmbH. All rights reserved.
//

#include "AdjustPlayStoreSubscription2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustPlayStoreSubscription2dx::initSubscription(
    std::string price,
    std::string currency,
    std::string sku,
    std::string orderId,
    std::string signature,
    std::string purchaseToken
) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustPlayStoreSubscription", "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jclass jclsAdjustPlayStoreSubscription = jmiInit.env->FindClass("com/adjust/sdk/AdjustPlayStoreSubscription");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustPlayStoreSubscription, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    jlong jPrice = std::stol(price);
    jstring jCurrency = jmiInit.env->NewStringUTF(currency.c_str());
    jstring jSku = jmiInit.env->NewStringUTF(sku.c_str());
    jstring jOrderId = jmiInit.env->NewStringUTF(orderId.c_str());
    jstring jSignature = jmiInit.env->NewStringUTF(signature.c_str());
    jstring jPurchaseToken = jmiInit.env->NewStringUTF(purchaseToken.c_str());
    subscription = jmiInit.env->NewObject(jclsAdjustPlayStoreSubscription, jmidInit, jPrice, jCurrency, jSku, jOrderId, jSignature, jPurchaseToken);
    jmiInit.env->DeleteLocalRef(jCurrency);
    jmiInit.env->DeleteLocalRef(jSku);
    jmiInit.env->DeleteLocalRef(jOrderId);
    jmiInit.env->DeleteLocalRef(jSignature);
    jmiInit.env->DeleteLocalRef(jPurchaseToken);
#endif
}

void AdjustPlayStoreSubscription2dx::setPurchaseTime(std::string purchaseTime) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (subscription == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetPurchaseTime;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetPurchaseTime, "com/adjust/sdk/AdjustPlayStoreSubscription", "setPurchaseTime", "(J)V")) {
        return;
    }

    jlong jPurchaseTime = std::stol(purchaseTime);
    jmiSetPurchaseTime.env->CallVoidMethod(subscription, jmiSetPurchaseTime.methodID, jPurchaseTime);
#endif
}

void AdjustPlayStoreSubscription2dx::addCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (subscription == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddCallbackParameter;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddCallbackParameter, "com/adjust/sdk/AdjustPlayStoreSubscription", "addCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddCallbackParameter.env->NewStringUTF(value.c_str());
    jmiAddCallbackParameter.env->CallVoidMethod(subscription, jmiAddCallbackParameter.methodID, jKey, jValue);
    jmiAddCallbackParameter.env->DeleteLocalRef(jKey);
    jmiAddCallbackParameter.env->DeleteLocalRef(jValue);
#endif
}

void AdjustPlayStoreSubscription2dx::addPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (subscription == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddPartnerParameter;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddPartnerParameter, "com/adjust/sdk/AdjustPlayStoreSubscription", "addPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddPartnerParameter.env->NewStringUTF(value.c_str());
    jmiAddPartnerParameter.env->CallVoidMethod(subscription, jmiAddPartnerParameter.methodID, jKey, jValue);
    jmiAddPartnerParameter.env->DeleteLocalRef(jKey);
    jmiAddPartnerParameter.env->DeleteLocalRef(jValue);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustPlayStoreSubscription2dx::getSubscription() {
    return subscription;
}
#endif
