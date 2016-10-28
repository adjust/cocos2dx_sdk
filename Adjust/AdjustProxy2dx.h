//
//  AdjustProxy2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 03/09/15.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "Adjust/AdjustAttribution2dx.h"
#include "Adjust/AdjustEventFailure2dx.h"
#include "Adjust/AdjustEventSuccess2dx.h"
#include "Adjust/AdjustSessionFailure2dx.h"
#include "Adjust/AdjustSessionSuccess2dx.h"

extern "C" {
    static void (*attributionCallbackMethod)(AdjustAttribution2dx attribution);
    static void (*eventTrackingFailedCallbackMethod)(AdjustEventFailure2dx eventFailure);
    static void (*eventTrackingSucceededCallbackMethod)(AdjustEventSuccess2dx eventSuccess);
    static void (*sessionTrackingFailedCallbackMethod)(AdjustSessionFailure2dx sessionFailure);
    static void (*sessionTrackingSucceededCallbackMethod)(AdjustSessionSuccess2dx sessionSuccess);
    static bool (*deferredDeeplinkCallbackMethod)(std::string deeplink);
    static void (*adIdCallbackMethod)(std::string adId);

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
    JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAdIdCallback_adIdRead
    (JNIEnv *, jobject, jstring);

    void setAttributionCallbackMethod(void (*callbackMethod)(AdjustAttribution2dx attribution));
    void setEventTrackingFailedCallbackMethod(void (*callbackMethod)(AdjustEventFailure2dx eventFailure));
    void setEventTrackingSucceededCallbackMethod(void (*callbackMethod)(AdjustEventSuccess2dx eventSuccess));
    void setSessionTrackingFailedCallbackMethod(void (*callbackMethod)(AdjustSessionFailure2dx sessionFailure));
    void setSessionTrackingSucceededCallbackMethod(void (*callbackMethod)(AdjustSessionSuccess2dx sessionSuccess));
    void setDeferredDeeplinkCallbackMethod(bool (*callbackMethod)(std::string deeplink));
    void setAdIdCallbackMethod(void (*callbackMethod)(std::string adId));
}
#endif
