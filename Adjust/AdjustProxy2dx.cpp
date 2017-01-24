//
//  AdjustProxy2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 03/09/15.
//

#include "AdjustProxy2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
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

    jclass clsAdjustAttribution = env->FindClass("com/adjust/sdk/AdjustAttribution");

    jfieldID fTrackerTokenID = env->GetFieldID(clsAdjustAttribution, "trackerToken", "Ljava/lang/String;");
    jfieldID fTrackerNameID = env->GetFieldID(clsAdjustAttribution, "trackerName", "Ljava/lang/String;");
    jfieldID fNetworkID = env->GetFieldID(clsAdjustAttribution, "network", "Ljava/lang/String;");
    jfieldID fCampaignID = env->GetFieldID(clsAdjustAttribution, "campaign", "Ljava/lang/String;");
    jfieldID fAdgroupID = env->GetFieldID(clsAdjustAttribution, "adgroup", "Ljava/lang/String;");
    jfieldID fCreativeID = env->GetFieldID(clsAdjustAttribution, "creative", "Ljava/lang/String;");
    jfieldID fClickLabelID = env->GetFieldID(clsAdjustAttribution, "clickLabel", "Ljava/lang/String;");
    jfieldID fAdidID = env->GetFieldID(clsAdjustAttribution, "adid", "Ljava/lang/String;");

    jstring jTrackerToken = (jstring)env->GetObjectField(attributionObject, fTrackerTokenID);
    jstring jTrackerName = (jstring)env->GetObjectField(attributionObject, fTrackerNameID);
    jstring jNetwork = (jstring)env->GetObjectField(attributionObject, fNetworkID);
    jstring jCampaign = (jstring)env->GetObjectField(attributionObject, fCampaignID);
    jstring jAdgroup = (jstring)env->GetObjectField(attributionObject, fAdgroupID);
    jstring jCreative = (jstring)env->GetObjectField(attributionObject, fCreativeID);
    jstring jClickLabel = (jstring)env->GetObjectField(attributionObject, fClickLabelID);
    jstring jAdid = (jstring)env->GetObjectField(attributionObject, fAdidID);

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
    std::string willRetry;
    std::string jsonResponse;

    jclass clsAdjustEventFailure = env->FindClass("com/adjust/sdk/AdjustEventFailure");

    jfieldID fMessageID = env->GetFieldID(clsAdjustEventFailure, "message", "Ljava/lang/String;");
    jfieldID fTimestampID = env->GetFieldID(clsAdjustEventFailure, "timestamp", "Ljava/lang/String;");
    jfieldID fAdidID = env->GetFieldID(clsAdjustEventFailure, "adid", "Ljava/lang/String;");
    jfieldID fEventTokenID = env->GetFieldID(clsAdjustEventFailure, "eventToken", "Ljava/lang/String;");
    jfieldID fWillRetryID = env->GetFieldID(clsAdjustEventFailure, "willRetry", "Z");
    jfieldID fJsonResponseID = env->GetFieldID(clsAdjustEventFailure, "jsonResponse", "Lorg/json/JSONObject;");

    jstring jMessage = (jstring)env->GetObjectField(eventFailureObject, fMessageID);
    jstring jTimestamp = (jstring)env->GetObjectField(eventFailureObject, fTimestampID);
    jstring jAdid = (jstring)env->GetObjectField(eventFailureObject, fAdidID);
    jstring jEventToken = (jstring)env->GetObjectField(eventFailureObject, fEventTokenID);
    
    jboolean jWillRetryObj = env->GetBooleanField(eventFailureObject, fWillRetryID);
    jstring jWillRetry = JNI_TRUE == jWillRetryObj ? env->NewStringUTF("true") : env->NewStringUTF("false");

    jobject jJsonResponseObj = env->GetObjectField(eventFailureObject, fJsonResponseID);
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
        jmethodID jToStringID = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToStringID);

        if (NULL != jJsonResponse) {
            const char *jsonResponseCStr = env->GetStringUTFChars(jJsonResponse, NULL);
            jsonResponse = std::string(jsonResponseCStr);
            env->ReleaseStringUTFChars(jJsonResponse, jsonResponseCStr);
            env->DeleteLocalRef(jJsonResponse);
        } else {
            jsonResponse = "";
        }
    }

    AdjustEventFailure2dx eventFailure = AdjustEventFailure2dx(adid, message, timestamp, willRetry, eventToken, jsonResponse);
    
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
    std::string jsonResponse;

    jclass clsAdjustEventSuccess = env->FindClass("com/adjust/sdk/AdjustEventSuccess");

    jfieldID fMessageID = env->GetFieldID(clsAdjustEventSuccess, "message", "Ljava/lang/String;");
    jfieldID fTimestampID = env->GetFieldID(clsAdjustEventSuccess, "timestamp", "Ljava/lang/String;");
    jfieldID fAdidID = env->GetFieldID(clsAdjustEventSuccess, "adid", "Ljava/lang/String;");
    jfieldID fEventTokenID = env->GetFieldID(clsAdjustEventSuccess, "eventToken", "Ljava/lang/String;");
    jfieldID fJsonResponseID = env->GetFieldID(clsAdjustEventSuccess, "jsonResponse", "Lorg/json/JSONObject;");

    jstring jMessage = (jstring)env->GetObjectField(eventSuccessObject, fMessageID);
    jstring jTimestamp = (jstring)env->GetObjectField(eventSuccessObject, fTimestampID);
    jstring jAdid = (jstring)env->GetObjectField(eventSuccessObject, fAdidID);
    jstring jEventToken = (jstring)env->GetObjectField(eventSuccessObject, fEventTokenID);
    jobject jJsonResponseObj = (jobject)env->GetObjectField(eventSuccessObject, fJsonResponseID);
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

    if (NULL != jJsonResponseObj) {
        jclass jcJsonObject = env->FindClass("org/json/JSONObject");
        jmethodID jToStringID = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToStringID);

        if (NULL != jJsonResponse) {
            const char *jsonResponseCStr = env->GetStringUTFChars(jJsonResponse, NULL);
            jsonResponse = std::string(jsonResponseCStr);
            env->ReleaseStringUTFChars(jJsonResponse, jsonResponseCStr);
            env->DeleteLocalRef(jJsonResponse);
        } else {
            jsonResponse = "";
        }
    }

    AdjustEventSuccess2dx eventSuccess = AdjustEventSuccess2dx(adid, message, timestamp, eventToken, jsonResponse);
    
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

    jclass clsAdjustSessionFailure = env->FindClass("com/adjust/sdk/AdjustSessionFailure");

    jfieldID fMessageID = env->GetFieldID(clsAdjustSessionFailure, "message", "Ljava/lang/String;");
    jfieldID fTimestampID = env->GetFieldID(clsAdjustSessionFailure, "timestamp", "Ljava/lang/String;");
    jfieldID fAdidID = env->GetFieldID(clsAdjustSessionFailure, "adid", "Ljava/lang/String;");
    jfieldID fWillRetryID = env->GetFieldID(clsAdjustSessionFailure, "willRetry", "Z");
    jfieldID fJsonResponseID = env->GetFieldID(clsAdjustSessionFailure, "jsonResponse", "Lorg/json/JSONObject;");

    jstring jMessage = (jstring)env->GetObjectField(sessionFailureObject, fMessageID);
    jstring jTimestamp = (jstring)env->GetObjectField(sessionFailureObject, fTimestampID);
    jstring jAdid = (jstring)env->GetObjectField(sessionFailureObject, fAdidID);
    
    jboolean jWillRetryObj = env->GetBooleanField(sessionFailureObject, fWillRetryID);
    jstring jWillRetry = JNI_TRUE == jWillRetryObj ? env->NewStringUTF("true") : env->NewStringUTF("false");
    
    jobject jJsonResponseObj = env->GetObjectField(sessionFailureObject, fJsonResponseID);
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
        jmethodID jToStringID = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToStringID);

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

    jclass clsAdjustSessionSuccess = env->FindClass("com/adjust/sdk/AdjustSessionSuccess");

    jfieldID fMessageID = env->GetFieldID(clsAdjustSessionSuccess, "message", "Ljava/lang/String;");
    jfieldID fTimestampID = env->GetFieldID(clsAdjustSessionSuccess, "timestamp", "Ljava/lang/String;");
    jfieldID fAdidID = env->GetFieldID(clsAdjustSessionSuccess, "adid", "Ljava/lang/String;");
    jfieldID fJsonResponseID = env->GetFieldID(clsAdjustSessionSuccess, "jsonResponse", "Lorg/json/JSONObject;");

    jstring jMessage = (jstring)env->GetObjectField(sessionSuccessObject, fMessageID);
    jstring jTimestamp = (jstring)env->GetObjectField(sessionSuccessObject, fTimestampID);
    jstring jAdid = (jstring)env->GetObjectField(sessionSuccessObject, fAdidID);
    jobject jJsonResponseObj = (jobject)env->GetObjectField(sessionSuccessObject, fJsonResponseID);
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
        jmethodID jToStringID = env->GetMethodID(jcJsonObject, "toString", "()Ljava/lang/String;");
        jJsonResponse = (jstring)env->CallObjectMethod(jJsonResponseObj, jToStringID);

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
