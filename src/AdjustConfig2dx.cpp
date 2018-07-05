
//  AdjustConfig2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "AdjustProxy2dx.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "cocos2d.h"
#include <windows.h>
#include <fstream>
USING_NS_CC;
#endif

#define COCOS2D_DEBUG 1
#include "AdjustConfig2dx.h"
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
AdjustConfig2dx::AttributionCallback AdjustConfig2dx::attributionCallbackSaved = NULL;

static unsigned char* readBuffer;

static void attributionCallbackGlobal(
    const char* trackerToken,
    const char* trackerName,
    const char* network,
    const char* campaign,
    const char* adgroup,
    const char* creative,
    const char* clickLabel) {
    std::string trackerTokenAsString;
    std::string trackerNameAsString;
    std::string networkAsString;
    std::string campaignAsString;
    std::string adgroupAsString;
    std::string creativeAsString;
    std::string clickLabelAsString;

    if (trackerToken != NULL) {
        trackerTokenAsString = std::string(trackerToken);
    }

    if (trackerName != NULL) {
        trackerNameAsString = std::string(trackerName);
    }

    if (network != NULL) {
        networkAsString = std::string(network);
    }

    if (campaign != NULL) {
        campaignAsString = std::string(campaign);
    }

    if (adgroup != NULL) {
        adgroupAsString = std::string(adgroup);
    }

    if (creative != NULL) {
        creativeAsString = std::string(creative);
    }

    if (clickLabel != NULL) {
        clickLabelAsString = std::string(clickLabel);
    }

    AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(trackerTokenAsString, trackerNameAsString, networkAsString, campaignAsString, adgroupAsString, creativeAsString, clickLabelAsString);
    AdjustConfig2dx::triggerSavedAttributionCallback(attribution2dx);
}

static void fileWriteCallback(const char* fileName, const char* newContent) {
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath().append(std::string(fileName));
    FILE *fp = fopen(path.c_str(), "w");

    if (!fp) {
        return;
    }

    fputs(newContent, fp);
    fclose(fp);
}

static int fileReadCallback(const char* fileName, int* size) {
    ssize_t fileSize = 0;
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath().append(fileName);
    CCLog(filePath.c_str());

    readBuffer = CCFileUtils::sharedFileUtils()->getFileData(filePath.c_str(), "r", &fileSize);
    *size = fileSize;

    return (int)readBuffer;
}
#endif

void AdjustConfig2dx::initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel) {
    std::string sdkPrefix = "cocos2d-x4.14.0";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/AdjustConfig", "<init>", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Z)V")) {
        return;
    }

    cocos2d::JniMethodInfo miGetContext;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    // Set SDK prefix.
    cocos2d::JniMethodInfo miSetSdkPrefix;

    if (!cocos2d::JniHelper::getMethodInfo(miSetSdkPrefix, "com/adjust/sdk/AdjustConfig", "setSdkPrefix", "(Ljava/lang/String;)V")) {
        return;
    }

    jclass clsAdjustConfig = miInit.env->FindClass("com/adjust/sdk/AdjustConfig");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjustConfig, "<init>", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Z)V");

    // Get context and initialize config object.
    jobject jContext = (jobject)miGetContext.env->CallStaticObjectMethod(miGetContext.classID, miGetContext.methodID);
    jstring jAppToken = miInit.env->NewStringUTF(appToken.c_str());
    jstring jEnvironment = miInit.env->NewStringUTF(environment.c_str());

    jobject tmp = miInit.env->NewObject(clsAdjustConfig, midInit, jContext, jAppToken, jEnvironment, allowSuppressLogLevel);
    this->config = cocos2d::JniHelper::getEnv()->NewGlobalRef(tmp);

    miGetContext.env->DeleteLocalRef(jContext);
    miInit.env->DeleteLocalRef(jAppToken);
    miInit.env->DeleteLocalRef(jEnvironment);

    jstring jSdkPrefix = miSetSdkPrefix.env->NewStringUTF(sdkPrefix.c_str());

    miSetSdkPrefix.env->CallVoidMethod(config, miSetSdkPrefix.methodID, jSdkPrefix);

    miSetSdkPrefix.env->DeleteLocalRef(jSdkPrefix);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    config = ADJConfig2dx(appToken, environment, allowSuppressLogLevel, sdkPrefix);
    isConfigSet = true;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::wstring wstrAppToken = std::wstring(appToken.begin(), appToken.end());
    std::wstring wstrEnvironment = std::wstring(environment.begin(), environment.end());
    const wchar_t* wcharAppToken = wstrAppToken.c_str();
    const wchar_t* wcharEnvironment = wstrEnvironment.c_str();

    config = ref new WRTAdjustConfig(ref new Platform::String(wcharAppToken), ref new Platform::String(wcharEnvironment));
    config->SetFileWritingCallback((int64)&fileWriteCallback);
    config->SetFileReadingCallback((int64)&fileReadCallback);

    isConfigSet = true;
#endif
}

void AdjustConfig2dx::setLogLevel(AdjustLogLevel2dx logLevel, void(*logCallback)(const char* log)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetLogLevel;

    if (!cocos2d::JniHelper::getMethodInfo(miSetLogLevel, "com/adjust/sdk/AdjustConfig", "setLogLevel", "(Lcom/adjust/sdk/LogLevel;)V")) {
        return;
    }

    jclass clsLogLevel = miSetLogLevel.env->FindClass("com/adjust/sdk/LogLevel");

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

    jfieldID fidValue = miSetLogLevel.env->GetStaticFieldID(clsLogLevel, enumValue.c_str(), "Lcom/adjust/sdk/LogLevel;");
    jobject jLogLevel = miSetLogLevel.env->GetStaticObjectField(clsLogLevel, fidValue);

    miSetLogLevel.env->CallVoidMethod(config, miSetLogLevel.methodID, jLogLevel);

    miSetLogLevel.env->DeleteLocalRef(jLogLevel);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setLogLevel((ADJLogLevel2dx)logLevel);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isConfigSet) {
        config->SetLogLevel(logLevel, (int64)logCallback);
    }
#endif
}

void AdjustConfig2dx::setDelayStart(double delayStart) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetDelayStart;

    if (!cocos2d::JniHelper::getMethodInfo(miSetDelayStart, "com/adjust/sdk/AdjustConfig", "setDelayStart", "(D)V")) {
        return;
    }

    miSetDelayStart.env->CallVoidMethod(config, miSetDelayStart.methodID, delayStart);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDelayStart(delayStart);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setSendInBackground(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetSendInBackground;

    if (!cocos2d::JniHelper::getMethodInfo(miSetSendInBackground, "com/adjust/sdk/AdjustConfig", "setSendInBackground", "(Z)V")) {
        return;
    }

    miSetSendInBackground.env->CallVoidMethod(config, miSetSendInBackground.methodID, isEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSendInBackground(isEnabled);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setEventBufferingEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetEventBufferingEnabled;

    if (!cocos2d::JniHelper::getMethodInfo(miSetEventBufferingEnabled, "com/adjust/sdk/AdjustConfig", "setEventBufferingEnabled", "(Ljava/lang/Boolean;)V")) {
        return;
    }

    jclass jcBoolean = miSetEventBufferingEnabled.env->FindClass("java/lang/Boolean");
    jmethodID midValueOf = miSetEventBufferingEnabled.env->GetStaticMethodID(jcBoolean, "valueOf", "(Z)Ljava/lang/Boolean;");
    jobject jIsEnabled = miSetEventBufferingEnabled.env->CallStaticObjectMethod(jcBoolean, midValueOf, isEnabled);

    miSetEventBufferingEnabled.env->CallVoidMethod(config, miSetEventBufferingEnabled.methodID, jIsEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventBufferingEnabled(isEnabled);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isConfigSet) {
        config->SetEventBufferingEnabled(isEnabled);
    }
#endif
}

void AdjustConfig2dx::setUserAgent(std::string userAgent) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miSetUserAgent;

    if (!cocos2d::JniHelper::getMethodInfo(miSetUserAgent, "com/adjust/sdk/AdjustConfig", "setUserAgent", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jUserAgent = miSetUserAgent.env->NewStringUTF(userAgent.c_str());

    miSetUserAgent.env->CallVoidMethod(config, miSetUserAgent.methodID, jUserAgent);

    miSetUserAgent.env->DeleteLocalRef(jUserAgent);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setUserAgent(userAgent);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#endif
}

void AdjustConfig2dx::setDefaultTracker(std::string defaultTracker) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetDefaultTracker;

    if (!cocos2d::JniHelper::getMethodInfo(miSetDefaultTracker, "com/adjust/sdk/AdjustConfig", "setDefaultTracker", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jDefaultTracker = miSetDefaultTracker.env->NewStringUTF(defaultTracker.c_str());

    miSetDefaultTracker.env->CallVoidMethod(config, miSetDefaultTracker.methodID, jDefaultTracker);

    miSetDefaultTracker.env->DeleteLocalRef(jDefaultTracker);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDefaultTracker(defaultTracker);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isConfigSet) {
        std::wstring wstrDefaultTracker = std::wstring(defaultTracker.begin(), defaultTracker.end());
        const wchar_t* wcharDefaultTracker = wstrDefaultTracker.c_str();
        config->SetDefaultTracker(ref new Platform::String(wcharDefaultTracker));
    }
#endif
}

void AdjustConfig2dx::setAppSecret(unsigned long long secretId, unsigned long long info1, unsigned long long info2, unsigned long long info3, unsigned long long info4) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetAppSecret;

    if (!cocos2d::JniHelper::getMethodInfo(miSetAppSecret, "com/adjust/sdk/AdjustConfig", "setAppSecret", "(JJJJJ)V")) {
        return;
    }

    miSetAppSecret.env->CallVoidMethod(config, miSetAppSecret.methodID, secretId, info1, info2, info3, info4);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setAppSecret(secretId, info1, info2, info3, info4);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setDeviceKnown(bool isDeviceKnown) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetDeviceKnown;

    if (!cocos2d::JniHelper::getMethodInfo(miSetDeviceKnown, "com/adjust/sdk/AdjustConfig", "setDeviceKnown", "(Z)V")) {
        return;
    }

    miSetDeviceKnown.env->CallVoidMethod(config, miSetDeviceKnown.methodID, isDeviceKnown);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setIsDeviceKnown(isDeviceKnown);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setReadMobileEquipmentIdentity(bool readMobileEquipmentIdentity) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetReadMobileEquipmentIdentity;

    if (!cocos2d::JniHelper::getMethodInfo(miSetReadMobileEquipmentIdentity, "com/adjust/sdk/AdjustConfig", "setReadMobileEquipmentIdentity", "(Z)V")) {
        return;
    }

    miSetReadMobileEquipmentIdentity.env->CallVoidMethod(config, miSetReadMobileEquipmentIdentity.methodID, readMobileEquipmentIdentity);
#endif
}

void AdjustConfig2dx::setProcessName(std::string processName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetProcessName;

    if (!cocos2d::JniHelper::getMethodInfo(miSetProcessName, "com/adjust/sdk/AdjustConfig", "setProcessName", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jProcessName = miSetProcessName.env->NewStringUTF(processName.c_str());

    miSetProcessName.env->CallVoidMethod(config, miSetProcessName.methodID, jProcessName);

    miSetProcessName.env->DeleteLocalRef(jProcessName);
#endif
}

void AdjustConfig2dx::setAttributionCallback(void(*attributionCallback)(AdjustAttribution2dx attribution)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setAttributionCallbackMethod(attributionCallback);

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnAttributionChangedListener", "(Lcom/adjust/sdk/OnAttributionChangedListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxAttributionCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxAttributionCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxAttributionCallback");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxAttributionCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxAttributionCallback, midInit);

    miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

    miInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setAttributionCallback(attributionCallback);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isConfigSet) {
        attributionCallbackSaved = attributionCallback;
        config->SetAttributionCallback((int64)&attributionCallbackGlobal);
    }
#endif
}

void AdjustConfig2dx::setEventSuccessCallback(void(*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setEventTrackingSucceededCallbackMethod(eventSuccessCallback);

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnEventTrackingSucceededListener", "(Lcom/adjust/sdk/OnEventTrackingSucceededListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxEventTrackingSucceededCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxEventTrackingSucceededCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxEventTrackingSucceededCallback");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxEventTrackingSucceededCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxEventTrackingSucceededCallback, midInit);

    miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

    miInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventSuccessCallback(eventSuccessCallback);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setEventFailureCallback(void(*eventFailureCallback)(AdjustEventFailure2dx eventFailure)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setEventTrackingFailedCallbackMethod(eventFailureCallback);

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnEventTrackingFailedListener", "(Lcom/adjust/sdk/OnEventTrackingFailedListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxEventTrackingFailedCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxEventTrackingFailedCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxEventTrackingFailedCallback");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxEventTrackingFailedCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxEventTrackingFailedCallback, midInit);

    miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

    miInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventFailureCallback(eventFailureCallback);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setSessionSuccessCallback(void(*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setSessionTrackingSucceededCallbackMethod(sessionSuccessCallback);

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnSessionTrackingSucceededListener", "(Lcom/adjust/sdk/OnSessionTrackingSucceededListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxSessionTrackingSucceededCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxSessionTrackingSucceededCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxSessionTrackingSucceededCallback");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxSessionTrackingSucceededCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxSessionTrackingSucceededCallback, midInit);

    miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

    miInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSessionSuccessCallback(sessionSuccessCallback);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setSessionFailureCallback(void(*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setSessionTrackingFailedCallbackMethod(sessionFailureCallback);

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnSessionTrackingFailedListener", "(Lcom/adjust/sdk/OnSessionTrackingFailedListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxSessionTrackingFailedCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxSessionTrackingFailedCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxSessionTrackingFailedCallback");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxSessionTrackingFailedCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxSessionTrackingFailedCallback, midInit);

    miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

    miInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setSessionFailureCallback(sessionFailureCallback);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

void AdjustConfig2dx::setDeferredDeeplinkCallback(bool(*deferredDeeplinkCallback)(std::string deeplink)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    setDeferredDeeplinkCallbackMethod(deferredDeeplinkCallback);

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnDeeplinkResponseListener", "(Lcom/adjust/sdk/OnDeeplinkResponseListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxDeferredDeeplinkCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxDeferredDeeplinkCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxDeferredDeeplinkCallback");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxDeferredDeeplinkCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxDeferredDeeplinkCallback, midInit);

    miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

    miInit.env->DeleteLocalRef(jCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDeferredDeeplinkCallback(deferredDeeplinkCallback);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

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

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
WRTAdjustConfig^ AdjustConfig2dx::getConfig() {
    return config;
}

void AdjustConfig2dx::triggerSavedAttributionCallback(AdjustAttribution2dx attribution) {
    attributionCallbackSaved(attribution);
}
#endif

