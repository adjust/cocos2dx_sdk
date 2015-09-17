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

	if (!cocos2d::JniHelper::getStaticMethodInfo(miOnCreate, "com.adjust.sdk.Adjust", "onCreate",
			"(Lcom/adjust/sdk/AdjustConfig;)V")) {
		return;
	}

	miOnCreate.env->CallStaticVoidMethod(miOnCreate.classID, miOnCreate.methodID, adjustConfig.getConfig());

	onResume();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ADJAdjust2dx::appDidLaunch(adjustConfig.getConfig());
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void Adjust2dx::onResume() {
	cocos2d::JniMethodInfo miOnResume;

	if (!cocos2d::JniHelper::getStaticMethodInfo(miOnResume, "com.adjust.sdk.Adjust", "onResume", "()V")) {
		return;
	}

	miOnResume.env->CallStaticVoidMethod(miOnResume.classID, miOnResume.methodID);
}

void Adjust2dx::onPause() {
	cocos2d::JniMethodInfo miOnPause;

	if (!cocos2d::JniHelper::getStaticMethodInfo(miOnPause, "com.adjust.sdk.Adjust", "onPause", "()V")) {
		return;
	}

	miOnPause.env->CallStaticVoidMethod(miOnPause.classID, miOnPause.methodID);
}

void Adjust2dx::setReferrer(std::string referrer) {
	cocos2d::JniMethodInfo miSetReferrer;

	if (cocos2d::JniHelper::getStaticMethodInfo(miSetReferrer, "com.adjust.sdk.Adjust", "setReferrer",
			"(Ljava/lang/String;)V")) {
		jstring jReferrer = miSetReferrer.env->NewStringUTF(referrer.c_str());

		miSetReferrer.env->CallStaticVoidMethod(miSetReferrer.classID, miSetReferrer.methodID, jReferrer);

		miSetReferrer.env->DeleteLocalRef(jReferrer);
	}
}
#endif

void Adjust2dx::trackEvent(AdjustEvent2dx event) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miTrackEvent;

	if (!cocos2d::JniHelper::getStaticMethodInfo(miTrackEvent, "com.adjust.sdk.Adjust", "trackEvent",
			"(Lcom/adjust/sdk/AdjustEvent;)V")) {
		return;
	}

	miTrackEvent.env->CallStaticVoidMethod(miTrackEvent.classID, miTrackEvent.methodID, event.getEvent());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ADJAdjust2dx::trackEvent(event.getEvent());
#endif
}

void Adjust2dx::setEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miSetEnabled;

	if (cocos2d::JniHelper::getStaticMethodInfo(miSetEnabled, "com.adjust.sdk.Adjust", "setEnabled", "(Z)V")) {
		miSetEnabled.env->CallStaticVoidMethod(miSetEnabled.classID, miSetEnabled.methodID, isEnabled);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ADJAdjust2dx::setEnabled(isEnabled);
#endif
}

bool Adjust2dx::isEnabled() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miIsEnabled;

	if (cocos2d::JniHelper::getStaticMethodInfo(miIsEnabled, "com.adjust.sdk.Adjust", "isEnabled", "()Z")) {
		jboolean jIsEnabled = miIsEnabled.env->CallStaticBooleanMethod(miIsEnabled.classID, miIsEnabled.methodID);

		return jIsEnabled;
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return ADJAdjust2dx::isEnabled();
#else
    return false;
#endif
}

void Adjust2dx::setOfflineMode(bool isOffline) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miIsOffline;

	if (cocos2d::JniHelper::getStaticMethodInfo(miIsOffline, "com.adjust.sdk.Adjust", "setOfflineMode", "(Z)V")) {
		miIsOffline.env->CallStaticVoidMethod(miIsOffline.classID, miIsOffline.methodID, isOffline);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ADJAdjust2dx::setOfflineMode(isOffline);
#endif
}

void Adjust2dx::appWillOpenUrl(void* url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdjust2dx::appWillOpenUrl(url);
#endif
}
