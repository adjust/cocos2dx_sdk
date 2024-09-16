//
//  Adjust2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#define COCOS2D_DEBUG 1

#include "Adjust2dx.h"
#include <stdlib.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "AdjustProxy2dx.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJAdjust2dx.h"
#endif

const std::string AdjustEnvironmentSandbox2dx = "sandbox";
const std::string AdjustEnvironmentProduction2dx = "production";

void Adjust2dx::start(AdjustConfig2dx adjustConfig) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiOnCreate;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiOnCreate, "com/adjust/sdk/Adjust", "initSdk", "(Lcom/adjust/sdk/AdjustConfig;)V")) {
        return;
    }
    jmiOnCreate.env->CallStaticVoidMethod(jmiOnCreate.classID, jmiOnCreate.methodID, adjustConfig.getConfig());
    onResume();
    jmiOnCreate.env->DeleteGlobalRef(adjustConfig.getConfig());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::initSdk(adjustConfig.getConfig());
    onResume();
#endif
}

void Adjust2dx::trackEvent(AdjustEvent2dx event) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackEvent;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackEvent, "com/adjust/sdk/Adjust", "trackEvent", "(Lcom/adjust/sdk/AdjustEvent;)V")) {
        return;
    }
    jmiTrackEvent.env->CallStaticVoidMethod(jmiTrackEvent.classID, jmiTrackEvent.methodID, event.getEvent());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackEvent(event.getEvent());
#endif
}

void Adjust2dx::trackAppStoreSubscription(AdjustAppStoreSubscription2dx subscription) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackAppStoreSubscription(subscription.getSubscription());
#endif
}

void Adjust2dx::verifyAppStorePurchase(AdjustAppStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::verifyAppStorePurchase(purchase.getPurchase(), verificationCallback);
#endif
}

void Adjust2dx::verifyAndTrackAppStorePurchase(AdjustEvent2dx event, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::verifyAndTrackAppStorePurchase(event.getEvent(), verificationCallback);
#endif
}

void Adjust2dx::trackPlayStoreSubscription(AdjustPlayStoreSubscription2dx subscription) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackPlayStoreSubscription;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackPlayStoreSubscription, "com/adjust/sdk/Adjust", "trackPlayStoreSubscription", "(Lcom/adjust/sdk/AdjustPlayStoreSubscription;)V")) {
        return;
    }
    jmiTrackPlayStoreSubscription.env->CallStaticVoidMethod(jmiTrackPlayStoreSubscription.classID, jmiTrackPlayStoreSubscription.methodID, subscription.getSubscription());
#endif
}

void Adjust2dx::verifyPlayStorePurchase(AdjustPlayStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setVerifyPlayStorePurchaseCallbackMethod(verificationCallback);

    cocos2d::JniMethodInfo jmiVerifyPlayStorePurchase;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiVerifyPlayStorePurchase, "com/adjust/sdk/Adjust", "verifyPlayStorePurchase", "(Lcom/adjust/sdk/AdjustPurchase;Lcom/adjust/sdk/OnPurchaseVerificationFinishedListener;)V")) {
        return;
    }
    jclass clsAdjust2dxVerifyPlayStorePurchaseCallback = jmiVerifyPlayStorePurchase.env->FindClass("com/adjust/sdk/Adjust2dxVerifyPlayStorePurchaseCallback");
    jmethodID jmidInit = jmiVerifyPlayStorePurchase.env->GetMethodID(clsAdjust2dxVerifyPlayStorePurchaseCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiVerifyPlayStorePurchase.env->NewObject(clsAdjust2dxVerifyPlayStorePurchaseCallback, jmidInit);
    jmiVerifyPlayStorePurchase.env->CallStaticVoidMethod(jmiVerifyPlayStorePurchase.classID, jmiVerifyPlayStorePurchase.methodID, purchase.getPurchase(), jCallbackProxy);
    jmiVerifyPlayStorePurchase.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::verifyAndTrackPlayStorePurchase(AdjustEvent2dx event, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setVerifyAndTrackPlayStorePurchaseCallbackMethod(verificationCallback);

    cocos2d::JniMethodInfo jmiVerifyAndTrackPlayStorePurchase;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiVerifyAndTrackPlayStorePurchase, "com/adjust/sdk/Adjust", "verifyAndTrackPlayStorePurchase", "(Lcom/adjust/sdk/AdjustEvent;Lcom/adjust/sdk/OnPurchaseVerificationFinishedListener;)V")) {
        return;
    }
    jclass clsAdjust2dxVerifyAndTrackPlayStorePurchaseCallback = jmiVerifyAndTrackPlayStorePurchase.env->FindClass("com/adjust/sdk/Adjust2dxVerifyAndTrackPlayStorePurchaseCallback");
    jmethodID jmidInit = jmiVerifyAndTrackPlayStorePurchase.env->GetMethodID(clsAdjust2dxVerifyAndTrackPlayStorePurchaseCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiVerifyAndTrackPlayStorePurchase.env->NewObject(clsAdjust2dxVerifyAndTrackPlayStorePurchaseCallback, jmidInit);
    jmiVerifyAndTrackPlayStorePurchase.env->CallStaticVoidMethod(jmiVerifyAndTrackPlayStorePurchase.classID, jmiVerifyAndTrackPlayStorePurchase.methodID, event.getEvent(), jCallbackProxy);
    jmiVerifyAndTrackPlayStorePurchase.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::enable() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetEnabled;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetEnabled, "com/adjust/sdk/Adjust", "enable", "()V")) {
        return;
    }
    jmiSetEnabled.env->CallStaticVoidMethod(jmiSetEnabled.classID, jmiSetEnabled.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::enable();
#endif
}

void Adjust2dx::disable() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetEnabled;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetEnabled, "com/adjust/sdk/Adjust", "disable", "()V")) {
        return;
    }
    jmiSetEnabled.env->CallStaticVoidMethod(jmiSetEnabled.classID, jmiSetEnabled.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::disable();
#endif
}

void Adjust2dx::isEnabledCallback(void(*callbackMethod)(bool isEnabled)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setIsEnabledCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiIsEnabledCallback;

    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiIsEnabledCallback, "com/adjust/sdk/Adjust", "isEnabled", "(Landroid/content/Context;Lcom/adjust/sdk/OnIsEnabledListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxIsEnabledCallback", "<init>", "()V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jclass clsAdjust2dxIsEnabledCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxIsEnabledCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxIsEnabledCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxIsEnabledCallback, jmidInit);
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiIsEnabledCallback.env->CallStaticVoidMethod(jmiIsEnabledCallback.classID, jmiIsEnabledCallback.methodID, jContext, jCallbackProxy);
    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::isEnabledCallback(callbackMethod);
#endif
}

void Adjust2dx::switchToOfflineMode() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSwitchToOfflineMode;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSwitchToOfflineMode, "com/adjust/sdk/Adjust", "switchToOfflineMode", "()V")) {
        return;
    }
    jmiSwitchToOfflineMode.env->CallStaticVoidMethod(jmiSwitchToOfflineMode.classID, jmiSwitchToOfflineMode.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::switchToOfflineMode();
#endif
}

void Adjust2dx::switchBackToOnlineMode() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSwitchBackToOnlineMode;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSwitchBackToOnlineMode, "com/adjust/sdk/Adjust", "switchBackToOnlineMode", "()V")) {
        return;
    }
    jmiSwitchBackToOnlineMode.env->CallStaticVoidMethod(jmiSwitchBackToOnlineMode.classID, jmiSwitchBackToOnlineMode.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::switchBackToOnlineMode();
#endif
}

void Adjust2dx::processDeeplink(AdjustDeeplink2dx deeplink) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::processDeeplink(deeplink.getDeeplink());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiProcessDeeplink;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiProcessDeeplink, "com/adjust/sdk/Adjust", "processDeeplink", "(Lcom/adjust/sdk/AdjustDeeplink;Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);

    jmiProcessDeeplink.env->CallStaticVoidMethod(jmiProcessDeeplink.classID, jmiProcessDeeplink.methodID, deeplink.getDeeplink(), jContext);

    jmiGetContext.env->DeleteLocalRef(jContext);
#endif
}

void Adjust2dx::setPushTokenAsString(std::string pushToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setPushTokenAsString(pushToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetPushToken;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetPushToken, "com/adjust/sdk/Adjust", "setPushToken", "(Ljava/lang/String;Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jstring jPushToken = jmiSetPushToken.env->NewStringUTF(pushToken.c_str());
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiSetPushToken.env->CallStaticVoidMethod(jmiSetPushToken.classID, jmiSetPushToken.methodID, jPushToken, jContext);
    jmiSetPushToken.env->DeleteLocalRef(jPushToken);
    jmiGetContext.env->DeleteLocalRef(jContext);
#endif
}

void Adjust2dx::gdprForgetMe() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::gdprForgetMe();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiGdprForgetMe;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGdprForgetMe, "com/adjust/sdk/Adjust", "gdprForgetMe", "(Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiGdprForgetMe.env->CallStaticVoidMethod(jmiGdprForgetMe.classID, jmiGdprForgetMe.methodID, jContext);
    jmiGetContext.env->DeleteLocalRef(jContext);
#endif
}

void Adjust2dx::addGlobalCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::addGlobalCallbackParameter(key, value);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiAddGlobalCallbackParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiAddGlobalCallbackParameter, "com/adjust/sdk/Adjust", "addGlobalCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddGlobalCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddGlobalCallbackParameter.env->NewStringUTF(value.c_str());
    jmiAddGlobalCallbackParameter.env->CallStaticVoidMethod(jmiAddGlobalCallbackParameter.classID, jmiAddGlobalCallbackParameter.methodID, jKey, jValue);
    jmiAddGlobalCallbackParameter.env->DeleteLocalRef(jKey);
    jmiAddGlobalCallbackParameter.env->DeleteLocalRef(jValue);
#endif
}

void Adjust2dx::addGlobalPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::addGlobalPartnerParameter(key, value);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiAddGlobalPartnerParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiAddGlobalPartnerParameter, "com/adjust/sdk/Adjust", "addGlobalPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddGlobalPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddGlobalPartnerParameter.env->NewStringUTF(value.c_str());
    jmiAddGlobalPartnerParameter.env->CallStaticVoidMethod(jmiAddGlobalPartnerParameter.classID, jmiAddGlobalPartnerParameter.methodID, jKey, jValue);
    jmiAddGlobalPartnerParameter.env->DeleteLocalRef(jKey);
    jmiAddGlobalPartnerParameter.env->DeleteLocalRef(jValue);
#endif
}

void Adjust2dx::removeGlobalCallbackParameter(std::string key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeGlobalCallbackParameter(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiRemoveGlobalCallbackParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiRemoveGlobalCallbackParameter, "com/adjust/sdk/Adjust", "removeGlobalCallbackParameter", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiRemoveGlobalCallbackParameter.env->NewStringUTF(key.c_str());
    jmiRemoveGlobalCallbackParameter.env->CallStaticVoidMethod(jmiRemoveGlobalCallbackParameter.classID, jmiRemoveGlobalCallbackParameter.methodID, jKey);
    jmiRemoveGlobalCallbackParameter.env->DeleteLocalRef(jKey);
#endif
}

void Adjust2dx::removeGlobalPartnerParameter(std::string key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeGlobalPartnerParameter(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiRemoveGlobalPartnerParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiRemoveGlobalPartnerParameter, "com/adjust/sdk/Adjust", "removeGlobalPartnerParameter", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiRemoveGlobalPartnerParameter.env->NewStringUTF(key.c_str());
    jmiRemoveGlobalPartnerParameter.env->CallStaticVoidMethod(jmiRemoveGlobalPartnerParameter.classID, jmiRemoveGlobalPartnerParameter.methodID, jKey);
    jmiRemoveGlobalPartnerParameter.env->DeleteLocalRef(jKey);
#endif
}

void Adjust2dx::removeGlobalCallbackParameters() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeGlobalCallbackParameters();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiRemoveGlobalCallbackParameters;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiRemoveGlobalCallbackParameters, "com/adjust/sdk/Adjust", "removeGlobalCallbackParameters", "()V")) {
        return;
    }
    jmiRemoveGlobalCallbackParameters.env->CallStaticVoidMethod(jmiRemoveGlobalCallbackParameters.classID, jmiRemoveGlobalCallbackParameters.methodID);
#endif
}

void Adjust2dx::removeGlobalPartnerParameters() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeGlobalPartnerParameters();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiRemoveGlobalPartnerParameters;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiRemoveGlobalPartnerParameters, "com/adjust/sdk/Adjust", "removeGlobalPartnerParameters", "()V")) {
        return;
    }
    jmiRemoveGlobalPartnerParameters.env->CallStaticVoidMethod(jmiRemoveGlobalPartnerParameters.classID, jmiRemoveGlobalPartnerParameters.methodID);
#endif
}

void Adjust2dx::trackThirdPartySharing(AdjustThirdPartySharing2dx thirdPartySharing) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackThirdPartySharing;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackThirdPartySharing, "com/adjust/sdk/Adjust", "trackThirdPartySharing", "(Lcom/adjust/sdk/AdjustThirdPartySharing;)V")) {
        return;
    }
    jmiTrackThirdPartySharing.env->CallStaticVoidMethod(jmiTrackThirdPartySharing.classID, jmiTrackThirdPartySharing.methodID, thirdPartySharing.getThirdPartySharing());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackThirdPartySharing(thirdPartySharing.getThirdPartySharing());
#endif
}

void Adjust2dx::trackMeasurementConsent(bool measurementConsent) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackMeasurementConsent;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackMeasurementConsent, "com/adjust/sdk/Adjust", "trackMeasurementConsent", "(Z)V")) {
        return;
    }
    jmiTrackMeasurementConsent.env->CallStaticVoidMethod(jmiTrackMeasurementConsent.classID, jmiTrackMeasurementConsent.methodID, measurementConsent);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackMeasurementConsent(measurementConsent);
#endif
}

void Adjust2dx::adidCallback(void(*callbackMethod)(std::string adid)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::adidCallback(callbackMethod);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setAdIdCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiGetAdIdCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAdIdCallback, "com/adjust/sdk/Adjust", "getAdId", "(Lcom/adjust/sdk/OnAdidReadListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxAdIdCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxAdIdCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxAdIdCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxAdIdCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxAdIdCallback, jmidInit);
    jmiGetAdIdCallback.env->CallStaticVoidMethod(jmiGetAdIdCallback.classID, jmiGetAdIdCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::sdkVersionCallback(void(*callbackMethod)(std::string sdkVersion)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::sdkVersionCallback(callbackMethod);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setSdkVersionCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiGetSdkVersionCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetSdkVersionCallback, "com/adjust/sdk/Adjust", "getSdkVersion", "(Lcom/adjust/sdk/OnSdkVersionReadListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxSdkVersionCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxSdkVersionCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxSdkVersionCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxSdkVersionCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxSdkVersionCallback, jmidInit);
    jmiGetSdkVersionCallback.env->CallStaticVoidMethod(jmiGetSdkVersionCallback.classID, jmiGetSdkVersionCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::attributionCallback(void(*callbackMethod)(AdjustAttribution2dx attribution)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::attributionCallback(callbackMethod);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setAttributionReadCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiGetAttributionReadCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAttributionReadCallback, "com/adjust/sdk/Adjust", "getAttribution", "(Lcom/adjust/sdk/OnAttributionReadListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxAttributionReadCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxAttributionReadCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxAttributionReadCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxAttributionReadCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxAttributionReadCallback, jmidInit);
    jmiGetAttributionReadCallback.env->CallStaticVoidMethod(jmiGetAttributionReadCallback.classID, jmiGetAttributionReadCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::trackAdRevenue(AdjustAdRevenue2dx adRevenue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackAdRevenue(adRevenue.getAdRevenue());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackAdRevenue;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackAdRevenue, "com/adjust/sdk/Adjust", "trackAdRevenue", "(Lcom/adjust/sdk/AdjustAdRevenue;)V")) {
        return;
    }
    jmiTrackAdRevenue.env->CallStaticVoidMethod(jmiTrackAdRevenue.classID, jmiTrackAdRevenue.methodID, adRevenue.getAdRevenue());
#endif
}

void Adjust2dx::processAndResolveDeeplink(AdjustDeeplink2dx deeplink,
                                          void (*resolvedLinkCallback)(std::string resolvedLink))
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::processAndResolveDeeplink(deeplink.getDeeplink(), resolvedLinkCallback);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setResolvedLinkCallbackMethod(resolvedLinkCallback);
    cocos2d::JniMethodInfo jmiProcessAndResolveDeeplink;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiProcessAndResolveDeeplink, "com/adjust/sdk/Adjust", "processAndResolveDeeplink", "(Lcom/adjust/sdk/AdjustDeeplink;Landroid/content/Context;Lcom/adjust/sdk/OnDeeplinkResolvedListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jclass clsAdjust2dxResolvedLinkCallback = jmiProcessAndResolveDeeplink.env->FindClass("com/adjust/sdk/Adjust2dxResolvedLinkCallback");
    jmethodID jmidInit = jmiProcessAndResolveDeeplink.env->GetMethodID(clsAdjust2dxResolvedLinkCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiProcessAndResolveDeeplink.env->NewObject(clsAdjust2dxResolvedLinkCallback, jmidInit);

    jmiProcessAndResolveDeeplink.env->CallStaticVoidMethod(jmiProcessAndResolveDeeplink.classID, jmiProcessAndResolveDeeplink.methodID, deeplink.getDeeplink(), jContext, jCallbackProxy);

    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiProcessAndResolveDeeplink.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::setReferrer(std::string referrer) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetReferrer;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetReferrer, "com/adjust/sdk/Adjust", "setReferrer", "(Ljava/lang/String;Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jstring jReferrer = jmiSetReferrer.env->NewStringUTF(referrer.c_str());
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiSetReferrer.env->CallStaticVoidMethod(jmiSetReferrer.classID, jmiSetReferrer.methodID, jReferrer, jContext);
    jmiSetReferrer.env->DeleteLocalRef(jReferrer);
    jmiGetContext.env->DeleteLocalRef(jContext);
#endif
}

void Adjust2dx::getGoogleAdId(void (*callbackMethod)(std::string adId)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setGoogleAdIdCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiGetAdIdCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAdIdCallback, "com/adjust/sdk/Adjust", "getGoogleAdId", "(Landroid/content/Context;Lcom/adjust/sdk/OnGoogleAdIdReadListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxGoogleAdIdCallback", "<init>", "()V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }
    
    jclass clsAdjust2dxGoogleAdIdCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxGoogleAdIdCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxGoogleAdIdCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxGoogleAdIdCallback, jmidInit);
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiGetAdIdCallback.env->CallStaticVoidMethod(jmiGetAdIdCallback.classID, jmiGetAdIdCallback.methodID, jContext, jCallbackProxy);
    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void getAmazonAdId(void (*callbackMethod)(std::string adId)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setAmazonAdIdCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiGetAdIdCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAdIdCallback, "com/adjust/sdk/Adjust", "getAmazonAdId", "(Landroid/content/Context;Lcom/adjust/sdk/OnAmazonAdIdReadListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxAmazonAdIdCallback", "<init>", "()V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jclass clsAdjust2dxAmazonAdIdCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxAmazonAdIdCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxAmazonAdIdCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxAmazonAdIdCallback, jmidInit);
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiGetAdIdCallback.env->CallStaticVoidMethod(jmiGetAdIdCallback.classID, jmiGetAdIdCallback.methodID, jContext, jCallbackProxy);
    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::onResume() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiOnResume;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiOnResume, "com/adjust/sdk/Adjust", "onResume", "()V")) {
        return;
    }
    jmiOnResume.env->CallStaticVoidMethod(jmiOnResume.classID, jmiOnResume.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackSubsessionStart();
#endif
}

void Adjust2dx::onPause() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiOnPause;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiOnPause, "com/adjust/sdk/Adjust", "onPause", "()V")) {
        return;
    }
    jmiOnPause.env->CallStaticVoidMethod(jmiOnPause.classID, jmiOnPause.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackSubsessionEnd();
#endif
}

void Adjust2dx::idfaCallback(void(*callbackMethod)(std::string idfa)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::idfaCallback(callbackMethod);
#endif
}

void Adjust2dx::requestAppTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::requestAppTrackingAuthorizationWithCompletionHandler(trackingStatusCallback);
#endif
}

int Adjust2dx::getAppTrackingAuthorizationStatus() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::getAppTrackingAuthorizationStatus();
#else
    return -1;
#endif
}

void Adjust2dx::updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool* optionalLockWindow,
                                          void (*errorCallback)(std::string error))
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::updateSkanConversionValue(conversionValue, coarseValue, optionalLockWindow, errorCallback);
#endif
}

void Adjust2dx::lastDeeplinkCallback(void(*callbackMethod)(std::string lastDeeplink)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::lastDeeplinkCallback(callbackMethod);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setLastDeeplinkCallbackMethod(callbackMethod);

    cocos2d::JniMethodInfo jmiGetLastDeeplinkCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetLastDeeplinkCallback, "com/adjust/sdk/Adjust", "getLastDeeplink", "(Landroid/content/Context;Lcom/adjust/sdk/OnLastDeeplinkReadListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dx   Callback", "<init>", "()V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jclass clsAdjust2dxLastDeeplinkCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxLastDeeplinkCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxLastDeeplinkCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxLastDeeplinkCallback, jmidInit);
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiGetLastDeeplinkCallback.env->CallStaticVoidMethod(jmiGetLastDeeplinkCallback.classID, jmiGetLastDeeplinkCallback.methodID, jContext, jCallbackProxy);
    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

void Adjust2dx::idfvCallback(void(*callbackMethod)(std::string idfv)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::idfvCallback(callbackMethod);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject getTestOptions(std::map<std::string, std::string> stringTestOptions,
                       std::map<std::string, int> intTestOptions)
{
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustTestOptions", "<init>", "()V")) {
        return NULL;
    }
    cocos2d::JniMethodInfo jmiInitBoolean;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInitBoolean, "java/lang/Boolean", "<init>", "(Z)V")) {
        return NULL;
    }

    jclass jclsBoolean = jmiInitBoolean.env->FindClass("java/lang/Boolean");
    jmethodID midInitBoolean = jmiInitBoolean.env->GetMethodID(jclsBoolean, "<init>", "(Z)V");

    cocos2d::JniMethodInfo jmiInitLong;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInitLong, "java/lang/Long", "<init>", "(J)V")) {
        return NULL;
    }
    jclass clsLong = jmiInitLong.env->FindClass("java/lang/Long");
    jmethodID midInitLong = jmiInitBoolean.env->GetMethodID(clsLong, "<init>", "(J)V");

    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return NULL;
    }
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);

    // Test options.
    jclass jclsTestOptions = jmiInit.env->FindClass("com/adjust/sdk/AdjustTestOptions");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsTestOptions, "<init>", "()V");
    jobject jTestOptions = jmiInit.env->NewObject(jclsTestOptions, jmidInit);

    // Context.
    if (intTestOptions.find("setContext") != intTestOptions.end()) {
        jfieldID jfidContext = jmiInit.env->GetFieldID(jclsTestOptions, "context", "Landroid/content/Context;");
        jmiInit.env->SetObjectField(jTestOptions, jfidContext, jContext);
    }
    jmiGetContext.env->DeleteLocalRef(jContext);

    // Base URL.
    jstring jBaseUrl = jmiInit.env->NewStringUTF(stringTestOptions["testUrlOverwrite"].c_str());
    jfieldID jfidBaseUrl = jmiInit.env->GetFieldID(jclsTestOptions, "baseUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidBaseUrl, jBaseUrl);

    // GDPR URL.
    jstring jsGdprUrl = jmiInit.env->NewStringUTF(stringTestOptions["testUrlOverwrite"].c_str());
    jfieldID jfidGdprUrl = jmiInit.env->GetFieldID(jclsTestOptions, "gdprUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidGdprUrl, jsGdprUrl);

    // Subscription URL.
    jstring jsSubscriptionUrl = jmiInit.env->NewStringUTF(stringTestOptions["testUrlOverwrite"].c_str());
    jfieldID jfidSubscriptionUrl = jmiInit.env->GetFieldID(jclsTestOptions, "subscriptionUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidSubscriptionUrl, jsSubscriptionUrl);

    // Purchase verification URL.
    jstring jsPurchaseVerificationUrl = jmiInit.env->NewStringUTF(stringTestOptions["testUrlOverwrite"].c_str());
    jfieldID jfidPurchaseVerificationUrl = jmiInit.env->GetFieldID(jclsTestOptions, "purchaseVerificationUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidPurchaseVerificationUrl, jsPurchaseVerificationUrl);

    // Base path.
    if (stringTestOptions.find("extraPath") != stringTestOptions.end()) {
        jstring jsExtraPath = jmiInit.env->NewStringUTF(stringTestOptions["extraPath"].c_str());
        jfieldID jfidBasePath = jmiInit.env->GetFieldID(jclsTestOptions, "basePath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidBasePath, jsExtraPath);
    }

    // GDPR path.
    if (stringTestOptions.find("extraPath") != stringTestOptions.end()) {
        jstring jsExtraPath = jmiInit.env->NewStringUTF(stringTestOptions["extraPath"].c_str());
        jfieldID jfidGdprPath = jmiInit.env->GetFieldID(jclsTestOptions, "gdprPath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidGdprPath, jsExtraPath);
    }

    // Subscription path.
    if (stringTestOptions.find("extraPath") != stringTestOptions.end()) {
        jstring jsExtraPath = jmiInit.env->NewStringUTF(stringTestOptions["extraPath"].c_str());
        jfieldID jfidSubscriptionPath = jmiInit.env->GetFieldID(jclsTestOptions, "subscriptionPath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidSubscriptionPath, jsExtraPath);
    }

    // Purchase verification path.
    if (stringTestOptions.find("extraPath") != stringTestOptions.end()) {
        jstring jsExtraPath = jmiInit.env->NewStringUTF(stringTestOptions["extraPath"].c_str());
        jfieldID jfidPurchaseVerificationPath = jmiInit.env->GetFieldID(jclsTestOptions, "purchaseVerificationPath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidPurchaseVerificationPath, jsExtraPath);
    }
/*  TO confirm
        there is no 'test connection options' in AdjustTestOptions, so
        it should/cannot be set here
    // Use test connection options.
    if (testOptions.find("useTestConnectionOptions") != testOptions.end()) {
        jboolean jUseTestConnectionOptions = testOptions["useTestConnectionOptions"] == "true" ? JNI_TRUE : JNI_FALSE;
        jobject jUseTestConnectionOptionsObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jUseTestConnectionOptions);
        jfieldID jfidUseTestConnectionOptions = jmiInit.env->GetFieldID(jclsTestOptions, "useTestConnectionOptions", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidUseTestConnectionOptions, jUseTestConnectionOptionsObj);
        jmiInit.env->DeleteLocalRef(jUseTestConnectionOptionsObj);
    }
*/
    // Timer interval in milliseconds.
    if (intTestOptions.find("timerIntervalInMilliseconds") != intTestOptions.end()) {
        long timerIntervalInMilliseconds = (long)intTestOptions["timerIntervalInMilliseconds"];
        jlong jTimerIntervalInMilliseconds = (jlong)(timerIntervalInMilliseconds);
        jobject jTimerIntervalInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jTimerIntervalInMilliseconds);
        jfieldID jfidTimerIntervalInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "timerIntervalInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTimerIntervalInMilliseconds, jTimerIntervalInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jTimerIntervalInMillisecondsObj);
    }

    // Timer start in milliseconds.
    if (intTestOptions.find("timerStartInMilliseconds") != intTestOptions.end()) {
        long timerStartInMilliseconds = (long)intTestOptions["timerStartInMilliseconds"];
        jlong jTimerStartInMilliseconds = (jlong)(timerStartInMilliseconds);
        jobject jTimerStartInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jTimerStartInMilliseconds);
        jfieldID jfidTimerStartInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "timerStartInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTimerStartInMilliseconds, jTimerStartInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jTimerStartInMillisecondsObj);
    }

    // Session interval in milliseconds.
    if (intTestOptions.find("sessionIntervalInMilliseconds") != intTestOptions.end()) {
        long sessionIntervalInMilliseconds = (long)intTestOptions["sessionIntervalInMilliseconds"];
        jlong jSessionIntervalInMilliseconds = (jlong)(sessionIntervalInMilliseconds);
        jobject jSessionIntervalInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jSessionIntervalInMilliseconds);
        jfieldID jfidSessionIntervalInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "sessionIntervalInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidSessionIntervalInMilliseconds, jSessionIntervalInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jSessionIntervalInMillisecondsObj);
    }

    // Sub-session interval in milliseconds.
    if (intTestOptions.find("subsessionIntervalInMilliseconds") != intTestOptions.end()) {
        long subsessionIntervalInMilliseconds = (long)intTestOptions["subsessionIntervalInMilliseconds"];
        jlong jSubsessionIntervalInMilliseconds = (jlong)(subsessionIntervalInMilliseconds);
        jobject jSubsessionIntervalInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jSubsessionIntervalInMilliseconds);
        jfieldID jfidSubsessionIntervalInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "subsessionIntervalInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidSubsessionIntervalInMilliseconds, jSubsessionIntervalInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jSubsessionIntervalInMillisecondsObj);
    }
/*
 if (command.containsParameter("doNotIgnoreSystemLifecycleBootstrap")) {
     String doNotIgnoreSystemLifecycleBootstrapString =
       command.getFirstParameterValue("doNotIgnoreSystemLifecycleBootstrap");
     Boolean doNotIgnoreSystemLifecycleBootstrap =
       Util.strictParseStringToBoolean(doNotIgnoreSystemLifecycleBootstrapString);
     if (doNotIgnoreSystemLifecycleBootstrap != null
       && doNotIgnoreSystemLifecycleBootstrap.booleanValue())
     {
         testOptions.ignoreSystemLifecycleBootstrap = false;
     }
 }
 public Boolean ignoreSystemLifecycleBootstrap = true;

 */
    // Teardown.
    if (intTestOptions.find("teardown") != intTestOptions.end()) {
        jboolean jTeardown = intTestOptions["teardown"] == 1 ? JNI_TRUE : JNI_FALSE;
        jobject jTeardownObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jTeardown);
        jfieldID jfidTeardown = jmiInit.env->GetFieldID(jclsTestOptions, "teardown", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTeardown, jTeardownObj);
        jmiInit.env->DeleteLocalRef(jTeardownObj);
    }

    // Try install referrer.
    if (intTestOptions.find("tryInstallReferrer") != intTestOptions.end()) {
        jboolean jTryInstallReferrer = intTestOptions["tryInstallReferrer"] == 1 ? JNI_TRUE : JNI_FALSE;
        jobject jTryInstallReferrerObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jTryInstallReferrer);
        jfieldID jfidTryInstallReferrer = jmiInit.env->GetFieldID(jclsTestOptions, "tryInstallReferrer", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTryInstallReferrer, jTryInstallReferrerObj);
        jmiInit.env->DeleteLocalRef(jTryInstallReferrerObj);
    }

    // No backoff wait.
    if (intTestOptions.find("noBackoffWait") != intTestOptions.end()) {
        jboolean jNoBackoffWait = intTestOptions["noBackoffWait"] == 1 ? JNI_TRUE : JNI_FALSE;
        jobject jNoBackoffWaitObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jNoBackoffWait);
        jfieldID jfidNoBackoffWait = jmiInit.env->GetFieldID(jclsTestOptions, "noBackoffWait", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidNoBackoffWait, jNoBackoffWaitObj);
        jmiInit.env->DeleteLocalRef(jNoBackoffWaitObj);
    }

    if (intTestOptions.find("doNotIgnoreSystemLifecycleBootstrap") != intTestOptions.end()) {
        if (intTestOptions["doNotIgnoreSystemLifecycleBootstrap"] == 1) {
            jboolean jIgnoreSystemLifecycleBootstrap = JNI_FALSE;
            jobject jIIgnoreSystemLifecycleBootstrapObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jIgnoreSystemLifecycleBootstrap);
            jfieldID jfidIgnoreSystemLifecycleBootstrap = jmiInit.env->GetFieldID(jclsTestOptions, "ignoreSystemLifecycleBootstrap", "Ljava/lang/Boolean;");
            jmiInit.env->SetObjectField(jTestOptions, jfidIgnoreSystemLifecycleBootstrap, jIIgnoreSystemLifecycleBootstrapObj);
            jmiInit.env->DeleteLocalRef(jIIgnoreSystemLifecycleBootstrapObj);
        }
    }

    return jTestOptions;
}
#endif

void Adjust2dx::setTestOptions(std::map<std::string, std::string> stringTestOptions,
                               std::map<std::string, int> intTestOptions)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject jTestOptions = getTestOptions(stringTestOptions, intTestOptions);
    cocos2d::JniMethodInfo jmiSetTestOptions;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetTestOptions, "com/adjust/sdk/Adjust", "setTestOptions", "(Lcom/adjust/sdk/AdjustTestOptions;)V")) {
        return;
    }
    jmiSetTestOptions.env->CallStaticVoidMethod(jmiSetTestOptions.classID, jmiSetTestOptions.methodID, jTestOptions);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setTestOptions(stringTestOptions, intTestOptions);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void Adjust2dx::teardown() {
    ADJAdjust2dx::teardown();
}
#endif
