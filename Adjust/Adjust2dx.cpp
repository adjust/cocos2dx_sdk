//
//  Adjust2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#include "Adjust2dx.h"

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
    cocos2d::JniMethodInfo miOnCreate;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miOnCreate, "com/adjust/sdk/Adjust", "onCreate", "(Lcom/adjust/sdk/AdjustConfig;)V")) {
        return;
    }

    miOnCreate.env->CallStaticVoidMethod(miOnCreate.classID, miOnCreate.methodID, adjustConfig.getConfig());

    onResume();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::appDidLaunch(adjustConfig.getConfig());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WRTAdjust::ApplicationLaunching(adjustConfig.getConfig());
#endif
}

void Adjust2dx::trackEvent(AdjustEvent2dx event) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miTrackEvent;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miTrackEvent, "com/adjust/sdk/Adjust", "trackEvent", "(Lcom/adjust/sdk/AdjustEvent;)V")) {
        return;
    }

    miTrackEvent.env->CallStaticVoidMethod(miTrackEvent.classID, miTrackEvent.methodID, event.getEvent());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackEvent(event.getEvent());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WRTAdjust::TrackEvent(event.getEvent());
#endif
}

void Adjust2dx::setEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miSetEnabled;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miSetEnabled, "com/adjust/sdk/Adjust", "setEnabled", "(Z)V")) {
        return;
    }

    miSetEnabled.env->CallStaticVoidMethod(miSetEnabled.classID, miSetEnabled.methodID, isEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setEnabled(isEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WRTAdjust::SetEnabled(isEnabled);
#endif
}

bool Adjust2dx::isEnabled() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miIsEnabled;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miIsEnabled, "com/adjust/sdk/Adjust", "isEnabled", "()Z")) {
        return false;
    }

    jboolean jIsEnabled = miIsEnabled.env->CallStaticBooleanMethod(miIsEnabled.classID, miIsEnabled.methodID);

    return jIsEnabled;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::isEnabled();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    return WRTAdjust::IsEnabled();
#else
    return false;
#endif
}

void Adjust2dx::setOfflineMode(bool isOffline) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miIsOffline;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miIsOffline, "com/adjust/sdk/Adjust", "setOfflineMode", "(Z)V")) {
        return;
    }

    miIsOffline.env->CallStaticVoidMethod(miIsOffline.classID, miIsOffline.methodID, isOffline);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setOfflineMode(isOffline);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WRTAdjust::SetOfflineMode(isOffline);
#endif
}

void Adjust2dx::appWillOpenUrl(std::string url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::appWillOpenUrl(url);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miAppWillOpenUrl;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miAppWillOpenUrl, "com/adjust/sdk/Adjust", "appWillOpenUrl", "(Landroid/net/Uri;)V")) {
        return;
    }

    jclass jcUri = miAppWillOpenUrl.env->FindClass("android/net/Uri");
    jmethodID midParse = miAppWillOpenUrl.env->GetStaticMethodID(jcUri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");

    jstring jUrl = miAppWillOpenUrl.env->NewStringUTF(url.c_str());
    jobject jUri = miAppWillOpenUrl.env->CallStaticObjectMethod(jcUri, midParse, jUrl);

    miAppWillOpenUrl.env->CallStaticVoidMethod(miAppWillOpenUrl.classID, miAppWillOpenUrl.methodID, jUri);

    miAppWillOpenUrl.env->DeleteLocalRef(jUrl);
    miAppWillOpenUrl.env->DeleteLocalRef(jUri);
#endif
}

void Adjust2dx::setDeviceToken(std::string deviceToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setDeviceToken(deviceToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miSetPushToken;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miSetPushToken, "com/adjust/sdk/Adjust", "setPushToken", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jPushToken = miSetPushToken.env->NewStringUTF(deviceToken.c_str());

    miSetPushToken.env->CallStaticVoidMethod(miSetPushToken.classID, miSetPushToken.methodID, jPushToken);

    miSetPushToken.env->DeleteLocalRef(jPushToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::sendFirstPackages() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::sendFirstPackages();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miSendFirstPackages;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miSendFirstPackages, "com/adjust/sdk/Adjust", "sendFirstPackages", "()V")) {
        return;
    }

    miSendFirstPackages.env->CallStaticVoidMethod(miSendFirstPackages.classID, miSendFirstPackages.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::addSessionCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::addSessionCallbackParameter(key, value);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miAddSessionCallbackParameter;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miAddSessionCallbackParameter, "com/adjust/sdk/Adjust", "addSessionCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miAddSessionCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = miAddSessionCallbackParameter.env->NewStringUTF(value.c_str());

    miAddSessionCallbackParameter.env->CallStaticVoidMethod(miAddSessionCallbackParameter.classID, miAddSessionCallbackParameter.methodID, jKey, jValue);

    miAddSessionCallbackParameter.env->DeleteLocalRef(jKey);
    miAddSessionCallbackParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::addSessionPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::addSessionPartnerParameter(key, value);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miAddSessionPartnerParameter;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miAddSessionPartnerParameter, "com/adjust/sdk/Adjust", "addSessionPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miAddSessionPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = miAddSessionPartnerParameter.env->NewStringUTF(value.c_str());

    miAddSessionPartnerParameter.env->CallStaticVoidMethod(miAddSessionPartnerParameter.classID, miAddSessionPartnerParameter.methodID, jKey, jValue);

    miAddSessionPartnerParameter.env->DeleteLocalRef(jKey);
    miAddSessionPartnerParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::removeSessionCallbackParameter(std::string key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeSessionCallbackParameter(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miRemoveSessionCallbackParameter;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miRemoveSessionCallbackParameter, "com/adjust/sdk/Adjust", "removeSessionCallbackParameter", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miRemoveSessionCallbackParameter.env->NewStringUTF(key.c_str());

    miRemoveSessionCallbackParameter.env->CallStaticVoidMethod(miRemoveSessionCallbackParameter.classID, miRemoveSessionCallbackParameter.methodID, jKey);

    miRemoveSessionCallbackParameter.env->DeleteLocalRef(jKey);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::removeSessionPartnerParameter(std::string key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeSessionPartnerParameter(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miRemoveSessionPartnerParameter;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miRemoveSessionPartnerParameter, "com/adjust/sdk/Adjust", "removeSessionPartnerParameter", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miRemoveSessionPartnerParameter.env->NewStringUTF(key.c_str());

    miRemoveSessionPartnerParameter.env->CallStaticVoidMethod(miRemoveSessionPartnerParameter.classID, miRemoveSessionPartnerParameter.methodID, jKey);

    miRemoveSessionPartnerParameter.env->DeleteLocalRef(jKey);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::resetSessionCallbackParameters() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::resetSessionCallbackParameters();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miResetSessionCallbackParameters;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miResetSessionCallbackParameters, "com/adjust/sdk/Adjust", "resetSessionCallbackParameters", "()V")) {
        return;
    }

    miResetSessionCallbackParameters.env->CallStaticVoidMethod(miResetSessionCallbackParameters.classID, miResetSessionCallbackParameters.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}

void Adjust2dx::resetSessionPartnerParameters() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::resetSessionPartnerParameters();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miResetSessionPartnerParameters;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miResetSessionPartnerParameters, "com/adjust/sdk/Adjust", "resetSessionPartnerParameters", "()V")) {
        return;
    }

    miResetSessionPartnerParameters.env->CallStaticVoidMethod(miResetSessionPartnerParameters.classID, miResetSessionPartnerParameters.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
#endif
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void Adjust2dx::onResume() {
    cocos2d::JniMethodInfo miOnResume;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miOnResume, "com/adjust/sdk/Adjust", "onResume", "()V")) {
        return;
    }

    miOnResume.env->CallStaticVoidMethod(miOnResume.classID, miOnResume.methodID);
}

void Adjust2dx::onPause() {
    cocos2d::JniMethodInfo miOnPause;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miOnPause, "com/adjust/sdk/Adjust", "onPause", "()V")) {
        return;
    }

    miOnPause.env->CallStaticVoidMethod(miOnPause.classID, miOnPause.methodID);
}

void Adjust2dx::setReferrer(std::string referrer) {
    cocos2d::JniMethodInfo miSetReferrer;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miSetReferrer, "com/adjust/sdk/Adjust", "setReferrer", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jReferrer = miSetReferrer.env->NewStringUTF(referrer.c_str());

    miSetReferrer.env->CallStaticVoidMethod(miSetReferrer.classID, miSetReferrer.methodID, jReferrer);

    miSetReferrer.env->DeleteLocalRef(jReferrer);
}

void Adjust2dx::getGoogleAdId(void (*adIdCallback)(std::string adId)) {
    setAdIdCallbackMethod(adIdCallback);

    cocos2d::JniMethodInfo miGetAdIdCallback;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miGetAdIdCallback, "com/adjust/sdk/Adjust", "getGoogleAdId", "(Landroid/content/Context;Lcom/adjust/sdk/OnDeviceIdsRead;)V")) {
        return;
    }

    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/Adjust2dxAdIdCallback", "<init>", "()V")) {
        return;
    }

    cocos2d::JniMethodInfo miGetContext;

    if (!cocos2d::JniHelper::getStaticMethodInfo(miGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jclass clsAdjust2dxAdIdCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxAdIdCallback");

    jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxAdIdCallback, "<init>", "()V");
    jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxAdIdCallback, midInit);

    // Get context and initialize config object.
    jobject jContext = (jobject)miGetContext.env->CallStaticObjectMethod(miGetContext.classID, miGetContext.methodID);

    miGetAdIdCallback.env->CallStaticVoidMethod(miGetAdIdCallback.classID, miGetAdIdCallback.methodID, jContext, jCallbackProxy);

    miGetContext.env->DeleteLocalRef(jContext);
    miInit.env->DeleteLocalRef(jCallbackProxy);
}
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
std::string Adjust2dx::getIdfa() {
    return ADJAdjust2dx::getIdfa();
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
std::string Adjust2dx::getWindowsAdId() {
    Platform::String^ managedAdId = WRTAdjust::GetWindowsAdId();
    std::wstring wstrAdId(managedAdId->Begin());
    std::string adId(wstrAdId.begin(), wstrAdId.end());

    return adId;
}

void Adjust2dx::applicationPaused() {
    WRTAdjust::ApplicationDeactivated();
}

void Adjust2dx::applicationResumed() {
    WRTAdjust::ApplicationActivated();
}
#endif
