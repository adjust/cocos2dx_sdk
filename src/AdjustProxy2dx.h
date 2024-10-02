//
//  AdjustProxy2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 3rd September 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "Adjust/AdjustAttribution2dx.h"
#include "Adjust/AdjustEventFailure2dx.h"
#include "Adjust/AdjustEventSuccess2dx.h"
#include "Adjust/AdjustSessionFailure2dx.h"
#include "Adjust/AdjustSessionSuccess2dx.h"
#include "Adjust/AdjustPurchaseVerificationResult2dx.h"

extern "C" {
    static void (*attributionCallbackMethod)(AdjustAttribution2dx attribution);
    static void (*eventTrackingFailedCallbackMethod)(AdjustEventFailure2dx eventFailure);
    static void (*eventTrackingSucceededCallbackMethod)(AdjustEventSuccess2dx eventSuccess);
    static void (*sessionTrackingFailedCallbackMethod)(AdjustSessionFailure2dx sessionFailure);
    static void (*sessionTrackingSucceededCallbackMethod)(AdjustSessionSuccess2dx sessionSuccess);
    static bool (*deferredDeeplinkCallbackMethod)(std::string deeplink);
    static void (*isEnabledCallbackMethod)(bool isEnabled);
    static void (*googleAdIdCallbackMethod)(std::string googleAdId);
    static void (*amazonAdIdCallbackMethod)(std::string amazonAdId);
    static void (*adidCallbackMethod)(std::string adid);
    static void (*attributionReadCallbackMethod)(AdjustAttribution2dx attribution);
    static void (*lastDeeplinkCallbackMethod)(std::string deeplink);
    static void (*sdkVersionCallbackMethod)(std::string deeplink);
    static void (*resolvedLinkCallbackMethod)(std::string resolvedLink);
    static void (*verifyPlayStorePurchaseCallbackMethod)(AdjustPurchaseVerificationResult2dx verificationResult);
    static void (*verifyAndTrackPlayStorePurchaseCallbackMethod)(AdjustPurchaseVerificationResult2dx verificationResult);
    // Only for testing purposes.
    static void (*executeTestLibCommandCallbackMethod)(std::string className, std::string methodName, std::string jsonParameters);

    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionCallback_attributionChanged
    (JNIEnv *, jobject, jobject);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxEventTrackingFailedCallback_eventTrackingFailed
    (JNIEnv *, jobject, jobject);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxEventTrackingSucceededCallback_eventTrackingSucceeded
    (JNIEnv *, jobject, jobject);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxSessionTrackingFailedCallback_sessionTrackingFailed
    (JNIEnv *, jobject, jobject);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxSessionTrackingSucceededCallback_sessionTrackingSucceeded
    (JNIEnv *, jobject, jobject);
    JNIEXPORT bool JNICALL Java_com_adjust_sdk_Adjust2dxDeferredDeeplinkCallback_deferredDeeplinkReceived
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxIsEnabledCallback_isEnabledRead
    (JNIEnv *, jobject, jboolean);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxGoogleAdIdCallback_googleAdIdRead
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAmazonAdIdCallback_amazonAdIdRead
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAdidCallback_adidRead
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionReadCallback_attributionRead
    (JNIEnv *, jobject, jobject);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxLastDeeplinkCallback_lastDeeplinkRead
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxSdkVersionCallback_sdkVersionRead
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxResolvedLinkCallback_deeplinkResolved
    (JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxVerifyPlayStorePurchaseCallback_verificationResult
    (JNIEnv *, jobject, jstring, int, jstring);
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxVerifyAndTrackPlayStorePurchaseCallback_verificationResult
    (JNIEnv *, jobject, jstring, int, jstring);
    // Only for testing purposes.
    JNIEXPORT void JNICALL Java_com_adjust_test_Adjust2dxCommandJsonListenerCallback_executeCommand2dx
    (JNIEnv *, jobject, jstring, jstring, jstring);

    void setAttributionCallbackMethod(void (*callback)(AdjustAttribution2dx attribution));
    void setEventTrackingFailedCallbackMethod(void (*callback)(AdjustEventFailure2dx eventFailure));
    void setEventTrackingSucceededCallbackMethod(void (*callback)(AdjustEventSuccess2dx eventSuccess));
    void setSessionTrackingFailedCallbackMethod(void (*callback)(AdjustSessionFailure2dx sessionFailure));
    void setSessionTrackingSucceededCallbackMethod(void (*callback)(AdjustSessionSuccess2dx sessionSuccess));
    void setDeferredDeeplinkCallbackMethod(bool (*callback)(std::string deeplink));
    void setIsEnabledCallbackMethod(void (*callback)(bool isEnabled));
    void setGoogleAdIdCallbackMethod(void (*callback)(std::string googleAdId));
    void setAmazonAdIdCallbackMethod(void (*callback)(std::string amazonAdId));
    void setAdidCallbackMethod(void (*callback)(std::string adid));
    void setAttributionReadCallbackMethod(void (*callback)(AdjustAttribution2dx attribution));
    void setLastDeeplinkCallbackMethod(void (*callback)(std::string deeplink));
    void setSdkVersionCallbackMethod(void (*callback)(std::string sdkVersion));
    void setResolvedLinkCallbackMethod(void (*callback)(std::string resolvedLink));
    void setVerifyPlayStorePurchaseCallbackMethod(void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    void setVerifyAndTrackPlayStorePurchaseCallbackMethod(void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    // Only for testing purposes.
    void setExecuteTestLibCommandCallbackMethod(void (*callback)(std::string className, std::string methodName, std::string jsonParameters));
}
#endif
