//  AdjustConfig2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "AdjustConfig2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "AdjustProxy2dx.h"
#endif

const std::string AdjustSdkPrefix2dx = "cocos2d-x5.0.1";

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
            enumValue = "SUPPRESS";
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

void AdjustConfig2dx::enableSendingInBackground() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEnableSendingInBackground;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEnableSendingInBackground, "com/adjust/sdk/AdjustConfig", "enableSendingInBackground", "()V")) {
        return;
    }

    jmiEnableSendingInBackground.env->CallVoidMethod(config, jmiEnableSendingInBackground.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.enableSendingInBackground();
    }
#endif
}

void AdjustConfig2dx::enableCostDataInAttribution() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEnableCostDataInAttribution;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEnableCostDataInAttribution, "com/adjust/sdk/AdjustConfig", "enableCostDataInAttribution", "()V")) {
        return;
    }

    jmiEnableCostDataInAttribution.env->CallVoidMethod(config, jmiEnableCostDataInAttribution.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.enableCostDataInAttribution();
    }
#endif
}

void AdjustConfig2dx::disableIdfaReading() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.disableIdfaReading();
    }
#endif
}

void AdjustConfig2dx::disableIdfvReading() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.disableIdfvReading();
    }
#endif
}

void AdjustConfig2dx::disableAdServices() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.disableAdServices();
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

void AdjustConfig2dx::setExternalDeviceId(std::string externalDeviceId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetExternalDeviceId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetExternalDeviceId, "com/adjust/sdk/AdjustConfig", "setExternalDeviceId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jExternalDeviceId = jmiSetExternalDeviceId.env->NewStringUTF(externalDeviceId.c_str());
    jmiSetExternalDeviceId.env->CallVoidMethod(config, jmiSetExternalDeviceId.methodID, jExternalDeviceId);
    jmiSetExternalDeviceId.env->DeleteLocalRef(jExternalDeviceId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setExternalDeviceId(externalDeviceId);
    }
#endif
}

void AdjustConfig2dx::setUrlStrategy(std::vector<std::string> urlStrategyDomains,
                                     bool useSubdomains,
                                     bool isDataResidency)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo jmiInitArrayList;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInitArrayList, "java/util/ArrayList", "<init>", "()V")) {
        return;
    }

    jclass clsArrayList = jmiInitArrayList.env->FindClass("java/util/ArrayList");
    jmethodID jmidInit = jmiInitArrayList.env->GetMethodID(clsArrayList, "<init>", "()V");
    jobject jArrayList = jmiInitArrayList.env->NewObject(clsArrayList, jmidInit);

    cocos2d::JniMethodInfo jmiAdd;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAdd, "java/util/ArrayList", "add", "(Ljava/lang/Object;)Z")) {
        return;
    }

    for (std::vector<std::string>::iterator toIterator = urlStrategyDomains.begin();
         toIterator != urlStrategyDomains.end(); toIterator++)
    {
        std::string urlStrategyDomain = (*toIterator);
        jstring jElement = jmiAdd.env->NewStringUTF(urlStrategyDomain.c_str());

        jboolean jReturnValue = jmiAdd.env->CallBooleanMethod(jArrayList, jmiAdd.methodID, jElement);

        jmiAdd.env->DeleteLocalRef(jElement);
        //jmiAdd.env->DeleteLocalRef(jReturnValue);
    }

    cocos2d::JniMethodInfo jmiSetUrlStrategy;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetUrlStrategy, "com/adjust/sdk/AdjustConfig", "setUrlStrategy", "(Ljava/util/List;ZZ)V")) {
        return;
    }

    jboolean jUseSubdomains = useSubdomains ? JNI_TRUE : JNI_FALSE;
    jboolean jIsDataResidency = isDataResidency ? JNI_TRUE : JNI_FALSE;

    jmiSetUrlStrategy.env->CallVoidMethod(config, jmiSetUrlStrategy.methodID, jArrayList, jUseSubdomains, jIsDataResidency);

    jmiSetUrlStrategy.env->DeleteLocalRef(jArrayList);
    //jmiSetUrlStrategy.env->DeleteLocalRef(jUseSubdomains);
    //jmiSetUrlStrategy.env->DeleteLocalRef(jIsDataResidency);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setUrlStrategy(urlStrategyDomains, useSubdomains, isDataResidency);
    }
#endif
}

void AdjustConfig2dx::enablePreinstallTracking() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEnablePreinstallTracking;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEnablePreinstallTracking, "com/adjust/sdk/AdjustConfig", "enablePreinstallTracking", "()V")) {
        return;
    }

    jmiEnablePreinstallTracking.env->CallVoidMethod(config, jmiEnablePreinstallTracking.methodID);
#endif
}

void AdjustConfig2dx::setPreinstallFilePath(std::string externalDeviceId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetExternalDeviceId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetExternalDeviceId, "com/adjust/sdk/AdjustConfig", "setExternalDeviceId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jExternalDeviceId = jmiSetExternalDeviceId.env->NewStringUTF(externalDeviceId.c_str());
    jmiSetExternalDeviceId.env->CallVoidMethod(config, jmiSetExternalDeviceId.methodID, jExternalDeviceId);
    jmiSetExternalDeviceId.env->DeleteLocalRef(jExternalDeviceId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setExternalDeviceId(externalDeviceId);
    }
#endif
}

void AdjustConfig2dx::disableSkanAttribution() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.disableSkanAttribution();
    }
#endif
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

void AdjustConfig2dx::setAttributionCallback(void(*callback)(AdjustAttribution2dx attribution)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setAttributionCallbackMethod(callback);
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
        config.setAttributionCallback(callback);
    }
#endif
}

void AdjustConfig2dx::setEventSuccessCallback(void(*callback)(AdjustEventSuccess2dx eventSuccess)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setEventTrackingSucceededCallbackMethod(callback);
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
        config.setEventSuccessCallback(callback);
    }
#endif
}

void AdjustConfig2dx::setEventFailureCallback(void(*callback)(AdjustEventFailure2dx eventFailure)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setEventTrackingFailedCallbackMethod(callback);
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
        config.setEventFailureCallback(callback);
    }
#endif
}

void AdjustConfig2dx::setSessionSuccessCallback(void(*callback)(AdjustSessionSuccess2dx sessionSuccess)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setSessionTrackingSucceededCallbackMethod(callback);
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
        config.setSessionSuccessCallback(callback);
    }
#endif
}

void AdjustConfig2dx::setSessionFailureCallback(void(*callback)(AdjustSessionFailure2dx sessionFailure)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setSessionTrackingFailedCallbackMethod(callback);
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
        config.setSessionFailureCallback(callback);
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
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetCallback, "com/adjust/sdk/AdjustConfig", "setOnDeferredDeeplinkResponseListener", "(Lcom/adjust/sdk/OnDeferredDeeplinkResponseListener;)V")) {
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

void AdjustConfig2dx::setSkanUpdatedCallback(void (*callback)(std::unordered_map<std::string, std::string> data)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSkanUpdatedCallback(callback);
    }
#endif
}

void AdjustConfig2dx::enableDeviceIdsReadingOnce() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEnableDeviceIdsReadingOnce;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEnableDeviceIdsReadingOnce, "com/adjust/sdk/AdjustConfig", "enableDeviceIdsReadingOnce", "()V")) {
        return;
    }
    jmiEnableDeviceIdsReadingOnce.env->CallVoidMethod(config, jmiEnableDeviceIdsReadingOnce.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.enableDeviceIdsReadingOnce();
    }
#endif
}

void AdjustConfig2dx::enableCoppaCompliance() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEnableCoppaCompliance;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEnableCoppaCompliance, "com/adjust/sdk/AdjustConfig", "enableCoppaCompliance", "()V")) {
        return;
    }
    jmiEnableCoppaCompliance.env->CallVoidMethod(config, jmiEnableCoppaCompliance.methodID);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.enableCoppaCompliance();
    }
#endif
}

void AdjustConfig2dx::setEventDeduplicationIdsMaxSize(int eventDeduplicationIdsMaxSize) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEventDeduplicationIdsMaxSize;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEventDeduplicationIdsMaxSize, "com/adjust/sdk/AdjustConfig", "setEventDeduplicationIdsMaxSize", "(Ljava/lang/Integer;)V")) {
        return;
    }

    jclass clsInteger = jmiEventDeduplicationIdsMaxSize.env->FindClass("java/lang/Integer");
    jmethodID midInit = jmiEventDeduplicationIdsMaxSize.env->GetMethodID(clsInteger, "<init>", "(I)V");
    jobject jEventDeduplicationIdsMaxSize = jmiEventDeduplicationIdsMaxSize.env->NewObject(clsInteger, midInit, eventDeduplicationIdsMaxSize);

    jmiEventDeduplicationIdsMaxSize.env->CallVoidMethod(config, jmiEventDeduplicationIdsMaxSize.methodID, jEventDeduplicationIdsMaxSize);

    jmiEventDeduplicationIdsMaxSize.env->DeleteLocalRef(jEventDeduplicationIdsMaxSize);


#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventDeduplicationIdsMaxSize(eventDeduplicationIdsMaxSize);
    }
#endif
}

void AdjustConfig2dx::enablePlayStoreKidsCompliance() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiEnablePlayStoreKidsCompliance;
    if (!cocos2d::JniHelper::getMethodInfo(jmiEnablePlayStoreKidsCompliance, "com/adjust/sdk/AdjustConfig", "enablePlayStoreKidsCompliance", "()V")) {
        return;
    }
    jmiEnablePlayStoreKidsCompliance.env->CallVoidMethod(config, jmiEnablePlayStoreKidsCompliance.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
}

void AdjustConfig2dx::setFbAppId(std::string fbAppId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSetFbAppId;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSetFbAppId, "com/adjust/sdk/AdjustConfig", "setFbAppId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jFbAppId = jmiSetFbAppId.env->NewStringUTF(fbAppId.c_str());
    jmiSetFbAppId.env->CallVoidMethod(config, jmiSetFbAppId.methodID, jFbAppId);
    jmiSetFbAppId.env->DeleteLocalRef(jFbAppId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
}

void AdjustConfig2dx::enableLinkMe() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.enableLinkMe();
    }
#endif
}

void AdjustConfig2dx::setAttConsentWaitingInterval(int numberOfSeconds) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setAttConsentWaitingInterval(numberOfSeconds);
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
