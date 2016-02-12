//
//  AdjustProxy2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 03/09/15.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "Adjust/AdjustAttribution2dx.h"

extern "C" {
static void (*attributionCallbackMethod)(AdjustAttribution2dx attribution);
static void (*adIdCallbackMethod)(std::string adId);

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionCallback_attributionChanged
(JNIEnv *, jobject, jobject);
JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAdIdCallback_adIdRead
(JNIEnv *, jobject, jstring);

void setAttributionCallbackMethod(void (*callbackMethod)(AdjustAttribution2dx attribution));
void setAdIdCallbackMethod(void (*callbackMethod)(std::string adId));
}
#endif
