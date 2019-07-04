
//  AdjustConfig2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "AdjustProxy2dx.h"
#endif

#define COCOS2D_DEBUG 1
#include "AdjustConfig2dx.h"
USING_NS_CC;

const std::string AdjustSdkPrefix2dx = "cocos2d-x4.18.0";

void AdjustConfig2dx::initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustConfig", "<init>", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Z)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetSdkPrefix;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetSdkPrefix, "com/adjust/sdk/AdjustConfig", "setSdkPrefix", "(Ljava/lang/String;)V")) {
        return;
    }

    jclass jclsAdjustConfig = jmiInit.env->FindClass("com/adjust/sdk/AdjustConfig");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustConfig, "<init>", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Z)V");
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jstring jAppToken = jmiInit.env->NewStringUTF(appToken.c_str());
    jstring jEnvironment = jmiInit.env->NewStringUTF(environment.c_str());
    jobject tmp = jmiInit.env->NewObject(jclsAdjustConfig, jmidInit, jContext, jAppToken, jEnvironment, allowSuppressLogLevel);
    this->config = jmiInit.env->NewGlobalRef(tmp);
    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jAppToken);
    jmiInit.env->DeleteLocalRef(jEnvironment);
    jstring jSdkPrefix = jmiSetSdkPrefix.env->NewStringUTF(AdjustSdkPrefix2dx.c_str());
    jmiSetSdkPrefix.env->CallVoidMethod(config, jmiSetSdkPrefix.methodID, jSdkPrefix);
    jmiSetSdkPrefix.env->DeleteLocalRef(jSdkPrefix);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    config = ADJConfig2dx(appToken, environment, allowSuppressLogLevel, AdjustSdkPrefix2dx);
    isConfigSet = true;
#endif
}

void AdjustConfig2dx::setLogLevel(AdjustLogLevel2dx logLevel, void(*logCallback)(const char* log)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetLogLevel;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetLogLevel, "com/adjust/sdk/AdjustConfig", "setLogLevel", "(Lcom/adjust/sdk/LogLevel;)V")) {
        return;
    }

    jclass clsLogLevel = jmiSetLogLevel.env->FindClass("com/adjust/sdk/LogLevel");
    std::string enumValue;
    switch (logLevel) {
        case AdjustLogLevel2dxSuppress: {
            enumValue = "SUPRESS";
            break;
        }
        case AdjustLogLevel2dxAssert: {
            enumValue = "ASSERT";
            break;
        }
        case AdjustLogLevel2dxError: {
            enumValue = "ERROR";
            break;
        }
        case AdjustLogLevel2dxWarn: {
            enumValue = "WARN";
            break;
        }
        case AdjustLogLevel2dxInfo: {
            enumValue = "INFO";
            break;
        }
        case AdjustLogLevel2dxDebug: {
            enumValue = "DEBUG";
            break;
        }
        case AdjustLogLevel2dxVerbose: {
            enumValue = "VERBOSE";
            break;
        }
        default: {
            enumValue = "INFO";
            break;
        }
    }

    jfieldID jfidValue = jmiSetLogLevel.env->GetStaticFieldID(clsLogLevel, enumValue.c_str(), "Lcom/adjust/sdk/LogLevel;");
    jobject jLogLevel = jmiSetLogLevel.env->GetStaticObjectField(clsLogLevel, jfidValue);
    jmiSetLogLevel.env->CallVoidMethod(config, jmiSetLogLevel.methodID, jLogLevel);
    jmiSetLogLevel.env->DeleteLocalRef(jLogLevel);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setLogLevel((ADJLogLevel2dx)logLevel);
    }
#endif
}

void AdjustConfig2dx::setDelayStart(double delayStart) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetDelayStart;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetDelayStart, "com/adjust/sdk/AdjustConfig", "setDelayStart", "(D)V")) {
        return;
    }

    jmiSetDelayStart.env->CallVoidMethod(config, jmiSetDelayStart.methodID, delayStart);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDelayStart(delayStart);
    }
#endif
}

void AdjustConfig2dx::setSendInBackground(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetSendInBackground;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetSendInBackground, "com/adjust/sdk/AdjustConfig", "setSendInBackground", "(Z)V")) {
        return;
    }

    jmiSetSendInBackground.env->CallVoidMethod(config, jmiSetSendInBackground.methodID, isEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSendInBackground(isEnabled);
    }
#endif
}

void AdjustConfig2dx::setEventBufferingEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetEventBufferingEnabled;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetEventBufferingEnabled, "com/adjust/sdk/AdjustConfig", "setEventBufferingEnabled", "(Ljava/lang/Boolean;)V")) {
        return;
    }

    jclass jclsBoolean = jmiSetEventBufferingEnabled.env->FindClass("java/lang/Boolean");
    jmethodID jmidValueOf = jmiSetEventBufferingEnabled.env->GetStaticMethodID(jclsBoolean, "valueOf", "(Z)Ljava/lang/Boolean;");
    jobject jIsEnabled = jmiSetEventBufferingEnabled.env->CallStaticObjectMethod(jclsBoolean, jmidValueOf, isEnabled);
    jmiSetEventBufferingEnabled.env->CallVoidMethod(config, jmiSetEventBufferingEnabled.methodID, jIsEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventBufferingEnabled(isEnabled);
    }
#endif
}

void AdjustConfig2dx::setUserAgent(std::string userAgent) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetUserAgent;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetUserAgent, "com/adjust/sdk/AdjustConfig", "setUserAgent", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jUserAgent = jmiSetUserAgent.env->NewStringUTF(userAgent.c_str());
    jmiSetUserAgent.env->CallVoidMethod(config, jmiSetUserAgent.methodID, jUserAgent);
    jmiSetUserAgent.env->DeleteLocalRef(jUserAgent);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setUserAgent(userAgent);
    }
#endif
}

void AdjustConfig2dx::setDefaultTracker(std::string defaultTracker) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetDefaultTracker;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetDefaultTracker, "com/adjust/sdk/AdjustConfig", "setDefaultTracker", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jDefaultTracker = jmiSetDefaultTracker.env->NewStringUTF(defaultTracker.c_str());
    jmiSetDefaultTracker.env->CallVoidMethod(config, jmiSetDefaultTracker.methodID, jDefaultTracker);
    jmiSetDefaultTracker.env->DeleteLocalRef(jDefaultTracker);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDefaultTracker(defaultTracker);
    }
#endif
}

void AdjustConfig2dx::setAppSecret(unsigned long long secretId, unsigned long long info1, unsigned long long info2, unsigned long long info3, unsigned long long info4) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetAppSecret;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetAppSecret, "com/adjust/sdk/AdjustConfig", "setAppSecret", "(JJJJJ)V")) {
        return;
    }
    jmiSetAppSecret.env->CallVoidMethod(config, jmiSetAppSecret.methodID, secretId, info1, info2, info3, info4);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setAppSecret(secretId, info1, info2, info3, info4);
    }
#endif
}

void AdjustConfig2dx::setDeviceKnown(bool isDeviceKnown) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetDeviceKnown;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetDeviceKnown, "com/adjust/sdk/AdjustConfig", "setDeviceKnown", "(Z)V")) {
        return;
    }
    jmiSetDeviceKnown.env->CallVoidMethod(config, jmiSetDeviceKnown.methodID, isDeviceKnown);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setIsDeviceKnown(isDeviceKnown);
    }
#endif
}

void AdjustConfig2dx::setReadMobileEquipmentIdentity(bool readMobileEquipmentIdentity) {
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//     if (config == NULL) {
//         return;
//     }
//     cocos2d::JniMethodInfo jmiSetReadMobileEquipmentIdentity;
//     if (!cocos2d::JniHelper::getMethodInfo(jmiSetReadMobileEquipmentIdentity, "com/adjust/sdk/AdjustConfig", "setReadMobileEquipmentIdentity", "(Z)V")) {
//         return;
//     }
//     jmiSetReadMobileEquipmentIdentity.env->CallVoidMethod(config, jmiSetReadMobileEquipmentIdentity.methodID, readMobileEquipmentIdentity);
// #endif
}

void AdjustConfig2dx::setProcessName(std::string processName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetProcessName;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetProcessName, "com/adjust/sdk/AdjustConfig", "setProcessName", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jProcessName = jmiSetProcessName.env->NewStringUTF(processName.c_str());
    jmiSetProcessName.env->CallVoidMethod(config, jmiSetProcessName.methodID, jProcessName);
    jmiSetProcessName.env->DeleteLocalRef(jProcessName);
#endif
}

void AdjustConfig2dx::setAttributionCallback(void(*attributionCallback)(AdjustAttribution2dx attribution)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setAttributionCallbackMethod(attributionCallback);
    cocos2d::JniMethodInfo jmiSetCallback;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnAttributionChangedListener", "(Lcom/adjust/sdk/OnAttributionChangedListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxAttributionCallback", "<init>", "()V")) {
        return;
    }

    jclass jjclsAdjust2dxAttributionCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxAttributionCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jjclsAdjust2dxAttributionCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(jjclsAdjust2dxAttributionCallback, jmidInit);
    jmiSetCallback.env->CallVoidMethod(config, jmiSetCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setAttributionCallback(attributionCallback);
    }
#endif
}

void AdjustConfig2dx::setEventSuccessCallback(void(*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setEventTrackingSucceededCallbackMethod(eventSuccessCallback);
    cocos2d::JniMethodInfo jmiSetCallback;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnEventTrackingSucceededListener", "(Lcom/adjust/sdk/OnEventTrackingSucceededListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxEventTrackingSucceededCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxEventTrackingSucceededCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxEventTrackingSucceededCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjust2dxEventTrackingSucceededCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(jclsAdjust2dxEventTrackingSucceededCallback, jmidInit);
    jmiSetCallback.env->CallVoidMethod(config, jmiSetCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventSuccessCallback(eventSuccessCallback);
    }
#endif
}

void AdjustConfig2dx::setEventFailureCallback(void(*eventFailureCallback)(AdjustEventFailure2dx eventFailure)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setEventTrackingFailedCallbackMethod(eventFailureCallback);
    cocos2d::JniMethodInfo jmiSetCallback;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnEventTrackingFailedListener", "(Lcom/adjust/sdk/OnEventTrackingFailedListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxEventTrackingFailedCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxEventTrackingFailedCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxEventTrackingFailedCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjust2dxEventTrackingFailedCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(jclsAdjust2dxEventTrackingFailedCallback, jmidInit);
    jmiSetCallback.env->CallVoidMethod(config, jmiSetCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventFailureCallback(eventFailureCallback);
    }
#endif
}

void AdjustConfig2dx::setSessionSuccessCallback(void(*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setSessionTrackingSucceededCallbackMethod(sessionSuccessCallback);
    cocos2d::JniMethodInfo jmiSetCallback;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnSessionTrackingSucceededListener", "(Lcom/adjust/sdk/OnSessionTrackingSucceededListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxSessionTrackingSucceededCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxSessionTrackingSucceededCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxSessionTrackingSucceededCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjust2dxSessionTrackingSucceededCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(jclsAdjust2dxSessionTrackingSucceededCallback, jmidInit);
    jmiSetCallback.env->CallVoidMethod(config, jmiSetCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSessionSuccessCallback(sessionSuccessCallback);
    }
#endif
}

void AdjustConfig2dx::setSessionFailureCallback(void(*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setSessionTrackingFailedCallbackMethod(sessionFailureCallback);
    cocos2d::JniMethodInfo jmiSetCallback;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnSessionTrackingFailedListener", "(Lcom/adjust/sdk/OnSessionTrackingFailedListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxSessionTrackingFailedCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxSessionTrackingFailedCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxSessionTrackingFailedCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjust2dxSessionTrackingFailedCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(jclsAdjust2dxSessionTrackingFailedCallback, jmidInit);
    jmiSetCallback.env->CallVoidMethod(config, jmiSetCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSessionFailureCallback(sessionFailureCallback);
    }
#endif
}

void AdjustConfig2dx::setDeferredDeeplinkCallback(bool(*deferredDeeplinkCallback)(std::string deeplink)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setDeferredDeeplinkCallbackMethod(deferredDeeplinkCallback);
    cocos2d::JniMethodInfo jmiSetCallback;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnDeeplinkResponseListener", "(Lcom/adjust/sdk/OnDeeplinkResponseListener;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxDeferredDeeplinkCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxDeferredDeeplinkCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxDeferredDeeplinkCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjust2dxDeferredDeeplinkCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(jclsAdjust2dxDeferredDeeplinkCallback, jmidInit);
    jmiSetCallback.env->CallVoidMethod(config, jmiSetCallback.methodID, jCallbackProxy);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDeferredDeeplinkCallback(deferredDeeplinkCallback);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustConfig2dx::getConfig() {
    return config;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJConfig2dx AdjustConfig2dx::getConfig() {
    return config;
}
#endif

