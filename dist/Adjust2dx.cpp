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
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiOnCreate, "com/adjust/sdk/Adjust", "onCreate", "(Lcom/adjust/sdk/AdjustConfig;)V")) {
        return;
    }
    jmiOnCreate.env->CallStaticVoidMethod(jmiOnCreate.classID, jmiOnCreate.methodID, adjustConfig.getConfig());
    onResume();
    jmiOnCreate.env->DeleteGlobalRef(adjustConfig.getConfig());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::appDidLaunch(adjustConfig.getConfig());
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

void Adjust2dx::trackPlayStoreSubscription(AdjustPlayStoreSubscription2dx subscription) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackPlayStoreSubscription;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackPlayStoreSubscription, "com/adjust/sdk/Adjust", "trackPlayStoreSubscription", "(Lcom/adjust/sdk/AdjustPlayStoreSubscription;)V")) {
        return;
    }
    jmiTrackPlayStoreSubscription.env->CallStaticVoidMethod(jmiTrackPlayStoreSubscription.classID, jmiTrackPlayStoreSubscription.methodID, subscription.getSubscription());
#endif
}

void Adjust2dx::setEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetEnabled;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetEnabled, "com/adjust/sdk/Adjust", "setEnabled", "(Z)V")) {
        return;
    }
    jmiSetEnabled.env->CallStaticVoidMethod(jmiSetEnabled.classID, jmiSetEnabled.methodID, isEnabled);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setEnabled(isEnabled);
#endif
}

bool Adjust2dx::isEnabled() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiIsEnabled;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiIsEnabled, "com/adjust/sdk/Adjust", "isEnabled", "()Z")) {
        return false;
    }
    jboolean jIsEnabled = jmiIsEnabled.env->CallStaticBooleanMethod(jmiIsEnabled.classID, jmiIsEnabled.methodID);
    return jIsEnabled;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::isEnabled();
#else
    return false;
#endif
}

void Adjust2dx::setOfflineMode(bool isOffline) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiIsOffline;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiIsOffline, "com/adjust/sdk/Adjust", "setOfflineMode", "(Z)V")) {
        return;
    }
    jmiIsOffline.env->CallStaticVoidMethod(jmiIsOffline.classID, jmiIsOffline.methodID, isOffline);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setOfflineMode(isOffline);
#endif
}

void Adjust2dx::appWillOpenUrl(std::string url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::appWillOpenUrl(url);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiAppWillOpenUrl;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiAppWillOpenUrl, "com/adjust/sdk/Adjust", "appWillOpenUrl", "(Landroid/net/Uri;Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jclass jcUri = jmiAppWillOpenUrl.env->FindClass("android/net/Uri");
    jmethodID midParse = jmiAppWillOpenUrl.env->GetStaticMethodID(jcUri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jstring jUrl = jmiAppWillOpenUrl.env->NewStringUTF(url.c_str());
    jobject jUri = jmiAppWillOpenUrl.env->CallStaticObjectMethod(jcUri, midParse, jUrl);
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiAppWillOpenUrl.env->CallStaticVoidMethod(jmiAppWillOpenUrl.classID, jmiAppWillOpenUrl.methodID, jUri, jContext);
    jmiAppWillOpenUrl.env->DeleteLocalRef(jUrl);
    jmiAppWillOpenUrl.env->DeleteLocalRef(jUri);
    jmiGetContext.env->DeleteLocalRef(jContext);
#endif
}

void Adjust2dx::setDeviceToken(std::string deviceToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setDeviceToken(deviceToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSetPushToken;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetPushToken, "com/adjust/sdk/Adjust", "setPushToken", "(Ljava/lang/String;Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jstring jPushToken = jmiSetPushToken.env->NewStringUTF(deviceToken.c_str());
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiSetPushToken.env->CallStaticVoidMethod(jmiSetPushToken.classID, jmiSetPushToken.methodID, jPushToken, jContext);
    jmiSetPushToken.env->DeleteLocalRef(jPushToken);
    jmiGetContext.env->DeleteLocalRef(jContext);
#endif
}

void Adjust2dx::sendFirstPackages() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::sendFirstPackages();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiSendFirstPackages;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSendFirstPackages, "com/adjust/sdk/Adjust", "sendFirstPackages", "()V")) {
        return;
    }
    jmiSendFirstPackages.env->CallStaticVoidMethod(jmiSendFirstPackages.classID, jmiSendFirstPackages.methodID);
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

void Adjust2dx::addSessionCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::addSessionCallbackParameter(key, value);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiAddSessionCallbackParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiAddSessionCallbackParameter, "com/adjust/sdk/Adjust", "addSessionCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddSessionCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddSessionCallbackParameter.env->NewStringUTF(value.c_str());
    jmiAddSessionCallbackParameter.env->CallStaticVoidMethod(jmiAddSessionCallbackParameter.classID, jmiAddSessionCallbackParameter.methodID, jKey, jValue);
    jmiAddSessionCallbackParameter.env->DeleteLocalRef(jKey);
    jmiAddSessionCallbackParameter.env->DeleteLocalRef(jValue);
#endif
}

void Adjust2dx::addSessionPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::addSessionPartnerParameter(key, value);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiAddSessionPartnerParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiAddSessionPartnerParameter, "com/adjust/sdk/Adjust", "addSessionPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddSessionPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddSessionPartnerParameter.env->NewStringUTF(value.c_str());
    jmiAddSessionPartnerParameter.env->CallStaticVoidMethod(jmiAddSessionPartnerParameter.classID, jmiAddSessionPartnerParameter.methodID, jKey, jValue);
    jmiAddSessionPartnerParameter.env->DeleteLocalRef(jKey);
    jmiAddSessionPartnerParameter.env->DeleteLocalRef(jValue);
#endif
}

void Adjust2dx::removeSessionCallbackParameter(std::string key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeSessionCallbackParameter(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiRemoveSessionCallbackParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiRemoveSessionCallbackParameter, "com/adjust/sdk/Adjust", "removeSessionCallbackParameter", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiRemoveSessionCallbackParameter.env->NewStringUTF(key.c_str());
    jmiRemoveSessionCallbackParameter.env->CallStaticVoidMethod(jmiRemoveSessionCallbackParameter.classID, jmiRemoveSessionCallbackParameter.methodID, jKey);
    jmiRemoveSessionCallbackParameter.env->DeleteLocalRef(jKey);
#endif
}

void Adjust2dx::removeSessionPartnerParameter(std::string key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::removeSessionPartnerParameter(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiRemoveSessionPartnerParameter;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiRemoveSessionPartnerParameter, "com/adjust/sdk/Adjust", "removeSessionPartnerParameter", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiRemoveSessionPartnerParameter.env->NewStringUTF(key.c_str());
    jmiRemoveSessionPartnerParameter.env->CallStaticVoidMethod(jmiRemoveSessionPartnerParameter.classID, jmiRemoveSessionPartnerParameter.methodID, jKey);
    jmiRemoveSessionPartnerParameter.env->DeleteLocalRef(jKey);
#endif
}

void Adjust2dx::resetSessionCallbackParameters() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::resetSessionCallbackParameters();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiResetSessionCallbackParameters;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiResetSessionCallbackParameters, "com/adjust/sdk/Adjust", "resetSessionCallbackParameters", "()V")) {
        return;
    }
    jmiResetSessionCallbackParameters.env->CallStaticVoidMethod(jmiResetSessionCallbackParameters.classID, jmiResetSessionCallbackParameters.methodID);
#endif
}

void Adjust2dx::resetSessionPartnerParameters() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::resetSessionPartnerParameters();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiResetSessionPartnerParameters;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiResetSessionPartnerParameters, "com/adjust/sdk/Adjust", "resetSessionPartnerParameters", "()V")) {
        return;
    }
    jmiResetSessionPartnerParameters.env->CallStaticVoidMethod(jmiResetSessionPartnerParameters.classID, jmiResetSessionPartnerParameters.methodID);
#endif
}

void Adjust2dx::trackAdRevenue(std::string source, std::string payload) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackAdRevenue(source, payload);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackAdRevenue;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackAdRevenue, "com/adjust/sdk/Adjust", "trackAdRevenue", "(Ljava/lang/String;Lorg/json/JSONObject;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiJsonObjectInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiJsonObjectInit, "org/json/JSONObject", "<init>", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jSource = jmiTrackAdRevenue.env->NewStringUTF(source.c_str());
    jstring jPayload = jmiTrackAdRevenue.env->NewStringUTF(payload.c_str());
    jclass clsJsonObject = jmiJsonObjectInit.env->FindClass("org/json/JSONObject");
    jmethodID jmidJsonObjectInit = jmiJsonObjectInit.env->GetMethodID(clsJsonObject, "<init>", "(Ljava/lang/String;)V");
    jobject jJsonObject = jmiJsonObjectInit.env->NewObject(clsJsonObject, jmidJsonObjectInit, jPayload);
    jmiTrackAdRevenue.env->CallStaticVoidMethod(jmiTrackAdRevenue.classID, jmiTrackAdRevenue.methodID, jSource, jJsonObject);
    jmiJsonObjectInit.env->DeleteLocalRef(jJsonObject);
#endif
}

void Adjust2dx::disableThirdPartySharing() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::disableThirdPartySharing();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiDisableThirdPartySharing;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiDisableThirdPartySharing, "com/adjust/sdk/Adjust", "disableThirdPartySharing", "(Landroid/content/Context;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiDisableThirdPartySharing.env->CallStaticVoidMethod(jmiDisableThirdPartySharing.classID, jmiDisableThirdPartySharing.methodID, jContext);
    jmiGetContext.env->DeleteLocalRef(jContext);
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

std::string Adjust2dx::getAdid() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::getAdid();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiGetAdid;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAdid, "com/adjust/sdk/Adjust", "getAdid", "()Ljava/lang/String;")) {
        return "";
    }

    jstring jAdid = (jstring)jmiGetAdid.env->CallStaticObjectMethod(jmiGetAdid.classID, jmiGetAdid.methodID);
    std::string adid = "";
    if (NULL != jAdid) {
        const char *adidCStr = jmiGetAdid.env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        jmiGetAdid.env->ReleaseStringUTFChars(jAdid, adidCStr);
        jmiGetAdid.env->DeleteLocalRef(jAdid);
    }
    return adid;
#endif
}

std::string Adjust2dx::getSdkVersion() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return AdjustSdkPrefix2dx + "@" + ADJAdjust2dx::getSdkVersion();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiGetSdkVersion;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetSdkVersion, "com/adjust/sdk/Adjust", "getSdkVersion", "()Ljava/lang/String;")) {
        return "";
    }

    jstring jSdkVersion = (jstring)jmiGetSdkVersion.env->CallStaticObjectMethod(jmiGetSdkVersion.classID, jmiGetSdkVersion.methodID);
    std::string sdkVersion = "";
    if (NULL != jSdkVersion) {
        const char *sdkVersionCStr = jmiGetSdkVersion.env->GetStringUTFChars(jSdkVersion, NULL);
        sdkVersion = std::string(sdkVersionCStr);
        jmiGetSdkVersion.env->ReleaseStringUTFChars(jSdkVersion, sdkVersionCStr);
        jmiGetSdkVersion.env->DeleteLocalRef(jSdkVersion);
    }
    return AdjustSdkPrefix2dx + "@" + sdkVersion;
#endif
}

AdjustAttribution2dx Adjust2dx::getAttribution() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::getAttribution();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;
    std::string adid;
    std::string costType;
    double costAmount;
    std::string costCurrency;
    std::string fbInstallReferrer;

    cocos2d::JniMethodInfo jmiGetAttribution;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAttribution, "com/adjust/sdk/Adjust", "getAttribution", "()Lcom/adjust/sdk/AdjustAttribution;")) {
        AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(
            trackerToken,
            trackerName,
            network,
            campaign,
            adgroup,
            creative,
            clickLabel,
            adid,
            costType,
            costAmount,
            costCurrency,
            fbInstallReferrer);
        return attribution2dx;
    }

    jobject jAttribution = jmiGetAttribution.env->CallStaticObjectMethod(jmiGetAttribution.classID, jmiGetAttribution.methodID);
    if (NULL != jAttribution) {
        jclass clsAdjustAttribution = jmiGetAttribution.env->FindClass("com/adjust/sdk/AdjustAttribution");
        jfieldID jfidTrackerToken = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "trackerToken", "Ljava/lang/String;");
        jfieldID jfidTrackerName = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "trackerName", "Ljava/lang/String;");
        jfieldID jfidNetwork = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "network", "Ljava/lang/String;");
        jfieldID jfidCampaign = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "campaign", "Ljava/lang/String;");
        jfieldID jfidAdgroup = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "adgroup", "Ljava/lang/String;");
        jfieldID jfidCreative = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "creative", "Ljava/lang/String;");
        jfieldID jfidClickLabel = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "clickLabel", "Ljava/lang/String;");
        jfieldID jfidAdid = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "adid", "Ljava/lang/String;");
        jfieldID jfidCostType = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "costType", "Ljava/lang/String;");
        jfieldID jfidCostAmount = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "costAmount", "Ljava/lang/Double;");
        jfieldID jfidCostCurrency = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "costCurrency", "Ljava/lang/String;");
        jfieldID jfidFbInstallReferrer = jmiGetAttribution.env->GetFieldID(clsAdjustAttribution, "fbInstallReferrer", "Ljava/lang/String;");
        jstring jTrackerToken = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidTrackerToken);
        jstring jTrackerName = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidTrackerName);
        jstring jNetwork = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidNetwork);
        jstring jCampaign = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidCampaign);
        jstring jAdgroup = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidAdgroup);
        jstring jCreative = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidCreative);
        jstring jClickLabel = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidClickLabel);
        jstring jAdid = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidAdid);
        jstring jCostType = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidCostType);
        jobject jCostAmount = jmiGetAttribution.env->GetObjectField(jAttribution, jfidCostAmount);
        jstring jCostCurrency = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidCostCurrency);
        jstring jFbInstallReferrer = (jstring)jmiGetAttribution.env->GetObjectField(jAttribution, jfidFbInstallReferrer);

        if (NULL != jTrackerToken) {
            const char *trackerTokenCStr = jmiGetAttribution.env->GetStringUTFChars(jTrackerToken, NULL);
            trackerToken = std::string(trackerTokenCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jTrackerToken, trackerTokenCStr);
            jmiGetAttribution.env->DeleteLocalRef(jTrackerToken);
        } else {
            trackerToken = "";
        }

        if (NULL != jTrackerName) {
            const char *trackerNameCStr = jmiGetAttribution.env->GetStringUTFChars(jTrackerName, NULL);
            trackerName = std::string(trackerNameCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jTrackerName, trackerNameCStr);
            jmiGetAttribution.env->DeleteLocalRef(jTrackerName);
        } else {
            trackerName = "";
        }

        if (NULL != jNetwork) {
            const char *networkCStr = jmiGetAttribution.env->GetStringUTFChars(jNetwork, NULL);
            network = std::string(networkCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jNetwork, networkCStr);
            jmiGetAttribution.env->DeleteLocalRef(jNetwork);
        } else {
            network = "";
        }

        if (NULL != jCampaign) {
            const char *campaignCStr = jmiGetAttribution.env->GetStringUTFChars(jCampaign, NULL);
            campaign = std::string(campaignCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jCampaign, campaignCStr);
            jmiGetAttribution.env->DeleteLocalRef(jCampaign);
        } else {
            campaign = "";
        }

        if (NULL != jAdgroup) {
            const char *adgroupCStr = jmiGetAttribution.env->GetStringUTFChars(jAdgroup, NULL);
            adgroup = std::string(adgroupCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jAdgroup, adgroupCStr);
            jmiGetAttribution.env->DeleteLocalRef(jAdgroup);
        } else {
            adgroup = "";
        }

        if (NULL != jCreative) {
            const char *creativeCStr = jmiGetAttribution.env->GetStringUTFChars(jCreative, NULL);
            creative = std::string(creativeCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jCreative, creativeCStr);
            jmiGetAttribution.env->DeleteLocalRef(jCreative);
        } else {
            creative = "";
        }

        if (NULL != jClickLabel) {
            const char *clickLabelCStr = jmiGetAttribution.env->GetStringUTFChars(jClickLabel, NULL);
            clickLabel = std::string(clickLabelCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jClickLabel, clickLabelCStr);
            jmiGetAttribution.env->DeleteLocalRef(jClickLabel);
        } else {
            clickLabel = "";
        }

        if (NULL != jAdid) {
            const char *adidCStr = jmiGetAttribution.env->GetStringUTFChars(jAdid, NULL);
            adid = std::string(adidCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jAdid, adidCStr);
            jmiGetAttribution.env->DeleteLocalRef(jAdid);
        } else {
            adid = "";
        }

        if (NULL != jCostType) {
            const char *costTypeCStr = jmiGetAttribution.env->GetStringUTFChars(jCostType, NULL);
            costType = std::string(costTypeCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jCostType, costTypeCStr);
            jmiGetAttribution.env->DeleteLocalRef(jCostType);
        } else {
            costType = "";
        }

        if (NULL != jCostAmount) {
            jclass jcDouble = jmiGetAttribution.env->FindClass("java/lang/Double");
            jmethodID jmidDoubleValue = jmiGetAttribution.env->GetMethodID(jcDouble, "doubleValue", "()D" );
            costAmount = jmiGetAttribution.env->CallDoubleMethod(jCostAmount, jmidDoubleValue);
        } else {
            costAmount = 0;
        }

        if (NULL != jCostCurrency) {
            const char *costCurrencyCStr = jmiGetAttribution.env->GetStringUTFChars(jCostCurrency, NULL);
            costCurrency = std::string(costCurrencyCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jCostCurrency, costCurrencyCStr);
            jmiGetAttribution.env->DeleteLocalRef(jCostCurrency);
        } else {
            costCurrency = "";
        }

        if (NULL != jFbInstallReferrer) {
            const char *fbInstallReferrerCStr = jmiGetAttribution.env->GetStringUTFChars(jFbInstallReferrer, NULL);
            fbInstallReferrer = std::string(fbInstallReferrerCStr);
            jmiGetAttribution.env->ReleaseStringUTFChars(jFbInstallReferrer, fbInstallReferrerCStr);
            jmiGetAttribution.env->DeleteLocalRef(jFbInstallReferrer);
        } else {
            fbInstallReferrer = "";
        }
    }

    AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(
        trackerToken,
        trackerName,
        network,
        campaign,
        adgroup,
        creative,
        clickLabel,
        adid,
        costType,
        costAmount,
        costCurrency,
        fbInstallReferrer);
    return attribution2dx;
#endif
}

void Adjust2dx::trackAdRevenueNew(AdjustAdRevenue2dx adRevenue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::trackAdRevenueNew(adRevenue.getAdRevenue());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiTrackAdRevenue;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTrackAdRevenue, "com/adjust/sdk/Adjust", "trackAdRevenue", "(Lcom/adjust/sdk/AdjustAdRevenue;)V")) {
        return;
    }
    jmiTrackAdRevenue.env->CallStaticVoidMethod(jmiTrackAdRevenue.classID, jmiTrackAdRevenue.methodID, adRevenue.getAdRevenue());
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

void Adjust2dx::getGoogleAdId(void (*adIdCallback)(std::string adId)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setAdIdCallbackMethod(adIdCallback);

    cocos2d::JniMethodInfo jmiGetAdIdCallback;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAdIdCallback, "com/adjust/sdk/Adjust", "getGoogleAdId", "(Landroid/content/Context;Lcom/adjust/sdk/OnDeviceIdsRead;)V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/Adjust2dxAdIdCallback", "<init>", "()V")) {
        return;
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }
    
    jclass clsAdjust2dxAdIdCallback = jmiInit.env->FindClass("com/adjust/sdk/Adjust2dxAdIdCallback");
    jmethodID jmidInit = jmiInit.env->GetMethodID(clsAdjust2dxAdIdCallback, "<init>", "()V");
    jobject jCallbackProxy = jmiInit.env->NewObject(clsAdjust2dxAdIdCallback, jmidInit);
    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);
    jmiGetAdIdCallback.env->CallStaticVoidMethod(jmiGetAdIdCallback.classID, jmiGetAdIdCallback.methodID, jContext, jCallbackProxy);
    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jCallbackProxy);
#endif
}

std::string Adjust2dx::getAmazonAdId() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiGetAmazonAdid;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetAmazonAdid, "com/adjust/sdk/Adjust", "getAmazonAdId", "(Landroid/content/Context;)Ljava/lang/String;")) {
        return "";
    }
    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return "";
    }

    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);    
    jstring jAdid = (jstring)jmiGetAmazonAdid.env->CallStaticObjectMethod(jmiGetAmazonAdid.classID, jmiGetAmazonAdid.methodID, jContext);
    std::string adid = "";
    if (NULL != jAdid) {
        const char *adidCStr = jmiGetAmazonAdid.env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        jmiGetAmazonAdid.env->ReleaseStringUTFChars(jAdid, adidCStr);
        jmiGetAmazonAdid.env->DeleteLocalRef(jAdid);
    }
    jmiGetContext.env->DeleteLocalRef(jContext);
    return adid;
#else
    return "";
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

std::string Adjust2dx::getIdfa() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::getIdfa();
#else
    return "";
#endif
}

void Adjust2dx::requestTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::requestTrackingAuthorizationWithCompletionHandler(trackingStatusCallback);
#endif
}

int Adjust2dx::getAppTrackingAuthorizationStatus() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::getAppTrackingAuthorizationStatus();
#else
    return -1;
#endif
}

void Adjust2dx::updateConversionValue(int conversionValue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::updateConversionValue(conversionValue);
#endif
}

std::string Adjust2dx::getLastDeeplink() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return ADJAdjust2dx::getLastDeeplink();
#else
    return "";
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject getTestOptions(std::map<std::string, std::string> testOptions) {
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
    if (testOptions.find("setContext") != testOptions.end()) {
        jfieldID jfidContext = jmiInit.env->GetFieldID(jclsTestOptions, "context", "Landroid/content/Context;");
        jmiInit.env->SetObjectField(jTestOptions, jfidContext, jContext);
    }
    jmiGetContext.env->DeleteLocalRef(jContext);

    // Base URL.
    jstring jBaseUrl = jmiInit.env->NewStringUTF(testOptions["baseUrl"].c_str());
    jfieldID jfidBaseUrl = jmiInit.env->GetFieldID(jclsTestOptions, "baseUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidBaseUrl, jBaseUrl);

    // GDPR URL.
    jstring jsGdprUrl = jmiInit.env->NewStringUTF(testOptions["gdprUrl"].c_str());
    jfieldID jfidGdprUrl = jmiInit.env->GetFieldID(jclsTestOptions, "gdprUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidGdprUrl, jsGdprUrl);

    // Subscription URL.
    jstring jsSubscriptionUrl = jmiInit.env->NewStringUTF(testOptions["subscriptionUrl"].c_str());
    jfieldID jfidSubscriptionUrl = jmiInit.env->GetFieldID(jclsTestOptions, "subscriptionUrl", "Ljava/lang/String;");
    jmiInit.env->SetObjectField(jTestOptions, jfidSubscriptionUrl, jsSubscriptionUrl);

    // Base path.
    if (testOptions.find("basePath") != testOptions.end()) {
        jstring jsBasePath = jmiInit.env->NewStringUTF(testOptions["basePath"].c_str());
        jfieldID jfidBasePath = jmiInit.env->GetFieldID(jclsTestOptions, "basePath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidBasePath, jsBasePath);
    }

    // GDPR path.
    if (testOptions.find("gdprPath") != testOptions.end()) {
        jstring jsGdprPath = jmiInit.env->NewStringUTF(testOptions["gdprPath"].c_str());
        jfieldID jfidGdprPath = jmiInit.env->GetFieldID(jclsTestOptions, "gdprPath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidGdprPath, jsGdprPath);
    }

    // GDPR path.
    if (testOptions.find("subscriptionPath") != testOptions.end()) {
        jstring jsSubscriptionPath = jmiInit.env->NewStringUTF(testOptions["subscriptionPath"].c_str());
        jfieldID jfidSubscriptionPath = jmiInit.env->GetFieldID(jclsTestOptions, "subscriptionPath", "Ljava/lang/String;");
        jmiInit.env->SetObjectField(jTestOptions, jfidSubscriptionPath, jsSubscriptionPath);
    }

    // Use test connection options.
    if (testOptions.find("useTestConnectionOptions") != testOptions.end()) {
        jboolean jUseTestConnectionOptions = testOptions["useTestConnectionOptions"] == "true" ? JNI_TRUE : JNI_FALSE;
        jobject jUseTestConnectionOptionsObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jUseTestConnectionOptions);
        jfieldID jfidUseTestConnectionOptions = jmiInit.env->GetFieldID(jclsTestOptions, "useTestConnectionOptions", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidUseTestConnectionOptions, jUseTestConnectionOptionsObj);
        jmiInit.env->DeleteLocalRef(jUseTestConnectionOptionsObj);
    }

    // Timer interval in milliseconds.
    if (testOptions.find("timerIntervalInMilliseconds") != testOptions.end()) {
        long timerIntervalInMilliseconds = atol(testOptions["timerIntervalInMilliseconds"].c_str());
        jlong jTimerIntervalInMilliseconds = (jlong)(timerIntervalInMilliseconds);
        jobject jTimerIntervalInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jTimerIntervalInMilliseconds);
        jfieldID jfidTimerIntervalInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "timerIntervalInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTimerIntervalInMilliseconds, jTimerIntervalInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jTimerIntervalInMillisecondsObj);
    }

    // Timer start in milliseconds.
    if (testOptions.find("timerStartInMilliseconds") != testOptions.end()) {
        long timerStartInMilliseconds = atol(testOptions["timerStartInMilliseconds"].c_str());
        jlong jTimerStartInMilliseconds = (jlong)(timerStartInMilliseconds);
        jobject jTimerStartInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jTimerStartInMilliseconds);
        jfieldID jfidTimerStartInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "timerStartInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTimerStartInMilliseconds, jTimerStartInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jTimerStartInMillisecondsObj);
    }

    // Session interval in milliseconds.
    if (testOptions.find("sessionIntervalInMilliseconds") != testOptions.end()) {
        long sessionIntervalInMilliseconds = atol(testOptions["sessionIntervalInMilliseconds"].c_str());
        jlong jSessionIntervalInMilliseconds = (jlong)(sessionIntervalInMilliseconds);
        jobject jSessionIntervalInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jSessionIntervalInMilliseconds);
        jfieldID jfidSessionIntervalInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "sessionIntervalInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidSessionIntervalInMilliseconds, jSessionIntervalInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jSessionIntervalInMillisecondsObj);
    }

    // Sub-session interval in milliseconds.
    if (testOptions.find("subsessionIntervalInMilliseconds") != testOptions.end()) {
        long subsessionIntervalInMilliseconds = atol(testOptions["subsessionIntervalInMilliseconds"].c_str());
        jlong jSubsessionIntervalInMilliseconds = (jlong)(subsessionIntervalInMilliseconds);
        jobject jSubsessionIntervalInMillisecondsObj = jmiInitLong.env->NewObject(clsLong, midInitLong, jSubsessionIntervalInMilliseconds);
        jfieldID jfidSubsessionIntervalInMilliseconds = jmiInit.env->GetFieldID(jclsTestOptions, "subsessionIntervalInMilliseconds", "Ljava/lang/Long;");
        jmiInit.env->SetObjectField(jTestOptions, jfidSubsessionIntervalInMilliseconds, jSubsessionIntervalInMillisecondsObj);
        jmiInit.env->DeleteLocalRef(jSubsessionIntervalInMillisecondsObj);
    }

    // Teardown.
    if (testOptions.find("teardown") != testOptions.end()) {
        jboolean jTeardown = testOptions["teardown"] == "true" ? JNI_TRUE : JNI_FALSE;
        jobject jTeardownObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jTeardown);
        jfieldID jfidTeardown = jmiInit.env->GetFieldID(jclsTestOptions, "teardown", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTeardown, jTeardownObj);
        jmiInit.env->DeleteLocalRef(jTeardownObj);
    }

    // Try install referrer.
    if (testOptions.find("tryInstallReferrer") != testOptions.end()) {
        jboolean jTryInstallReferrer = testOptions["tryInstallReferrer"] == "true" ? JNI_TRUE : JNI_FALSE;
        jobject jTryInstallReferrerObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jTryInstallReferrer);
        jfieldID jfidTryInstallReferrer = jmiInit.env->GetFieldID(jclsTestOptions, "tryInstallReferrer", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidTryInstallReferrer, jTryInstallReferrerObj);
        jmiInit.env->DeleteLocalRef(jTryInstallReferrerObj);
    }

    // No backoff wait.
    if (testOptions.find("noBackoffWait") != testOptions.end()) { 
        jboolean jNoBackoffWait = testOptions["noBackoffWait"] == "true" ? JNI_TRUE : JNI_FALSE;
        jobject jNoBackoffWaitObj = jmiInitBoolean.env->NewObject(jclsBoolean, midInitBoolean, jNoBackoffWait);
        jfieldID jfidNoBackoffWait = jmiInit.env->GetFieldID(jclsTestOptions, "noBackoffWait", "Ljava/lang/Boolean;");
        jmiInit.env->SetObjectField(jTestOptions, jfidNoBackoffWait, jNoBackoffWaitObj);
        jmiInit.env->DeleteLocalRef(jNoBackoffWaitObj);
    }

    return jTestOptions;
}
#endif

void Adjust2dx::setTestOptions(std::map<std::string, std::string> testOptions) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject jTestOptions = getTestOptions(testOptions);
    cocos2d::JniMethodInfo jmiSetTestOptions;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiSetTestOptions, "com/adjust/sdk/Adjust", "setTestOptions", "(Lcom/adjust/sdk/AdjustTestOptions;)V")) {
        return;
    }
    jmiSetTestOptions.env->CallStaticVoidMethod(jmiSetTestOptions.classID, jmiSetTestOptions.methodID, jTestOptions);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::setTestOptions(testOptions);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void Adjust2dx::teardown() {
    ADJAdjust2dx::teardown();
}
#endif
