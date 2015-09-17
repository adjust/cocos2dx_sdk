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
#endif

#include "AdjustConfig2dx.h"

void AdjustConfig2dx::initConfig(std::string appToken, std::string environment) {
	std::string sdkPrefix = "cocos2d-x4.1.0";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miInit;

	if (cocos2d::JniHelper::getMethodInfo(miInit, "com.adjust.sdk.AdjustConfig", "<init>",
			"(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V")) {
		jclass clsAdjustConfig = miInit.env->FindClass("com.adjust.sdk.AdjustConfig");
		jmethodID midInit = miInit.env->GetMethodID(clsAdjustConfig, "<init>",
				"(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");

		cocos2d::JniMethodInfo miGetContext;

		if (cocos2d::JniHelper::getStaticMethodInfo(miGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext",
				"()Landroid/content/Context;")) {
			// Get context and initialize config object.
			jobject jContext = (jobject)miGetContext.env->CallStaticObjectMethod(miGetContext.classID, miGetContext.methodID);
			jstring jAppToken = miInit.env->NewStringUTF(appToken.c_str());
			jstring jEnvironment = miInit.env->NewStringUTF(environment.c_str());

			config = miInit.env->NewObject(clsAdjustConfig, midInit, jContext, jAppToken, jEnvironment);

			miGetContext.env->DeleteLocalRef(jContext);
			miInit.env->DeleteLocalRef(jAppToken);
			miInit.env->DeleteLocalRef(jEnvironment);

			// Set SDK prefix.
			cocos2d::JniMethodInfo miSetSdkPrefix;

			if (cocos2d::JniHelper::getMethodInfo(miSetSdkPrefix, "com.adjust.sdk.AdjustConfig", "setSdkPrefix",
					"(Ljava/lang/String;)V")) {
				jstring jSdkPrefix = miSetSdkPrefix.env->NewStringUTF(sdkPrefix.c_str());

				miSetSdkPrefix.env->CallVoidMethod(config, miSetSdkPrefix.methodID, jSdkPrefix);

				miSetSdkPrefix.env->DeleteLocalRef(jSdkPrefix);
			}
		}
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    config = ADJConfig2dx(appToken, environment, sdkPrefix);
    isConfigSet = true;
#endif
}

void AdjustConfig2dx::setLogLevel(AdjustLogLevel2dx logLevel) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miSetLogLevel;

	if (NULL != config) {
		if (cocos2d::JniHelper::getMethodInfo(miSetLogLevel, "com.adjust.sdk.AdjustConfig", "setLogLevel",
				"(Lcom/adjust/sdk/LogLevel;)V")) {
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
		}
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setLogLevel((ADJLogLevel2dx)logLevel);
    }
#endif
}

void AdjustConfig2dx::setEventBufferingEnabled(bool isEnabled) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miSetEventBufferingEnabled;

	if (NULL != config) {
		if (cocos2d::JniHelper::getMethodInfo(miSetEventBufferingEnabled, "com.adjust.sdk.AdjustConfig",
				"setEventBufferingEnabled", "(Z)V")) {
			miSetEventBufferingEnabled.env->CallVoidMethod(config, miSetEventBufferingEnabled.methodID, isEnabled);
		}
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setEventBufferingEnabled(isEnabled);
    }
#endif
}

void AdjustConfig2dx::setDefaultTracker(std::string defaultTracker) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo miSetDefaultTracker;

	if (NULL != config) {
		if (cocos2d::JniHelper::getMethodInfo(miSetDefaultTracker, "com.adjust.sdk.AdjustConfig", "setDefaultTracker",
				"(Ljava/lang/String;)V")) {
			jstring jDefaultTracker = miSetDefaultTracker.env->NewStringUTF(defaultTracker.c_str());

			miSetDefaultTracker.env->CallVoidMethod(config, miSetDefaultTracker.methodID, jDefaultTracker);

			miSetDefaultTracker.env->DeleteLocalRef(jDefaultTracker);
		}
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setDefaultTracker(defaultTracker);
    }
#endif
}

void AdjustConfig2dx::setAttributionCallback(void (*callbackMethod)(AdjustAttribution2dx attribution)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	setAttributionCallbackMethod(callbackMethod);

	cocos2d::JniMethodInfo miSetCallback;

	if (NULL != config) {
		if (cocos2d::JniHelper::getMethodInfo(miSetCallback, "com.adjust.sdk.AdjustConfig", "setOnAttributionChangedListener",
				"(Lcom/adjust/sdk/OnAttributionChangedListener;)V")) {
			cocos2d::JniMethodInfo miInit;

			if (cocos2d::JniHelper::getMethodInfo(miInit, "com.adjust.sdk.Adjust2dxAttributionCallback", "<init>", "()V")) {
				jclass clsAdjust2dxAttributionCallback = miInit.env->FindClass("com/adjust/sdk/Adjust2dxAttributionCallback");
				jmethodID midInit = miInit.env->GetMethodID(clsAdjust2dxAttributionCallback, "<init>", "()V");
				jobject jCallbackProxy = miInit.env->NewObject(clsAdjust2dxAttributionCallback, midInit);

				miSetCallback.env->CallVoidMethod(config, miSetCallback.methodID, jCallbackProxy);

				miInit.env->DeleteLocalRef(jCallbackProxy);
			}
		}
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isConfigSet) {
        config.setAttributionCallback(callbackMethod);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustConfig2dx::getConfig() {
	return config;
}

void AdjustConfig2dx::setProcessName(std::string processName) {
    cocos2d::JniMethodInfo miSetProcessName;

    if (NULL != config) {
        if (cocos2d::JniHelper::getMethodInfo(miSetProcessName, "com.adjust.sdk.AdjustConfig", "setProcessName",
                                              "(Ljava/lang/String;)V")) {
            jstring jProcessName = miSetProcessName.env->NewStringUTF(processName.c_str());

            miSetProcessName.env->CallVoidMethod(config, miSetProcessName.methodID, jProcessName);
            
            miSetProcessName.env->DeleteLocalRef(jProcessName);
        }
    }
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJConfig2dx AdjustConfig2dx::getConfig() {
    return config;
}

void AdjustConfig2dx::setMacMd5TrackingEnabled(bool isEnabled) {
    if (isConfigSet) {
        config.setMacMd5TrackingEnabled(isEnabled);
    }
}
#endif
