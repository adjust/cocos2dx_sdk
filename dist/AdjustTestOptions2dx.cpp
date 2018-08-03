//
//  AdjustTestOptions2dx.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018 Adjust GmbH. All rights reserved.
//

#include "AdjustTestOptions2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ATLAdjustTestOptions2dx.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustTestOptions2dx::getTestOptions() {
    cocos2d::JniMethodInfo miInit;
    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/sdk/AdjustTestOptions", "<init>", "()V")) {
        return NULL;
    }

    cocos2d::JniMethodInfo miInitBoolean;
    if (!cocos2d::JniHelper::getMethodInfo(miInitBoolean, "java/lang/Boolean", "<init>", "(Z)V")) {
        return NULL;
    }

    jclass clsBoolean = miInitBoolean.env->FindClass("java/lang/Boolean");
    jmethodID midInitBoolean = miInitBoolean.env->GetMethodID(clsBoolean, "<init>", "(Z)V");

    cocos2d::JniMethodInfo miInitLong;
    if (!cocos2d::JniHelper::getMethodInfo(miInitLong, "java/lang/Long", "<init>", "(J)V")) {
        return NULL;
    }
    jclass clsLong = miInitLong.env->FindClass("java/lang/Long");
    jmethodID midInitLong = miInitBoolean.env->GetMethodID(clsLong, "<init>", "(J)V");

    cocos2d::JniMethodInfo miGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(miGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return NULL;
    }
    jobject jContext = (jobject)miGetContext.env->CallStaticObjectMethod(miGetContext.classID, miGetContext.methodID);

    // Test options
    jclass clsTestOptions = miInit.env->FindClass("com/adjust/sdk/AdjustTestOptions");
    jmethodID midInit = miInit.env->GetMethodID(clsTestOptions, "<init>", "()V");
    jobject jobjTestOptions = miInit.env->NewObject(clsTestOptions, midInit);

    // Context
    if (this->setContext != NULL && *this->setContext == true) {
        jfieldID fContext = miInit.env->GetFieldID(clsTestOptions, "context", "Landroid/content/Context;");
        miInit.env->SetObjectField(jobjTestOptions, fContext, jContext);
    }
    miGetContext.env->DeleteLocalRef(jContext);

    // Base URL
    jstring jsBaseUrl = miInit.env->NewStringUTF(this->baseUrl.c_str());
    jfieldID fBaseUrl = miInit.env->GetFieldID(clsTestOptions, "baseUrl", "Ljava/lang/String;");
    miInit.env->SetObjectField(jobjTestOptions, fBaseUrl, jsBaseUrl);

    // GDPR URL
    jstring jsGdprUrl = miInit.env->NewStringUTF(this->gdprUrl.c_str());
    jfieldID fGdprUrl = miInit.env->GetFieldID(clsTestOptions, "gdprUrl", "Ljava/lang/String;");
    miInit.env->SetObjectField(jobjTestOptions, fGdprUrl, jsGdprUrl);

    // Base path
    if (this->assignBasePath) {
        jstring jsBasePath = miInit.env->NewStringUTF(this->basePath.c_str());
        jfieldID fBasePath = miInit.env->GetFieldID(clsTestOptions, "basePath", "Ljava/lang/String;");
        miInit.env->SetObjectField(jobjTestOptions, fBasePath, jsBasePath);
    }

    // GDPR path
    if (this->assignGdprPath) {
        jstring jsGdprPath = miInit.env->NewStringUTF(this->gdprPath.c_str());
        jfieldID fGdprPath = miInit.env->GetFieldID(clsTestOptions, "gdprPath", "Ljava/lang/String;");
        miInit.env->SetObjectField(jobjTestOptions, fGdprPath, jsGdprPath);
    }

    // Use test connection options
    if (this->useTestConnectionOptions != NULL) {
        jboolean jbUseTestConnectionOptions = *this->useTestConnectionOptions == true ? JNI_TRUE : JNI_FALSE;
        jobject jobjUseTestConnectionOptions = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbUseTestConnectionOptions);
        jfieldID fUseTestConnectionOptions = miInit.env->GetFieldID(clsTestOptions, "useTestConnectionOptions", "Ljava/lang/Boolean;");
        miInit.env->SetObjectField(jobjTestOptions, fUseTestConnectionOptions, jobjUseTestConnectionOptions);
        miInit.env->DeleteLocalRef(jobjUseTestConnectionOptions);
    }

    // Timer interval in milliseconds
    if (this->timerIntervalInMilliseconds != NULL) {
        jlong jTimerIntervalInMilliseconds = (jlong)(*this->timerIntervalInMilliseconds);
        jobject jobjTimerIntervalInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jTimerIntervalInMilliseconds);
        jfieldID fTimerIntervalInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "timerIntervalInMilliseconds", "Ljava/lang/Long;");
        miInit.env->SetObjectField(jobjTestOptions, fTimerIntervalInMilliseconds, jobjTimerIntervalInMilliseconds);
        miInit.env->DeleteLocalRef(jobjTimerIntervalInMilliseconds);
    }

    // Timer start in milliseconds
    if (this->timerStartInMilliseconds != NULL) {
        jlong jTimerStartInMilliseconds = (jlong)(*this->timerStartInMilliseconds);
        jobject jobjTimerStartInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jTimerStartInMilliseconds);
        jfieldID fTimerStartInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "timerStartInMilliseconds", "Ljava/lang/Long;");
        miInit.env->SetObjectField(jobjTestOptions, fTimerStartInMilliseconds, jobjTimerStartInMilliseconds);
        miInit.env->DeleteLocalRef(jobjTimerStartInMilliseconds);
    }

    // Session interval in milliseconds
    if (this->sessionIntervalInMilliseconds != NULL) {
        jlong jSessionIntervalInMilliseconds = (jlong)(*this->sessionIntervalInMilliseconds);
        jobject jobjSessionIntervalInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jSessionIntervalInMilliseconds);
        jfieldID fSessionIntervalInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "sessionIntervalInMilliseconds", "Ljava/lang/Long;");
        miInit.env->SetObjectField(jobjTestOptions, fSessionIntervalInMilliseconds, jobjSessionIntervalInMilliseconds);
        miInit.env->DeleteLocalRef(jobjSessionIntervalInMilliseconds);
    }

    // Sub-session interval in milliseconds
    if (this->subsessionIntervalInMilliseconds != NULL) {
        jlong jSubsessionIntervalInMilliseconds = (jlong)(*this->subsessionIntervalInMilliseconds);
        jobject jobjSubsessionIntervalInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jSubsessionIntervalInMilliseconds);
        jfieldID fSubsessionIntervalInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "subsessionIntervalInMilliseconds", "Ljava/lang/Long;");
        miInit.env->SetObjectField(jobjTestOptions, fSubsessionIntervalInMilliseconds, jobjSubsessionIntervalInMilliseconds);
        miInit.env->DeleteLocalRef(jobjSubsessionIntervalInMilliseconds);
    }

    // Teardown
    if (this->teardown != NULL) {
        jboolean jbTeardown = *this->teardown == true ? JNI_TRUE : JNI_FALSE;
        jobject jobjTeardown = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbTeardown);
        jfieldID fTeardown = miInit.env->GetFieldID(clsTestOptions, "teardown", "Ljava/lang/Boolean;");
        miInit.env->SetObjectField(jobjTestOptions, fTeardown, jobjTeardown);
        miInit.env->DeleteLocalRef(jobjTeardown);
    }

    // Try install referrer
    if (this->tryInstallReferrer != NULL) {
        jboolean jbTryInstallReferrer = *this->tryInstallReferrer == true ? JNI_TRUE : JNI_FALSE;
        jobject jobjTryInstallReferrer = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbTryInstallReferrer);
        jfieldID fTryInstallReferrer = miInit.env->GetFieldID(clsTestOptions, "tryInstallReferrer", "Ljava/lang/Boolean;");
        miInit.env->SetObjectField(jobjTestOptions, fTryInstallReferrer, jobjTryInstallReferrer);
        miInit.env->DeleteLocalRef(jobjTryInstallReferrer);
    }

    // No backoff wait
    if (this->noBackoffWait != NULL) {
        jboolean jbNoBackoffWait = *this->noBackoffWait == true ? JNI_TRUE : JNI_FALSE;
        jobject jobjNoBackoffWait = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbNoBackoffWait);
        jfieldID fNoBackoffWait = miInit.env->GetFieldID(clsTestOptions, "noBackoffWait", "Ljava/lang/Boolean;");
        miInit.env->SetObjectField(jobjTestOptions, fNoBackoffWait, jobjNoBackoffWait);
        miInit.env->DeleteLocalRef(jobjNoBackoffWait);
    }

    return jobjTestOptions;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void* AdjustTestOptions2dx::getTestOptions() {
    ATLAdjustTestOptions2dx *testOptions = new ATLAdjustTestOptions2dx();
    testOptions->setBaseUrl(this->baseUrl);
    testOptions->setGdprUrl(this->gdprUrl);

    // Base path
    if (this->assignBasePath) {
        testOptions->setBasePath(this->basePath);
    }

    // GDPR path
    if (this->assignGdprPath) {
        testOptions->setGdprPath(this->gdprPath);
    }

    // Timer interval in milliseconds
    if (this->timerIntervalInMilliseconds != NULL) {
        testOptions->setTimerIntervalInMilliseconds(*this->timerIntervalInMilliseconds);
    }

    // Timer start in milliseconds
    if (this->timerStartInMilliseconds != NULL) {
        testOptions->setTimerStartInMilliseconds(*this->timerStartInMilliseconds);
    }

    // Session interval in milliseconds
    if (this->sessionIntervalInMilliseconds != NULL) {
        testOptions->setSessionIntervalInMilliseconds(*this->sessionIntervalInMilliseconds);
    }

    // Sub-session interval in milliseconds
    if (this->subsessionIntervalInMilliseconds != NULL) {
        testOptions->setSubsessionIntervalInMilliseconds(*this->subsessionIntervalInMilliseconds);
    }

    // Teardown
    if (this->teardown != NULL) {
        testOptions->setTeardown(*this->teardown);
    }

    // Delete state
    if (this->deleteState != NULL) {
        testOptions->setDeleteState(*this->deleteState);
    }

    // No backoff wait
    if (this->noBackoffWait != NULL) {
        testOptions->setNoBackoffWait(*this->noBackoffWait);
    }

    // iAd framework enabled
    if (this->iAdFrameworkEnabled != NULL) {
        testOptions->setIAdFrameworkEnabled(*this->iAdFrameworkEnabled);
    }

    return (void*)testOptions;
}
#endif