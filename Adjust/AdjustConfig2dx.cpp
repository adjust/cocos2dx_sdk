//
//  AdjustConfig2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "AdjustProxy2dx.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#else
#include "cocos2d.h"
#include <windows.h>
#include <fstream>
USING_NS_CC;
#endif

#include "AdjustConfig2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#else
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

void AdjustConfig2dx::initConfig(std::string appToken, std::string environment) {
    std::string sdkPrefix = "cocos2d-x4.2.0";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/AdjustConfig", "<init>",
            "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miGetContext;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext",
            "()Landroid/content/Context;")) {
        return;
    }

    // Set SDK prefix.
    cocos2d::JniMethodInfo miSetSdkPrefix;

    if (!cocos2d::JniHelper::getMethodInfo(miSetSdkPrefix, "com/adjust/sdk/AdjustConfig", "setSdkPrefix",
            "(Ljava/lang/String;)V")) {
        return;
    }

    jclass clsAdjustConfig = miInit.env->FindClass("com/adjust/sdk/AdjustConfig");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjustConfig, "<init>",
            "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");

    // Get context and initialize config object.
    jobject jContext = (jobject)miGetContext.env->CallStaticObjectMethod(miGetContext.classID, miGetContext.methodID);
    jstring jAppToken = miInit.env->NewStringUTF(appToken.c_str());
    jstring jEnvironment = miInit.env->NewStringUTF(environment.c_str());

    config = miInit.env->NewObject(clsAdjustConfig, midInit, jContext, jAppToken, jEnvironment);

    miGetContext.env->DeleteLocalRef(jContext);
    miInit.env->DeleteLocalRef(jAppToken);
    miInit.env->DeleteLocalRef(jEnvironment);

    jstring jSdkPrefix = miSetSdkPrefix.env->NewStringUTF(sdkPrefix.c_str());

    miSetSdkPrefix.env->CallVoidMethod(config, miSetSdkPrefix.methodID, jSdkPrefix);

    miSetSdkPrefix.env->DeleteLocalRef(jSdkPrefix);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    config = ADJConfig2dx(appToken, environment, sdkPrefix);
    isConfigSet = true;
#else
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
    if (!cocos2d::JniHelper::getMethodInfo(miSetLogLevel, "com/adjust/sdk/AdjustConfig", "setLogLevel",
            "(Lcom/adjust/sdk/LogLevel;)V")) {
        return;
    }
    jclass clsLogLevel = miSetLogLevel.env->FindClass("com/adjust/sdk/LogLevel");

    std::string enumValue;

    switch (logLevel) {
    case AdjustLogLevel2dxAssert:
        enumValue = "ASSERT";
        break;
    case AdjustLogLevel2dxDebug:
        enumValue = "DEBUG";
        break;
    case AdjustLogLevel2dxError:
        enumValue = "ERROR";
        break;
    case AdjustLogLevel2dxInfo:
        enumValue = "INFO";
        break;
    case AdjustLogLevel2dxVerbose:
        enumValue = "VERBOSE";
        break;
    case AdjustLogLevel2dxWarn:
        enumValue = "WARN";
        break;
    default:
        enumValue = "INFO";
        break;
    }

    jfieldID fidValue = miSetLogLevel.env->GetStaticFieldID(clsLogLevel, enumValue.c_str(),
            "Lcom/adjust/sdk/LogLevel;");
    jobject jLogLevel = miSetLogLevel.env->GetStaticObjectField(clsLogLevel, fidValue);

    miSetLogLevel.env->CallVoidMethod(config, miSetLogLevel.methodID, jLogLevel);

    miSetLogLevel.env->DeleteLocalRef(jLogLevel);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setLogLevel((ADJLogLevel2dx)logLevel);
    }
#else
    if (isConfigSet) {
        config->SetLogLevel(logLevel, (int64)logCallback);
    }
#endif
}

void AdjustConfig2dx::setEventBufferingEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetEventBufferingEnabled;
    if (!cocos2d::JniHelper::getMethodInfo(miSetEventBufferingEnabled, "com/adjust/sdk/AdjustConfig",
            "setEventBufferingEnabled", "(Z)V")) {
        return;
    }
    miSetEventBufferingEnabled.env->CallVoidMethod(config, miSetEventBufferingEnabled.methodID, isEnabled);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventBufferingEnabled(isEnabled);
    }
#else
    if (isConfigSet) {
        config->SetEventBufferingEnabled(isEnabled);
    }
#endif
}

void AdjustConfig2dx::setDefaultTracker(std::string defaultTracker) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetDefaultTracker;
    if (!cocos2d::JniHelper::getMethodInfo(miSetDefaultTracker, "com/adjust/sdk/AdjustConfig", "setDefaultTracker",
            "(Ljava/lang/String;)V")) {
        return;
    }
    jstring jDefaultTracker = miSetDefaultTracker.env->NewStringUTF(defaultTracker.c_str());

    miSetDefaultTracker.env->CallVoidMethod(config, miSetDefaultTracker.methodID, jDefaultTracker);

    miSetDefaultTracker.env->DeleteLocalRef(jDefaultTracker);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDefaultTracker(defaultTracker);
    }
#else
    if (isConfigSet) {
        std::wstring wstrDefaultTracker = std::wstring(defaultTracker.begin(), defaultTracker.end());
        const wchar_t* wcharDefaultTracker = wstrDefaultTracker.c_str();
        config->SetDefaultTracker(ref new Platform::String(wcharDefaultTracker));
    }
#endif
}

void AdjustConfig2dx::setAttributionCallback(void (*attributionCallback)(AdjustAttribution2dx attribution)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setAttributionCallbackMethod(attributionCallback);

    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetCallback;

    if (!cocos2d::JniHelper::getMethodInfo(miSetCallback, "com/adjust/sdk/AdjustConfig", "setOnAttributionChangedListener",
            "(Lcom/adjust/sdk/OnAttributionChangedListener;)V")) {
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
#else
    if (isConfigSet) {
        attributionCallbackSaved = attributionCallback;
        config->SetAttributionCallback((int64)&attributionCallbackGlobal);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustConfig2dx::getConfig() {
    return config;
}

void AdjustConfig2dx::setProcessName(std::string processName) {
    if (config == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetProcessName;
    if (!cocos2d::JniHelper::getMethodInfo(miSetProcessName, "com/adjust/sdk/AdjustConfig", "setProcessName",
                                          "(Ljava/lang/String;)V")) {
        return;
    }
    jstring jProcessName = miSetProcessName.env->NewStringUTF(processName.c_str());

    miSetProcessName.env->CallVoidMethod(config, miSetProcessName.methodID, jProcessName);

    miSetProcessName.env->DeleteLocalRef(jProcessName);
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJConfig2dx AdjustConfig2dx::getConfig() {
    return config;
}
#else
WRTAdjustConfig^ AdjustConfig2dx::getConfig() {
    return config;
}

void AdjustConfig2dx::triggerSavedAttributionCallback(AdjustAttribution2dx attribution) {
    attributionCallbackSaved(attribution);
}
#endif
