//
//  AdjustProxy2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 3rd September 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
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
    std::string costType;
    double costAmount;
    std::string costCurrency;
    std::string fbInstallReferrer;

    jclass jclsAdjustAttribution = env->FindClass("com/adjust/sdk/AdjustAttribution");
    jfieldID jfidTrackerToken = env->GetFieldID(jclsAdjustAttribution, "trackerToken", "Ljava/lang/String;");
    jfieldID jfidTrackerName = env->GetFieldID(jclsAdjustAttribution, "trackerName", "Ljava/lang/String;");
    jfieldID jfidNetwork = env->GetFieldID(jclsAdjustAttribution, "network", "Ljava/lang/String;");
    jfieldID jfidCampaign = env->GetFieldID(jclsAdjustAttribution, "campaign", "Ljava/lang/String;");
    jfieldID jfidAdgroup = env->GetFieldID(jclsAdjustAttribution, "adgroup", "Ljava/lang/String;");
    jfieldID jfidCreative = env->GetFieldID(jclsAdjustAttribution, "creative", "Ljava/lang/String;");
    jfieldID jfidClickLabel = env->GetFieldID(jclsAdjustAttribution, "clickLabel", "Ljava/lang/String;");
    jfieldID jfidCostType = env->GetFieldID(jclsAdjustAttribution, "costType", "Ljava/lang/String;");
    jfieldID jfidCostAmount = env->GetFieldID(jclsAdjustAttribution, "costAmount", "Ljava/lang/Double;");
    jfieldID jfidCostCurrency = env->GetFieldID(jclsAdjustAttribution, "costCurrency", "Ljava/lang/String;");
    jfieldID jfidFbInstallReferrer = env->GetFieldID(jclsAdjustAttribution, "fbInstallReferrer", "Ljava/lang/String;");
    jstring jTrackerToken = (jstring)env->GetObjectField(attributionObject, jfidTrackerToken);
    jstring jTrackerName = (jstring)env->GetObjectField(attributionObject, jfidTrackerName);
    jstring jNetwork = (jstring)env->GetObjectField(attributionObject, jfidNetwork);
    jstring jCampaign = (jstring)env->GetObjectField(attributionObject, jfidCampaign);
    jstring jAdgroup = (jstring)env->GetObjectField(attributionObject, jfidAdgroup);
    jstring jCreative = (jstring)env->GetObjectField(attributionObject, jfidCreative);
    jstring jClickLabel = (jstring)env->GetObjectField(attributionObject, jfidClickLabel);
    jstring jCostType = (jstring)env->GetObjectField(attributionObject, jfidCostType);
    jobject jCostAmount = env->GetObjectField(attributionObject, jfidCostAmount);
    jstring jCostCurrency = (jstring)env->GetObjectField(attributionObject, jfidCostCurrency);
    jstring jFbInstallReferrer = (jstring)env->GetObjectField(attributionObject, jfidFbInstallReferrer);

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

    if (NULL != jCostType) {
        const char *costTypeCStr = env->GetStringUTFChars(jCostType, NULL);
        costType = std::string(costTypeCStr);
        env->ReleaseStringUTFChars(jCostType, costTypeCStr);
        env->DeleteLocalRef(jCostType);
    } else {
        costType = "";
    }

    if (NULL != jCostAmount) {
        jclass jcDouble = env->FindClass("java/lang/Double");
        jmethodID jmidDoubleValue = env->GetMethodID(jcDouble, "doubleValue", "()D" );
        costAmount = env->CallDoubleMethod(jCostAmount, jmidDoubleValue);
    } else {
        costAmount = 0;
    }

    if (NULL != jCostCurrency) {
        const char *costCurrencyCStr = env->GetStringUTFChars(jCostCurrency, NULL);
        costCurrency = std::string(costCurrencyCStr);
        env->ReleaseStringUTFChars(jCostCurrency, costCurrencyCStr);
        env->DeleteLocalRef(jCostCurrency);
    } else {
        costCurrency = "";
    }

    if (NULL != jFbInstallReferrer) {
        const char *fbInstallReferrerCStr = env->GetStringUTFChars(jFbInstallReferrer, NULL);
        fbInstallReferrer = std::string(fbInstallReferrerCStr);
        env->ReleaseStringUTFChars(jFbInstallReferrer, fbInstallReferrerCStr);
        env->DeleteLocalRef(jFbInstallReferrer);
    } else {
        fbInstallReferrer = "";
    }

    AdjustAttribution2dx attribution = AdjustAttribution2dx(
        trackerToken,
        trackerName,
        network,
        campaign,
        adgroup,
        creative,
        clickLabel,
        costType,
        costAmount,
        costCurrency,
        fbInstallReferrer);
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

    AdjustEventFailure2dx eventFailure = AdjustEventFailure2dx(
        adid,
        message,
        timestamp,
        willRetry,
        eventToken,
        callbackId,
        jsonResponse);
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

    AdjustEventSuccess2dx eventSuccess = AdjustEventSuccess2dx(
        adid,
        message,
        timestamp,
        eventToken,
        callbackId,
        jsonResponse);
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

    AdjustSessionFailure2dx sessionFailure = AdjustSessionFailure2dx(
        adid,
        message,
        timestamp,
        willRetry,
        jsonResponse);
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

    AdjustSessionSuccess2dx sessionSuccess = AdjustSessionSuccess2dx(
        adid,
        message,
        timestamp,
        jsonResponse);
    sessionTrackingSucceededCallbackMethod(sessionSuccess);
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

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxIsEnabledCallback_isEnabledRead
(JNIEnv *env, jobject obj, jboolean jIsEnabled) {
    if (NULL == isEnabledCallbackMethod) {
        return;
    }
    if (NULL == jIsEnabled) {
        return;
    }

    isEnabledCallbackMethod(jIsEnabled);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxGoogleAdIdCallback_googleAdIdRead
(JNIEnv *env, jobject obj, jstring jGoogleAdId) {
    if (NULL == googleAdIdCallbackMethod) {
        return;
    }
    if (NULL == jGoogleAdId) {
        googleAdIdCallbackMethod(std::string());
        return;
    }

    const char *googleAdIdCStr = env->GetStringUTFChars(jGoogleAdId, NULL);
    std::string googleAdId = std::string(googleAdIdCStr);
    googleAdIdCallbackMethod(googleAdId);
    env->ReleaseStringUTFChars(jGoogleAdId, googleAdIdCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAmazonAdIdCallback_amazonAdIdRead
(JNIEnv *env, jobject obj, jstring jAmazonAdId) {
    if (NULL == amazonAdIdCallbackMethod) {
        return;
    }
    if (NULL == jAmazonAdId) {
        amazonAdIdCallbackMethod(std::string());
        return;
    }

    const char *amazionAdIdCStr = env->GetStringUTFChars(jAmazonAdId, NULL);
    std::string amazonAdId = std::string(amazionAdIdCStr);
    amazonAdIdCallbackMethod(amazonAdId);
    env->ReleaseStringUTFChars(jAmazonAdId, amazionAdIdCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAdidCallback_adidRead
(JNIEnv *env, jobject obj, jstring jAdid) {
    if (NULL == adidCallbackMethod) {
        return;
    }
    if (NULL == jAdid) {
        adidCallbackMethod(std::string());
        return;
    }

    const char *adidCStr = env->GetStringUTFChars(jAdid, NULL);
    std::string adid = std::string(adidCStr);
    adidCallbackMethod(adid);
    env->ReleaseStringUTFChars(jAdid, adidCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionReadCallback_attributionRead
 (JNIEnv *env, jobject obj, jobject attributionObject) {
    if (NULL == attributionReadCallbackMethod) {
        return;
    }
    if (NULL == attributionObject) {
        return;
    }

    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;

    std::string costType;
    double costAmount;
    std::string costCurrency;
    std::string fbInstallReferrer;

    jclass jclsAdjustAttribution = env->FindClass("com/adjust/sdk/AdjustAttribution");
    jfieldID jfidTrackerToken = env->GetFieldID(jclsAdjustAttribution, "trackerToken", "Ljava/lang/String;");
    jfieldID jfidTrackerName = env->GetFieldID(jclsAdjustAttribution, "trackerName", "Ljava/lang/String;");
    jfieldID jfidNetwork = env->GetFieldID(jclsAdjustAttribution, "network", "Ljava/lang/String;");
    jfieldID jfidCampaign = env->GetFieldID(jclsAdjustAttribution, "campaign", "Ljava/lang/String;");
    jfieldID jfidAdgroup = env->GetFieldID(jclsAdjustAttribution, "adgroup", "Ljava/lang/String;");
    jfieldID jfidCreative = env->GetFieldID(jclsAdjustAttribution, "creative", "Ljava/lang/String;");
    jfieldID jfidClickLabel = env->GetFieldID(jclsAdjustAttribution, "clickLabel", "Ljava/lang/String;");
    jfieldID jfidCostType = env->GetFieldID(jclsAdjustAttribution, "costType", "Ljava/lang/String;");
    jfieldID jfidCostAmount = env->GetFieldID(jclsAdjustAttribution, "costAmount", "Ljava/lang/Double;");
    jfieldID jfidCostCurrency = env->GetFieldID(jclsAdjustAttribution, "costCurrency", "Ljava/lang/String;");
    jfieldID jfidFbInstallReferrer = env->GetFieldID(jclsAdjustAttribution, "fbInstallReferrer", "Ljava/lang/String;");
    jstring jTrackerToken = (jstring)env->GetObjectField(attributionObject, jfidTrackerToken);
    jstring jTrackerName = (jstring)env->GetObjectField(attributionObject, jfidTrackerName);
    jstring jNetwork = (jstring)env->GetObjectField(attributionObject, jfidNetwork);
    jstring jCampaign = (jstring)env->GetObjectField(attributionObject, jfidCampaign);
    jstring jAdgroup = (jstring)env->GetObjectField(attributionObject, jfidAdgroup);
    jstring jCreative = (jstring)env->GetObjectField(attributionObject, jfidCreative);
    jstring jClickLabel = (jstring)env->GetObjectField(attributionObject, jfidClickLabel);
    jstring jCostType = (jstring)env->GetObjectField(attributionObject, jfidCostType);
    jobject jCostAmount = env->GetObjectField(attributionObject, jfidCostAmount);
    jstring jCostCurrency = (jstring)env->GetObjectField(attributionObject, jfidCostCurrency);
    jstring jFbInstallReferrer = (jstring)env->GetObjectField(attributionObject, jfidFbInstallReferrer);

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

    if (NULL != jCostType) {
        const char *costTypeCStr = env->GetStringUTFChars(jCostType, NULL);
        costType = std::string(costTypeCStr);
        env->ReleaseStringUTFChars(jCostType, costTypeCStr);
        env->DeleteLocalRef(jCostType);
    } else {
        costType = "";
    }

    if (NULL != jCostAmount) {
        jclass jcDouble = env->FindClass("java/lang/Double");
        jmethodID jmidDoubleValue = env->GetMethodID(jcDouble, "doubleValue", "()D" );
        costAmount = env->CallDoubleMethod(jCostAmount, jmidDoubleValue);
    } else {
        costAmount = 0;
    }

    if (NULL != jCostCurrency) {
        const char *costCurrencyCStr = env->GetStringUTFChars(jCostCurrency, NULL);
        costCurrency = std::string(costCurrencyCStr);
        env->ReleaseStringUTFChars(jCostCurrency, costCurrencyCStr);
        env->DeleteLocalRef(jCostCurrency);
    } else {
        costCurrency = "";
    }

    if (NULL != jFbInstallReferrer) {
        const char *fbInstallReferrerCStr = env->GetStringUTFChars(jFbInstallReferrer, NULL);
        fbInstallReferrer = std::string(fbInstallReferrerCStr);
        env->ReleaseStringUTFChars(jFbInstallReferrer, fbInstallReferrerCStr);
        env->DeleteLocalRef(jFbInstallReferrer);
    } else {
        fbInstallReferrer = "";
    }

    AdjustAttribution2dx attribution = AdjustAttribution2dx(
        trackerToken,
        trackerName,
        network,
        campaign,
        adgroup,
        creative,
        clickLabel,
        costType,
        costAmount,
        costCurrency,
        fbInstallReferrer);
    attributionReadCallbackMethod(attribution);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxLastDeeplinkCallback_lastDeeplinkRead
(JNIEnv *env, jobject obj, jstring jDeeplink) {
    if (NULL == lastDeeplinkCallbackMethod) {
        return;
    }
    if (NULL == jDeeplink) {
        lastDeeplinkCallbackMethod(std::string());
        return;
    }

    const char *deeplinkCStr = env->GetStringUTFChars(jDeeplink, NULL);
    std::string deeplink = std::string(deeplinkCStr);
    lastDeeplinkCallbackMethod(deeplink);
    env->ReleaseStringUTFChars(jDeeplink, deeplinkCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxSdkVersionCallback_sdkVersionRead
 (JNIEnv *env, jobject obj, jstring jSdkVersion) {
    if (NULL == sdkVersionCallbackMethod) {
        return;
    }
    if (NULL == jSdkVersion) {
        sdkVersionCallbackMethod(std::string());
        return;
    }

    const char *sdkVersionCStr = env->GetStringUTFChars(jSdkVersion, NULL);
    std::string sdkVersion = std::string(sdkVersionCStr);
    sdkVersionCallbackMethod(sdkVersion);
    env->ReleaseStringUTFChars(jSdkVersion, sdkVersionCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxResolvedLinkCallback_deeplinkResolved
(JNIEnv *env, jobject obj, jstring jResolvedLink) {
    if (NULL == resolvedLinkCallbackMethod) {
        return;
    }
    if (NULL == jResolvedLink) {
        resolvedLinkCallbackMethod(std::string());
        return;
    }

    const char *resolvedLinkCStr = env->GetStringUTFChars(jResolvedLink, NULL);
    std::string resolvedLink = std::string(resolvedLinkCStr);
    resolvedLinkCallbackMethod(resolvedLink);
    env->ReleaseStringUTFChars(jResolvedLink, resolvedLinkCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxVerifyPlayStorePurchaseCallback_verificationResult
(JNIEnv *env, jobject obj, jstring jVerificationStatus, int code, jstring jMessage) {
    if (NULL == verifyPlayStorePurchaseCallbackMethod) {
        return;
    }

    const char *verificationStatusCStr = env->GetStringUTFChars(jVerificationStatus, NULL);
    std::string verificationStatus = std::string(verificationStatusCStr);
    const char *messageCStr = env->GetStringUTFChars(jMessage, NULL);
    std::string message = std::string(messageCStr);
    AdjustPurchaseVerificationResult2dx verificationResult = AdjustPurchaseVerificationResult2dx(
        verificationStatus,
        message,
        code);
    verifyPlayStorePurchaseCallbackMethod(verificationResult);
    env->ReleaseStringUTFChars(jVerificationStatus, verificationStatusCStr);
    env->ReleaseStringUTFChars(jMessage, messageCStr);
}

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxVerifyAndTrackPlayStorePurchaseCallback_verificationResult
(JNIEnv *env, jobject obj, jstring jVerificationStatus, int code, jstring jMessage) {
    if (NULL == verifyAndTrackPlayStorePurchaseCallbackMethod) {
        return;
    }

    const char *verificationStatusCStr = env->GetStringUTFChars(jVerificationStatus, NULL);
    std::string verificationStatus = std::string(verificationStatusCStr);
    const char *messageCStr = env->GetStringUTFChars(jMessage, NULL);
    std::string message = std::string(messageCStr);
    AdjustPurchaseVerificationResult2dx verificationResult = AdjustPurchaseVerificationResult2dx(
        verificationStatus,
        message,
        code);
    verifyPlayStorePurchaseCallbackMethod(verificationResult);
    env->ReleaseStringUTFChars(jVerificationStatus, verificationStatusCStr);
    env->ReleaseStringUTFChars(jMessage, messageCStr);
}

void setExecuteTestLibCommandCallbackMethod(void(*callback)(std::string className, std::string methodName, std::string jsonParameters)) {
    if (NULL == executeTestLibCommandCallbackMethod) {
        executeTestLibCommandCallbackMethod = callback;
    }
}

void setAttributionCallbackMethod(void (*callback)(AdjustAttribution2dx attribution)) {
    if (NULL == attributionCallbackMethod) {
        attributionCallbackMethod = callback;
    }
}

void setEventTrackingFailedCallbackMethod(void (*callback)(AdjustEventFailure2dx eventFailure)) {
    if (NULL == eventTrackingFailedCallbackMethod) {
        eventTrackingFailedCallbackMethod = callback;
    }
}

void setEventTrackingSucceededCallbackMethod(void (*callback)(AdjustEventSuccess2dx eventSuccess)) {
    if (NULL == eventTrackingSucceededCallbackMethod) {
        eventTrackingSucceededCallbackMethod = callback;
    }
}

void setSessionTrackingFailedCallbackMethod(void (*callback)(AdjustSessionFailure2dx sessionFailure)) {
    if (NULL == sessionTrackingFailedCallbackMethod) {
        sessionTrackingFailedCallbackMethod = callback;
    }
}

void setSessionTrackingSucceededCallbackMethod(void (*callback)(AdjustSessionSuccess2dx sessionSuccess)) {
    if (NULL == sessionTrackingSucceededCallbackMethod) {
        sessionTrackingSucceededCallbackMethod = callback;
    }
}

void setDeferredDeeplinkCallbackMethod(bool (*callback)(std::string deeplink)) {
    if (NULL == deferredDeeplinkCallbackMethod) {
        deferredDeeplinkCallbackMethod = callback;
    }
}

void setIsEnabledCallbackMethod(void (*callback)(bool isEnabled)) {
    isEnabledCallbackMethod = callback;
}

void setGoogleAdIdCallbackMethod(void (*callback)(std::string googleAdId)) {
    googleAdIdCallbackMethod = callback;
}

void setAmazonAdIdCallbackMethod(void (*callback)(std::string amazonAdId)) {
    amazonAdIdCallbackMethod = callback;
}

void setAdidCallbackMethod(void (*callback)(std::string adid)) {
    adidCallbackMethod = callback;
}

void setAttributionReadCallbackMethod(void (*callback)(AdjustAttribution2dx attribution)) {
    attributionReadCallbackMethod = callback;
}

void setLastDeeplinkCallbackMethod(void (*callback)(std::string deeplink)) {
    lastDeeplinkCallbackMethod = callback;
}

void setSdkVersionCallbackMethod(void (*callback)(std::string sdkVersion)) {
    sdkVersionCallbackMethod = callback;
}

void setResolvedLinkCallbackMethod(void (*callback)(std::string resolvedLink)) {
    resolvedLinkCallbackMethod = callback;
}

void setVerifyPlayStorePurchaseCallbackMethod(void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult)) {
    verifyPlayStorePurchaseCallbackMethod = callback;
}

void setVerifyAndTrackPlayStorePurchaseCallbackMethod(void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult)) {
    verifyAndTrackPlayStorePurchaseCallbackMethod = callback;
}

#endif
