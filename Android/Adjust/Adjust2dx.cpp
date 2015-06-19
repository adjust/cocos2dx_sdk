/*
 * Adjust2dx.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: uerceg
 */

#include "Adjust/Adjust2dx.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"


void Adjust2dx::trackEvent(AdjustEvent2dx event) {
	cocos2d::JniMethodInfo methodInfo;

	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/adjust/sdk/Adjust", "trackEvent",
			"(Lcom/adjust/sdk/AdjustEvent;)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, event.getEvent());
}

void Adjust2dx::setEnabled(bool isEnabled) {
	cocos2d::JniMethodInfo methodInfo;

	if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/adjust/sdk/Adjust", "setEnabled", "(Z)V")) {
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, isEnabled);
	}
}

bool Adjust2dx::isEnabled() {
	return false;
}

void Adjust2dx::setOfflineMode(bool isOffline) {
	cocos2d::JniMethodInfo methodInfo;

	if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/adjust/sdk/Adjust", "setOfflineMode", "(Z)V")) {
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, isOffline);
	}
}

