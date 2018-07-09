//
//  AdjustTestOptions2dx.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#include "AdjustTestOptions2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
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

    // TEST OPTIONS JAVA OBJECT ////////////////////////////////////////////////////////////////////////////////
    jclass clsTestOptions = miInit.env->FindClass("com/adjust/sdk/AdjustTestOptions");
    jmethodID midInit = miInit.env->GetMethodID(clsTestOptions, "<init>", "()V");
    jobject jobjTestOptions = miInit.env->NewObject(clsTestOptions, midInit);

    // context ////////////////////////////////////////////////////////////////////////////////
    if (this->setContext == true) {
        jfieldID fContext = miInit.env->GetFieldID(clsTestOptions, "context", "Landroid/content/Context;");
        miInit.env->SetObjectField(jobjTestOptions, fContext, jContext);
    }
    miGetContext.env->DeleteLocalRef(jContext);

    // base url ////////////////////////////////////////////////////////////////////////////////
    jstring jsBaseUrl = miInit.env->NewStringUTF(this->baseUrl.c_str());
    jfieldID fBaseUrl = miInit.env->GetFieldID(clsTestOptions, "baseUrl", "Ljava/lang/String;");
    miInit.env->SetObjectField(jobjTestOptions, fBaseUrl, jsBaseUrl);

    // gdpr url ////////////////////////////////////////////////////////////////////////////////
    jstring jsGdprUrl = miInit.env->NewStringUTF(this->gdprUrl.c_str());
    jfieldID fGdprUrl = miInit.env->GetFieldID(clsTestOptions, "gdprUrl", "Ljava/lang/String;");
    miInit.env->SetObjectField(jobjTestOptions, fGdprUrl, jsGdprUrl);

    // base path ////////////////////////////////////////////////////////////////////////////////
    jstring jsBasePath = miInit.env->NewStringUTF(this->basePath.c_str());
    jfieldID fBasePath = miInit.env->GetFieldID(clsTestOptions, "basePath", "Ljava/lang/String;");
    miInit.env->SetObjectField(jobjTestOptions, fBasePath, jsBasePath);

    // gdpr path ////////////////////////////////////////////////////////////////////////////////
    jstring jsGdprPath = miInit.env->NewStringUTF(this->gdprPath.c_str());
    jfieldID fGdprPath = miInit.env->GetFieldID(clsTestOptions, "gdprPath", "Ljava/lang/String;");
    miInit.env->SetObjectField(jobjTestOptions, fGdprPath, jsGdprPath);

    // useTestConnectionOptions ////////////////////////////////////////////////////////////////////////////////
    jboolean jbUseTestConnectionOptions = this->useTestConnectionOptions == true ? JNI_TRUE : JNI_FALSE; 
    jobject jobjUseTestConnectionOptions = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbUseTestConnectionOptions);
    jfieldID fUseTestConnectionOptions = miInit.env->GetFieldID(clsTestOptions, "useTestConnectionOptions", "Ljava/lang/Boolean;");
    miInit.env->SetObjectField(jobjTestOptions, fUseTestConnectionOptions, jobjUseTestConnectionOptions);
    miInit.env->DeleteLocalRef(jobjUseTestConnectionOptions);

    // timerIntervalInMilliseconds ////////////////////////////////////////////////////////////////////////////////
    jlong jTimerIntervalInMilliseconds = (jlong)this->timerIntervalInMilliseconds;
    jobject jobjTimerIntervalInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jTimerIntervalInMilliseconds);
    jfieldID fTimerIntervalInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "timerIntervalInMilliseconds", "Ljava/lang/Long;");
    miInit.env->SetObjectField(jobjTestOptions, fTimerIntervalInMilliseconds, jobjTimerIntervalInMilliseconds);
    miInit.env->DeleteLocalRef(jobjTimerIntervalInMilliseconds);

    // timerStartInMilliseconds ////////////////////////////////////////////////////////////////////////////////
    jlong jTimerStartInMilliseconds = (jlong)this->timerStartInMilliseconds;
    jobject jobjTimerStartInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jTimerStartInMilliseconds);
    jfieldID fTimerStartInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "timerStartInMilliseconds", "Ljava/lang/Long;");
    miInit.env->SetObjectField(jobjTestOptions, fTimerStartInMilliseconds, jobjTimerStartInMilliseconds);
    miInit.env->DeleteLocalRef(jobjTimerStartInMilliseconds);

    // sessionIntervalInMilliseconds ////////////////////////////////////////////////////////////////////////////////
    jlong jSessionIntervalInMilliseconds = (jlong)this->sessionIntervalInMilliseconds;
    jobject jobjSessionIntervalInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jSessionIntervalInMilliseconds);
    jfieldID fSessionIntervalInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "sessionIntervalInMilliseconds", "Ljava/lang/Long;");
    miInit.env->SetObjectField(jobjTestOptions, fSessionIntervalInMilliseconds, jobjSessionIntervalInMilliseconds);
    miInit.env->DeleteLocalRef(jobjSessionIntervalInMilliseconds);

    // subsessionIntervalInMilliseconds ////////////////////////////////////////////////////////////////////////////////
    jlong jSubsessionIntervalInMilliseconds = (jlong)this->subsessionIntervalInMilliseconds;
    jobject jobjSubsessionIntervalInMilliseconds = miInitLong.env->NewObject(clsLong, midInitLong, jSubsessionIntervalInMilliseconds);
    jfieldID fSubsessionIntervalInMilliseconds = miInit.env->GetFieldID(clsTestOptions, "subsessionIntervalInMilliseconds", "Ljava/lang/Long;");
    miInit.env->SetObjectField(jobjTestOptions, fSubsessionIntervalInMilliseconds, jobjSubsessionIntervalInMilliseconds);
    miInit.env->DeleteLocalRef(jobjSubsessionIntervalInMilliseconds);

    // teardown ////////////////////////////////////////////////////////////////////////////////
    jboolean jbTeardown = this->teardown == true ? JNI_TRUE : JNI_FALSE;
    jobject jobjTeardown = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbTeardown);
    jfieldID fTeardown = miInit.env->GetFieldID(clsTestOptions, "teardown", "Ljava/lang/Boolean;");
    miInit.env->SetObjectField(jobjTestOptions, fTeardown, jobjTeardown);
    miInit.env->DeleteLocalRef(jobjTeardown);

    // tryInstallReferrer ////////////////////////////////////////////////////////////////////////////////
    jboolean jbTryInstallReferrer = this->tryInstallReferrer == true ? JNI_TRUE : JNI_FALSE;
    jobject jobjTryInstallReferrer = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbTryInstallReferrer);
    jfieldID fTryInstallReferrer = miInit.env->GetFieldID(clsTestOptions, "tryInstallReferrer", "Ljava/lang/Boolean;");
    miInit.env->SetObjectField(jobjTestOptions, fTryInstallReferrer, jobjTryInstallReferrer);
    miInit.env->DeleteLocalRef(jobjTryInstallReferrer);

    // noBackoffWait ////////////////////////////////////////////////////////////////////////////////
    jboolean jbNoBackoffWait = this->noBackoffWait == true ? JNI_TRUE : JNI_FALSE;
    jobject jobjNoBackoffWait = miInitBoolean.env->NewObject(clsBoolean, midInitBoolean, jbNoBackoffWait);
    jfieldID fNoBackoffWait = miInit.env->GetFieldID(clsTestOptions, "noBackoffWait", "Ljava/lang/Boolean;");
    miInit.env->SetObjectField(jobjTestOptions, fNoBackoffWait, jobjNoBackoffWait);
    miInit.env->DeleteLocalRef(jobjNoBackoffWait);
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJAdjustTestOptions2dx AdjustTestOptions2dx::getTestOptions() {

}
#endif