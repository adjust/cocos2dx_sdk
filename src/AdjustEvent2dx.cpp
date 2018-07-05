//
//  AdjustEvent2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#include "AdjustEvent2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustEvent2dx::initEvent(std::string eventToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo miInit;

    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/AdjustEvent", "<init>", "(Ljava/lang/String;)V")) {
        return;
    }

    jclass clsAdjustEvent = miInit.env->FindClass("com/adjust/sdk/AdjustEvent");
    jmethodID midInit = miInit.env->GetMethodID(clsAdjustEvent, "<init>", "(Ljava/lang/String;)V");
    jstring jToken = miInit.env->NewStringUTF(eventToken.c_str());

    event = miInit.env->NewObject(clsAdjustEvent, midInit, jToken);

    miInit.env->DeleteLocalRef(jToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    event = ADJEvent2dx(eventToken);
    isEventSet = true;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::wstring wstrEventToken = std::wstring(eventToken.begin(), eventToken.end());
    const wchar_t* wcharEventToken = wstrEventToken.c_str();
    event = ref new WRTAdjustEvent(ref new Platform::String(wcharEventToken));
    isEventSet = true;
#endif
}

void AdjustEvent2dx::addCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miAddCallbackParameter;

    if (!cocos2d::JniHelper::getMethodInfo(miAddCallbackParameter, "com/adjust/sdk/AdjustEvent", "addCallbackParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miAddCallbackParameter.env->NewStringUTF(key.c_str());
    jstring jValue = miAddCallbackParameter.env->NewStringUTF(value.c_str());

    miAddCallbackParameter.env->CallVoidMethod(event, miAddCallbackParameter.methodID, jKey, jValue);

    miAddCallbackParameter.env->DeleteLocalRef(jKey);
    miAddCallbackParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.addCallbackParameter(key, value);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isEventSet) {
        std::wstring wstrKey = std::wstring(key.begin(), key.end());
        std::wstring wstrValue = std::wstring(value.begin(), value.end());
        const wchar_t* wcharKey = wstrKey.c_str();
        const wchar_t* wcharValue = wstrValue.c_str();

        event->AddCallbackParameter(ref new Platform::String(wcharKey), ref new Platform::String(wcharValue));
    }
#endif
}

void AdjustEvent2dx::addPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miAddPartnerParameter;

    if (!cocos2d::JniHelper::getMethodInfo(miAddPartnerParameter, "com/adjust/sdk/AdjustEvent", "addPartnerParameter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miAddPartnerParameter.env->NewStringUTF(key.c_str());
    jstring jValue = miAddPartnerParameter.env->NewStringUTF(value.c_str());

    miAddPartnerParameter.env->CallVoidMethod(event, miAddPartnerParameter.methodID, jKey, jValue);

    miAddPartnerParameter.env->DeleteLocalRef(jKey);
    miAddPartnerParameter.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.addPartnerParameter(key, value);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isEventSet) {
        std::wstring wstrKey = std::wstring(key.begin(), key.end());
        std::wstring wstrValue = std::wstring(value.begin(), value.end());
        const wchar_t* wcharKey = wstrKey.c_str();
        const wchar_t* wcharValue = wstrValue.c_str();

        event->AddPartnerParameter(ref new Platform::String(wcharKey), ref new Platform::String(wcharValue));
    }
#endif
}

void AdjustEvent2dx::setRevenue(double amount, std::string currency) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetRevenue;

    if (!cocos2d::JniHelper::getMethodInfo(miSetRevenue, "com/adjust/sdk/AdjustEvent", "setRevenue", "(DLjava/lang/String;)V")) {
        return;
    }

    jstring jCurrency = miSetRevenue.env->NewStringUTF(currency.c_str());

    miSetRevenue.env->CallVoidMethod(event, miSetRevenue.methodID, amount, jCurrency);

    miSetRevenue.env->DeleteLocalRef(jCurrency);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setRevenue(amount, currency);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isEventSet) {
        std::wstring wstrCurrency = std::wstring(currency.begin(), currency.end());
        const wchar_t* wcharCurrency = wstrCurrency.c_str();

        event->SetRevenue(amount, ref new Platform::String(wcharCurrency));
    }
#endif
}

void AdjustEvent2dx::setTransactionId(std::string transactionId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        event.setTransactionId(transactionId);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return;
    }

    cocos2d::JniMethodInfo miSetTransactionId;

    if (!cocos2d::JniHelper::getMethodInfo(miSetTransactionId, "com/adjust/sdk/AdjustEvent", "setOrderId", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTransactionId = miSetTransactionId.env->NewStringUTF(transactionId.c_str());

    miSetTransactionId.env->CallVoidMethod(event, miSetTransactionId.methodID, jTransactionId);

    miSetTransactionId.env->DeleteLocalRef(jTransactionId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void AdjustEvent2dx::setReceipt(std::string receipt, std::string transactionId) {
    if (isEventSet) {
        event.setReceipt(receipt, transactionId);
    }
}
#endif

bool AdjustEvent2dx::isValid() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (event == NULL) {
        return false;
    }

    cocos2d::JniMethodInfo miIsValid;

    if (!cocos2d::JniHelper::getMethodInfo(miIsValid, "com/adjust/sdk/AdjustEvent", "isValid", "()Z")) {
        return false;
    }

    jboolean jIsValid = miIsValid.env->CallBooleanMethod(event, miIsValid.methodID);

    return jIsValid;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isEventSet) {
        return event.isValid();
    } else {
        return false;
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    if (isEventSet) {
        return event->IsValid();
    } else {
        return false;
    }
#else
    return false;
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustEvent2dx::getEvent() {
    return event;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJEvent2dx AdjustEvent2dx::getEvent() {
    return event;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
WRTAdjustEvent^ AdjustEvent2dx::getEvent() {
    return event;
}
#endif
