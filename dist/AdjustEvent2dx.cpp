//
//  AdjustEvent2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "AdjustEvent2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustEvent2dx::initEvent(std::string eventToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustEvent", "<init>", "(Ljava/lang/String;)V")) {
        return;
    }

    jclass jclsAdjustEvent = jmiInit.env->FindClass("com/adjust/sdk/AdjustEvent");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustEvent, "<init>", "(Ljava/lang/String;)V");
    jstring jToken = jmiInit.env->NewStringUTF(eventToken.c_str());
    event = jmiInit.env->NewObject(jclsAdjustEvent, jmidInit, jToken);
    jmiInit.env->DeleteLocalRef(jToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    event = ADJEvent2dx(eventToken);
    isEventSet = true;
#endif
}

void AdjustEvent2dx::addCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddCallbackParameter;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddCallbackParameter, "com/adjust/sdk/AdjustEvent", "addCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddCallbackParameter.env->NewStringUTF(value.c_str());
    jmiAddCallbackParameter.env->CallVoidMethod(event, jmiAddCallbackParameter.methodID, jKey, jValue);
    jmiAddCallbackParameter.env->DeleteLocalRef(jKey);
    jmiAddCallbackParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.addCallbackParameter(key, value);
    }
#endif
}

void AdjustEvent2dx::addPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddPartnerParameter;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddPartnerParameter, "com/adjust/sdk/AdjustEvent", "addPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddPartnerParameter.env->NewStringUTF(value.c_str());
    jmiAddPartnerParameter.env->CallVoidMethod(event, jmiAddPartnerParameter.methodID, jKey, jValue);
    jmiAddPartnerParameter.env->DeleteLocalRef(jKey);
    jmiAddPartnerParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.addPartnerParameter(key, value);
    }
#endif
}

void AdjustEvent2dx::setRevenue(double amount, std::string currency) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetRevenue;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetRevenue, "com/adjust/sdk/AdjustEvent", "setRevenue", "(DLjava/lang/String;)V")) {
        return;
    }

    jstring jCurrency = jmiSetRevenue.env->NewStringUTF(currency.c_str());
    jmiSetRevenue.env->CallVoidMethod(event, jmiSetRevenue.methodID, amount, jCurrency);
    jmiSetRevenue.env->DeleteLocalRef(jCurrency);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setRevenue(amount, currency);
    }
#endif
}

void AdjustEvent2dx::setTransactionId(std::string transactionId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setTransactionId(transactionId);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetTransactionId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetTransactionId, "com/adjust/sdk/AdjustEvent", "setOrderId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTransactionId = jmiSetTransactionId.env->NewStringUTF(transactionId.c_str());
    jmiSetTransactionId.env->CallVoidMethod(event, jmiSetTransactionId.methodID, jTransactionId);
    jmiSetTransactionId.env->DeleteLocalRef(jTransactionId);
#endif
}

void AdjustEvent2dx::setCallbackId(std::string callbackId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setCallbackId(callbackId);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetCallbackId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallbackId, "com/adjust/sdk/AdjustEvent", "setCallbackId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jCallbackId = jmiSetCallbackId.env->NewStringUTF(callbackId.c_str());
    jmiSetCallbackId.env->CallVoidMethod(event, jmiSetCallbackId.methodID, jCallbackId);
    jmiSetCallbackId.env->DeleteLocalRef(jCallbackId);
#endif
}

bool AdjustEvent2dx::isValid() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return false;
    }
    cocos2d::JniMethodInfo jmiIsValid;
    if (!cocos2d::JniHelper::getMethodInfo(jmiIsValid, "com/adjust/sdk/AdjustEvent", "isValid", "()Z")) {
        return false;
    }

    jboolean jIsValid = jmiIsValid.env->CallBooleanMethod(event, jmiIsValid.methodID);
    return jIsValid;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        return event.isValid();
    } else {
        return false;
    }
#else
    return false;
#endif
}

void AdjustEvent2dx::setProductId(std::string productId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setProductId(productId);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetProductId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetProductId, "com/adjust/sdk/AdjustEvent", "setProductId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jProductId = jmiSetProductId.env->NewStringUTF(productId.c_str());
    jmiSetProductId.env->CallVoidMethod(event, jmiSetProductId.methodID, jProductId);
    jmiSetProductId.env->DeleteLocalRef(jProductId);
#endif
}

void AdjustEvent2dx::setDeduplicationId(std::string deduplicationId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setDeduplicationId(deduplicationId);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetDeduplicationId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetDeduplicationId, "com/adjust/sdk/AdjustEvent", "setDeduplicationId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jDeduplicationId = jmiSetDeduplicationId.env->NewStringUTF(deduplicationId.c_str());
    jmiSetDeduplicationId.env->CallVoidMethod(event, jmiSetDeduplicationId.methodID, jDeduplicationId);
    jmiSetDeduplicationId.env->DeleteLocalRef(jDeduplicationId);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void AdjustEvent2dx::setPurchaseToken(std::string purchaseToken) {
    if (event == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetPurchaseToken;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetPurchaseToken, "com/adjust/sdk/AdjustEvent", "setPurchaseToken", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jPurchaseToken = jmiSetPurchaseToken.env->NewStringUTF(purchaseToken.c_str());
    jmiSetPurchaseToken.env->CallVoidMethod(event, jmiSetPurchaseToken.methodID, jPurchaseToken);
    jmiSetPurchaseToken.env->DeleteLocalRef(jPurchaseToken);
}

jobject AdjustEvent2dx::getEvent() {
    return event;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJEvent2dx AdjustEvent2dx::getEvent() {
    return event;
}
#endif
