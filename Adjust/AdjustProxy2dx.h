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
static void (*callbackToTrigger)(AdjustAttribution2dx attribution);

JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionCallback_attributionChanged
(JNIEnv *, jobject, jobject);

void setAttributionCallbackMethod(void (*callbackMethod)(AdjustAttribution2dx attribution));
}

#endif
