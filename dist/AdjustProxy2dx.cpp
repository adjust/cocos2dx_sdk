//
//  AdjustProxy2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 3rd September 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#include "AdjustProxy2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JNIEXPORT void Java_com_adjust_test_Adjust2dxCommandJsonListenerCallback_executeCommand2dx
(JNIEnv *env, jobject obj, jstring jClassName, jstring jMethodName, jstring jJsonParameters) {
    if (NULL == executeTestLibCommandCallbackMethod) {
        return;
    }

    const char *classNameCStr = env->GetStringUTFChars(jClassName, NULL);
    const char *methodNameCStr = env->GetStringUTFChars(jMethodName, NULL);
    const char *jsonParametersCStr = env->GetStringUTFChars(jJsonParameters, NULL);
    std::string className = std::string(classNameCStr);
    std::string methodName = std::string(methodNameCStr);
    std::string jsonParameters = std::string(jsonParametersCStr);

    executeTestLibCommandCallbackMethod(className, methodName, jsonParameters);

    env->ReleaseStringUTFChars(jClassName, classNameCStr);
    env->ReleaseStringUTFChars(jMethodName, methodNameCStr);
    env->ReleaseStringUTFChars(jJsonParameters, jsonParametersCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionCallback_attributionChanged
(JNIEnv *env, jobject obj, jobject attributionObject) {
    if (NULL == attributionCallbackMethod) {
        return;
    }

    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;
    std::string adid;

    jclass jclsAdjustAttribution = env->FindClass("com/adjust/sdk/AdjustAttribution");
    jfieldID jfidTrackerToken = env->GetFieldID(jclsAdjustAttribution, "trackerToken", "Ljava/lang/String;");
    jfieldID jfidTrackerName = env->GetFieldID(jclsAdjustAttribution, "trackerName", "Ljava/lang/String;");
    jfieldID jfidNetwork = env->GetFieldID(jclsAdjustAttribution, "network", "Ljava/lang/String;");
    jfieldID jfidCampaign = env->GetFieldID(jclsAdjustAttribution, "campaign", "Ljava/lang/String;");
    jfieldID jfidAdgroup = env->GetFieldID(jclsAdjustAttribution, "adgroup", "Ljava/lang/String;");
    jfieldID jfidCreative = env->GetFieldID(jclsAdjustAttribution, "creative", "Ljava/lang/String;");
    jfieldID jfidClickLabel = env->GetFieldID(jclsAdjustAttribution, "clickLabel", "Ljava/lang/String;");
    jfieldID jfidAdid = env->GetFieldID(jclsAdjustAttribution, "adid", "Ljava/lang/String;");
    jstring jTrackerToken = (jstring)env->GetObjectField(attributionObject, jfidTrackerToken);
    jstring jTrackerName = (jstring)env->GetObjectField(attributionObject, jfidTrackerName);
    jstring jNetwork = (jstring)env->GetObjectField(attributionObject, jfidNetwork);
    jstring jCampaign = (jstring)env->GetObjectField(attributionObject, jfidCampaign);
    jstring jAdgroup = (jstring)env->GetObjectField(attributionObject, jfidAdgroup);
    jstring jCreative = (jstring)env->GetObjectField(attributionObject, jfidCreative);
    jstring jClickLabel = (jstring)env->GetObjectField(attributionObject, jfidClickLabel);
    jstring jAdid = (jstring)env->GetObjectField(attributionObject, jfidAdid);

    if (NULL != jTrackerToken) {
        const char *trackerTokenCStr = env->GetStringUTFChars(jTrackerToken, NULL);
        trackerToken = std::string(trackerTokenCStr);
        env->ReleaseStringUTFChars(jTrackerToken, trackerTokenCStr);
        env->DeleteLocalRef(jTrackerToken);
    } else {
        trackerToken = "";
    }

    if (NULL != jTrackerName) {
        const char *trackerNameCStr = env->GetStringUTFChars(jTrackerName, NULL);
        trackerName = std::string(trackerNameCStr);
        env->ReleaseStringUTFChars(jTrackerName, trackerNameCStr);
        env->DeleteLocalRef(jTrackerName);
    } else {
        trackerName = "";
    }

    if (NULL != jNetwork) {
        const char *networkCStr = env->GetStringUTFChars(jNetwork, NULL);
        network = std::string(networkCStr);
        env->ReleaseStringUTFChars(jNetwork, networkCStr);
        env->DeleteLocalRef(jNetwork);
    } else {
        network = "";
    }

    if (NULL != jCampaign) {
        const char *campaignCStr = env->GetStringUTFChars(jCampaign, NULL);
        campaign = std::string(campaignCStr);
        env->ReleaseStringUTFChars(jCampaign, campaignCStr);
        env->DeleteLocalRef(jCampaign);
    } else {
        campaign = "";
    }

    if (NULL != jAdgroup) {
        const char *adgroupCStr = env->GetStringUTFChars(jAdgroup, NULL);
        adgroup = std::string(adgroupCStr);
        env->ReleaseStringUTFChars(jAdgroup, adgroupCStr);
        env->DeleteLocalRef(jAdgroup);
    } else {
        adgroup = "";
    }

    if (NULL != jCreative) {
        const char *creativeCStr = env->GetStringUTFChars(jCreative, NULL);
        creative = std::string(creativeCStr);
        env->ReleaseStringUTFChars(jCreative, creativeCStr);
        env->DeleteLocalRef(jCreative);
    } else {
        creative = "";
    }

    if (NULL != jClickLabel) {
        const char *clickLabelCStr = env->GetStringUTFChars(jClickLabel, NULL);
        clickLabel = std::string(clickLabelCStr);
        env->ReleaseStringUTFChars(jClickLabel, clickLabelCStr);
        env->DeleteLocalRef(jClickLabel);
    } else {
        clickLabel = "";
    }

    if (NULL != jAdid) {
        const char *adidCStr = env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        env->ReleaseStringUTFChars(jAdid, adidCStr);
        env->DeleteLocalRef(jAdid);
    } else {
        adid = "";
    }

    AdjustAttribution2dx attribution = AdjustAttribution2dx(trackerToken, trackerName, network, campaign, adgroup, creative, clickLabel, adid);
    attributionCallbackMethod(attribution);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxEventTrackingFailedCallback_eventTrackingFailed
(JNIEnv *env, jobject obj, jobject eventFailureObject) {
    if (NULL == eventTrackingFailedCallbackMethod) {
        return;
    }
    if (NULL == eventFailureObject) {
        return;
    }

    std::string message;
    std::string timestamp;
    std::string adid;
    std::string eventToken;
    std::string callbackId;
    std::string willRetry;
    std::string jsonResponse;

    jclass jclsAdjustEventFailure = env->FindClass("com/adjust/sdk/AdjustEventFailure");
    jfieldID jfidMessage = env->GetFieldID(jclsAdjustEventFailure, "message", "Ljava/lang/String;");
    jfieldID jfidTimestamp = env->GetFieldID(jclsAdjustEventFailure, "timestamp", "Ljava/lang/String;");
    jfieldID jfidAdid = env->GetFieldID(jclsAdjustEventFailure, "adid", "Ljava/lang/String;");
    jfieldID jfidEventToken = env->GetFieldID(jclsAdjustEventFailure, "eventToken", "Ljava/lang/String;");
    jfieldID jfidCallbackId = env->GetFieldID(jclsAdjustEventFailure, "callbackId", "Ljava/lang/String;");
    jfieldID jfidWillRetry = env->GetFieldID(jclsAdjustEventFailure, "willRetry", "Z");
    jfieldID jfidJsonResponse = env->GetFieldID(jclsAdjustEventFailure, "jsonResponse", "Lorg/json/JSONObject;");
    jstring jMessage = (jstring)env->GetObjectField(eventFailureObject, jfidMessage);
    jstring jTimestamp = (jstring)env->GetObjectField(eventFailureObject, jfidTimestamp);
    jstring jAdid = (jstring)env->GetObjectField(eventFailureObject, jfidAdid);
    jstring jEventToken = (jstring)env->GetObjectField(eventFailureObject, jfidEventToken);
    jstring jCallbackId = (jstring)env->GetObjectField(eventFailureObject, jfidCallbackId);
    jboolean jWillRetryObj = env->GetBooleanField(eventFailureObject, jfidWillRetry);
    jstring jWillRetry = JNI_TRUE == jWillRetryObj ? env->NewStringUTF("true") : env->NewStringUTF("false");
    jobject jJsonResponseObj = env->GetObjectField(eventFailureObject, jfidJsonResponse);
    jstring jJsonResponse;

    if (NULL != jMessage) {
        const char *messageCStr = env->GetStringUTFChars(jMessage, NULL);
        message = std::string(messageCStr);
        env->ReleaseStringUTFChars(jMessage, messageCStr);
        env->DeleteLocalRef(jMessage);
    } else {
        message = "";
    }

    if (NULL != jTimestamp) {
        const char *timestampCStr = env->GetStringUTFChars(jTimestamp, NULL);
        timestamp = std::string(timestampCStr);
        env->ReleaseStringUTFChars(jTimestamp, timestampCStr);
        env->DeleteLocalRef(jTimestamp);
    } else {
        timestamp = "";
    }

    if (NULL != jAdid) {
        const char *adidCStr = env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        env->ReleaseStringUTFChars(jAdid, adidCStr);
        env->DeleteLocalRef(jAdid);
    } else {
        adid = "";
    }

    if (NULL != jEventToken) {
        const char *eventTokenCStr = env->GetStringUTFChars(jEventToken, NULL);
        eventToken = std::string(eventTokenCStr);
        env->ReleaseStringUTFChars(jEventToken, eventTokenCStr);
        env->DeleteLocalRef(jEventToken);
    } else {
        eventToken = "";
    }

    if (NULL != jCallbackId) {
        const char *callbackIdCStr = env->GetStringUTFChars(jCallbackId, NULL);
        callbackId = std::string(callbackIdCStr);
        env->ReleaseStringUTFChars(jCallbackId, callbackIdCStr);
        env->DeleteLocalRef(jCallbackId);
    } else {
        callbackId = "";
    }

    if (NULL != jWillRetry) {
        const char *willRetryCStr = env->GetStringUTFChars(jWillRetry, NULL);
        willRetry = std::string(willRetryCStr);
        env->ReleaseStringUTFChars(jWillRetry, willRetryCStr);
        env->DeleteLocalRef(jWillRetry);
    } else {
        willRetry = "";
    }

    if (NULL != jJsonResponseObj) {
        jclass jcJsonObject = env->FindClass("org/json/JSONObject");
        jmethodID jToString = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToString);

        if (NULL != jJsonResponse) {
            const char *jsonResponseCStr = env->GetStringUTFChars(jJsonResponse, NULL);
            jsonResponse = std::string(jsonResponseCStr);
            env->ReleaseStringUTFChars(jJsonResponse, jsonResponseCStr);
            env->DeleteLocalRef(jJsonResponse);
        } else {
            jsonResponse = "";
        }
    }

    AdjustEventFailure2dx eventFailure = AdjustEventFailure2dx(adid, message, timestamp, willRetry, eventToken, callbackId, jsonResponse);
    eventTrackingFailedCallbackMethod(eventFailure);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxEventTrackingSucceededCallback_eventTrackingSucceeded
(JNIEnv *env, jobject obj, jobject eventSuccessObject) {
    if (NULL == eventTrackingSucceededCallbackMethod) {
        return;
    }
    if (NULL == eventSuccessObject) {
        return;
    }

    std::string message;
    std::string timestamp;
    std::string adid;
    std::string eventToken;
    std::string callbackId;
    std::string jsonResponse;

    jclass jclsAdjustEventSuccess = env->FindClass("com/adjust/sdk/AdjustEventSuccess");
    jfieldID jfidMessage = env->GetFieldID(jclsAdjustEventSuccess, "message", "Ljava/lang/String;");
    jfieldID jfidTimestamp = env->GetFieldID(jclsAdjustEventSuccess, "timestamp", "Ljava/lang/String;");
    jfieldID jfidAdid = env->GetFieldID(jclsAdjustEventSuccess, "adid", "Ljava/lang/String;");
    jfieldID jfidEventToken = env->GetFieldID(jclsAdjustEventSuccess, "eventToken", "Ljava/lang/String;");
    jfieldID jfidCallbackId = env->GetFieldID(jclsAdjustEventSuccess, "callbackId", "Ljava/lang/String;");
    jfieldID jfidJsonResponse = env->GetFieldID(jclsAdjustEventSuccess, "jsonResponse", "Lorg/json/JSONObject;");
    jstring jMessage = (jstring)env->GetObjectField(eventSuccessObject, jfidMessage);
    jstring jTimestamp = (jstring)env->GetObjectField(eventSuccessObject, jfidTimestamp);
    jstring jAdid = (jstring)env->GetObjectField(eventSuccessObject, jfidAdid);
    jstring jEventToken = (jstring)env->GetObjectField(eventSuccessObject, jfidEventToken);
    jstring jCallbackId = (jstring)env->GetObjectField(eventSuccessObject, jfidCallbackId);
    jobject jJsonResponseObj = (jobject)env->GetObjectField(eventSuccessObject, jfidJsonResponse);
    jstring jJsonResponse;

    if (NULL != jMessage) {
        const char *messageCStr = env->GetStringUTFChars(jMessage, NULL);
        message = std::string(messageCStr);
        env->ReleaseStringUTFChars(jMessage, messageCStr);
        env->DeleteLocalRef(jMessage);
    } else {
        message = "";
    }

    if (NULL != jTimestamp) {
        const char *timestampCStr = env->GetStringUTFChars(jTimestamp, NULL);
        timestamp = std::string(timestampCStr);
        env->ReleaseStringUTFChars(jTimestamp, timestampCStr);
        env->DeleteLocalRef(jTimestamp);
    } else {
        timestamp = "";
    }

    if (NULL != jAdid) {
        const char *adidCStr = env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        env->ReleaseStringUTFChars(jAdid, adidCStr);
        env->DeleteLocalRef(jAdid);
    } else {
        adid = "";
    }

    if (NULL != jEventToken) {
        const char *eventTokenCStr = env->GetStringUTFChars(jEventToken, NULL);
        eventToken = std::string(eventTokenCStr);
        env->ReleaseStringUTFChars(jEventToken, eventTokenCStr);
        env->DeleteLocalRef(jEventToken);
    } else {
        eventToken = "";
    }

    if (NULL != jCallbackId) {
        const char *callbackIdCStr = env->GetStringUTFChars(jCallbackId, NULL);
        callbackId = std::string(callbackIdCStr);
        env->ReleaseStringUTFChars(jCallbackId, callbackIdCStr);
        env->DeleteLocalRef(jCallbackId);
    } else {
        callbackId = "";
    }

    if (NULL != jJsonResponseObj) {
        jclass jcJsonObject = env->FindClass("org/json/JSONObject");
        jmethodID jToString = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToString);

        if (NULL != jJsonResponse) {
            const char *jsonResponseCStr = env->GetStringUTFChars(jJsonResponse, NULL);
            jsonResponse = std::string(jsonResponseCStr);
            env->ReleaseStringUTFChars(jJsonResponse, jsonResponseCStr);
            env->DeleteLocalRef(jJsonResponse);
        } else {
            jsonResponse = "";
        }
    }

    AdjustEventSuccess2dx eventSuccess = AdjustEventSuccess2dx(adid, message, timestamp, eventToken, callbackId, jsonResponse);
    eventTrackingSucceededCallbackMethod(eventSuccess);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxSessionTrackingFailedCallback_sessionTrackingFailed
(JNIEnv *env, jobject obj, jobject sessionFailureObject) {
    if (NULL == sessionTrackingFailedCallbackMethod) {
        return;
    }
    if (NULL == sessionFailureObject) {
        return;
    }

    std::string message;
    std::string timestamp;
    std::string adid;
    std::string willRetry;
    std::string jsonResponse;

    jclass jclsAdjustSessionFailure = env->FindClass("com/adjust/sdk/AdjustSessionFailure");
    jfieldID jfidMessage = env->GetFieldID(jclsAdjustSessionFailure, "message", "Ljava/lang/String;");
    jfieldID jfidTimestamp = env->GetFieldID(jclsAdjustSessionFailure, "timestamp", "Ljava/lang/String;");
    jfieldID jfidAdid = env->GetFieldID(jclsAdjustSessionFailure, "adid", "Ljava/lang/String;");
    jfieldID jfidWillRetry = env->GetFieldID(jclsAdjustSessionFailure, "willRetry", "Z");
    jfieldID jfidJsonResponse = env->GetFieldID(jclsAdjustSessionFailure, "jsonResponse", "Lorg/json/JSONObject;");
    jstring jMessage = (jstring)env->GetObjectField(sessionFailureObject, jfidMessage);
    jstring jTimestamp = (jstring)env->GetObjectField(sessionFailureObject, jfidTimestamp);
    jstring jAdid = (jstring)env->GetObjectField(sessionFailureObject, jfidAdid);
    jboolean jWillRetryObj = env->GetBooleanField(sessionFailureObject, jfidWillRetry);
    jstring jWillRetry = JNI_TRUE == jWillRetryObj ? env->NewStringUTF("true") : env->NewStringUTF("false");
    jobject jJsonResponseObj = env->GetObjectField(sessionFailureObject, jfidJsonResponse);
    jstring jJsonResponse;

    if (NULL != jMessage) {
        const char *messageCStr = env->GetStringUTFChars(jMessage, NULL);
        message = std::string(messageCStr);
        env->ReleaseStringUTFChars(jMessage, messageCStr);
        env->DeleteLocalRef(jMessage);
    } else {
        message = "";
    }

    if (NULL != jTimestamp) {
        const char *timestampCStr = env->GetStringUTFChars(jTimestamp, NULL);
        timestamp = std::string(timestampCStr);
        env->ReleaseStringUTFChars(jTimestamp, timestampCStr);
        env->DeleteLocalRef(jTimestamp);
    } else {
        timestamp = "";
    }

    if (NULL != jAdid) {
        const char *adidCStr = env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        env->ReleaseStringUTFChars(jAdid, adidCStr);
        env->DeleteLocalRef(jAdid);
    } else {
        adid = "";
    }

    if (NULL != jWillRetry) {
        const char *willRetryCStr = env->GetStringUTFChars(jWillRetry, NULL);
        willRetry = std::string(willRetryCStr);
        env->ReleaseStringUTFChars(jWillRetry, willRetryCStr);
        env->DeleteLocalRef(jWillRetry);
    } else {
        willRetry = "";
    }

    if (NULL != jJsonResponseObj) {
        jclass jcJsonObject = env->FindClass("org/json/JSONObject");
        jmethodID jToString = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToString);

        if (NULL != jJsonResponse) {
            const char *jsonResponseCStr = env->GetStringUTFChars(jJsonResponse, NULL);
            jsonResponse = std::string(jsonResponseCStr);
            env->ReleaseStringUTFChars(jJsonResponse, jsonResponseCStr);
            env->DeleteLocalRef(jJsonResponse);
        } else {
            jsonResponse = "";
        }
    }

    AdjustSessionFailure2dx sessionFailure = AdjustSessionFailure2dx(adid, message, timestamp, willRetry, jsonResponse);
    sessionTrackingFailedCallbackMethod(sessionFailure);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxSessionTrackingSucceededCallback_sessionTrackingSucceeded
(JNIEnv *env, jobject obj, jobject sessionSuccessObject) {
    if (NULL == sessionTrackingSucceededCallbackMethod) {
        return;
    }
    if (NULL == sessionSuccessObject) {
        return;
    }

    std::string message;
    std::string timestamp;
    std::string adid;
    std::string eventToken;
    std::string jsonResponse;

    jclass jclsAdjustSessionSuccess = env->FindClass("com/adjust/sdk/AdjustSessionSuccess");
    jfieldID jfidMessage = env->GetFieldID(jclsAdjustSessionSuccess, "message", "Ljava/lang/String;");
    jfieldID jfidTimestamp = env->GetFieldID(jclsAdjustSessionSuccess, "timestamp", "Ljava/lang/String;");
    jfieldID jfidAdid = env->GetFieldID(jclsAdjustSessionSuccess, "adid", "Ljava/lang/String;");
    jfieldID jfidJsonResponse = env->GetFieldID(jclsAdjustSessionSuccess, "jsonResponse", "Lorg/json/JSONObject;");
    jstring jMessage = (jstring)env->GetObjectField(sessionSuccessObject, jfidMessage);
    jstring jTimestamp = (jstring)env->GetObjectField(sessionSuccessObject, jfidTimestamp);
    jstring jAdid = (jstring)env->GetObjectField(sessionSuccessObject, jfidAdid);
    jobject jJsonResponseObj = (jobject)env->GetObjectField(sessionSuccessObject, jfidJsonResponse);
    jstring jJsonResponse;

    if (NULL != jMessage) {
        const char *messageCStr = env->GetStringUTFChars(jMessage, NULL);
        message = std::string(messageCStr);
        env->ReleaseStringUTFChars(jMessage, messageCStr);
        env->DeleteLocalRef(jMessage);
    } else {
        message = "";
    }

    if (NULL != jTimestamp) {
        const char *timestampCStr = env->GetStringUTFChars(jTimestamp, NULL);
        timestamp = std::string(timestampCStr);
        env->ReleaseStringUTFChars(jTimestamp, timestampCStr);
        env->DeleteLocalRef(jTimestamp);
    } else {
        timestamp = "";
    }

    if (NULL != jAdid) {
        const char *adidCStr = env->GetStringUTFChars(jAdid, NULL);
        adid = std::string(adidCStr);
        env->ReleaseStringUTFChars(jAdid, adidCStr);
        env->DeleteLocalRef(jAdid);
    } else {
        adid = "";
    }

    if (NULL != jJsonResponseObj) {
        jclass jcJsonObject = env->FindClass("org/json/JSONObject");
        jmethodID jToString = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToString);

        if (NULL != jJsonResponse) {
            const char *jsonResponseCStr = env->GetStringUTFChars(jJsonResponse, NULL);
            jsonResponse = std::string(jsonResponseCStr);
            env->ReleaseStringUTFChars(jJsonResponse, jsonResponseCStr);
            env->DeleteLocalRef(jJsonResponse);
        } else {
            jsonResponse = "";
        }
    }

    AdjustSessionSuccess2dx sessionSuccess = AdjustSessionSuccess2dx(adid, message, timestamp, jsonResponse);
    sessionTrackingSucceededCallbackMethod(sessionSuccess);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAdIdCallback_adIdRead
(JNIEnv *env, jobject obj, jstring jAdId) {
    if (NULL == adIdCallbackMethod) {
        return;
    }
	if (NULL == jAdId) {
        return;
    }

	const char *adIdCStr = env->GetStringUTFChars(jAdId, NULL);
	std::string adId = std::string(adIdCStr);
	adIdCallbackMethod(adId);
	env->ReleaseStringUTFChars(jAdId, adIdCStr);	
}

JNIEXPORT bool JNICALL Java_com_adjust_sdk_Adjust2dxDeferredDeeplinkCallback_deferredDeeplinkReceived
(JNIEnv *env, jobject obj, jstring jDeeplink) {
    if (NULL == deferredDeeplinkCallbackMethod) {
        return true;
    }
    if (NULL == jDeeplink) {
        return true;
    }

    const char *deeplinkCStr = env->GetStringUTFChars(jDeeplink, NULL);
    std::string deeplink = std::string(deeplinkCStr);
    env->ReleaseStringUTFChars(jDeeplink, deeplinkCStr);
    return deferredDeeplinkCallbackMethod(deeplink);
}

void setExecuteTestLibCommandCallbackMethod(void(*callbackMethod)(std::string className, std::string methodName, std::string jsonParameters)) {
    if (NULL == executeTestLibCommandCallbackMethod) {
        executeTestLibCommandCallbackMethod = callbackMethod;
    }
}

void setAttributionCallbackMethod(void (*callbackMethod)(AdjustAttribution2dx attribution)) {
    if (NULL == attributionCallbackMethod) {
    	attributionCallbackMethod = callbackMethod;
    }
}

void setEventTrackingFailedCallbackMethod(void (*callbackMethod)(AdjustEventFailure2dx eventFailure)) {
    if (NULL == eventTrackingFailedCallbackMethod) {
        eventTrackingFailedCallbackMethod = callbackMethod;
    }
}

void setEventTrackingSucceededCallbackMethod(void (*callbackMethod)(AdjustEventSuccess2dx eventSuccess)) {
    if (NULL == eventTrackingSucceededCallbackMethod) {
        eventTrackingSucceededCallbackMethod = callbackMethod;
    }
}

void setSessionTrackingFailedCallbackMethod(void (*callbackMethod)(AdjustSessionFailure2dx sessionFailure)) {
    if (NULL == sessionTrackingFailedCallbackMethod) {
        sessionTrackingFailedCallbackMethod = callbackMethod;
    }
}

void setSessionTrackingSucceededCallbackMethod(void (*callbackMethod)(AdjustSessionSuccess2dx sessionSuccess)) {
    if (NULL == sessionTrackingSucceededCallbackMethod) {
        sessionTrackingSucceededCallbackMethod = callbackMethod;
    }
}

void setDeferredDeeplinkCallbackMethod(bool (*callbackMethod)(std::string deeplink)) {
    if (NULL == deferredDeeplinkCallbackMethod) {
        deferredDeeplinkCallbackMethod = callbackMethod;
    }
}

void setAdIdCallbackMethod(void (*callbackMethod)(std::string adId)) {
	if (NULL == adIdCallbackMethod) {
		adIdCallbackMethod = callbackMethod;
	}
}
#endif
