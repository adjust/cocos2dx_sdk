//
//  TestLib2dx.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 29th June 2018.
//  Copyright © 2018-Present Adjust GmbH. All rights reserved.
//

#include "TestLib2dx.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <Adjust/AdjustProxy2dx.h>
#include "platform/android/jni/JniHelper.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ATLTestLibrary2dx.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static jobject testLibrary;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static ATLTestLibrary2dx testLibrary;
#endif

void TestLib2dx::initTestLibrary(std::string baseUrl, std::string controlUrl, void(*callback)(std::string className, std::string methodName, std::string jsonParameters)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setExecuteTestLibCommandCallbackMethod(callback);

    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/test/TestLibrary", "<init>", "(Ljava/lang/String;Ljava/lang/String;Landroid/content/Context;Lcom/adjust/test/ICommandJsonListener;)V")) {
        return;
    }

    cocos2d::JniMethodInfo jmiGetContext;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;")) {
        return;
    }

    jclass jclsTestLibrary = jmiInit.env->FindClass("com/adjust/test/TestLibrary");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsTestLibrary, "<init>", "(Ljava/lang/String;Ljava/lang/String;Landroid/content/Context;Lcom/adjust/test/ICommandJsonListener;)V");
    // Base URL.
    jstring jBaseUrl = jmiInit.env->NewStringUTF(baseUrl.c_str());
    // Control URL.
    jstring jControlUrl = jmiInit.env->NewStringUTF(controlUrl.c_str());
    // Command listener.
    cocos2d::JniMethodInfo jmiInitCommJsonListener;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInitCommJsonListener, "com/adjust/test/Adjust2dxCommandJsonListenerCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxCommandJsonListenerCallback = jmiInitCommJsonListener.env->FindClass("com/adjust/test/Adjust2dxCommandJsonListenerCallback");
    jmethodID jmidInitCommJsonListener = jmiInitCommJsonListener.env->GetMethodID(jclsAdjust2dxCommandJsonListenerCallback, "<init>", "()V");
    jobject jCommListenerCallbackProxy = jmiInitCommJsonListener.env->NewObject(jclsAdjust2dxCommandJsonListenerCallback, jmidInitCommJsonListener);

    jobject jContext = (jobject)jmiGetContext.env->CallStaticObjectMethod(jmiGetContext.classID, jmiGetContext.methodID);

    // Initialise test library
    jobject jTestLib = jmiInit.env->NewObject(jclsTestLibrary, jmidInit, jBaseUrl, jControlUrl, jContext, jCommListenerCallbackProxy);
    testLibrary = cocos2d::JniHelper::getEnv()->NewGlobalRef(jTestLib);

    jmiGetContext.env->DeleteLocalRef(jContext);
    jmiInit.env->DeleteLocalRef(jBaseUrl);
    jmiInit.env->DeleteLocalRef(jControlUrl);
    jmiInit.env->DeleteLocalRef(jCommListenerCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary = ATLTestLibrary2dx(baseUrl, controlUrl, callback);
#endif
}

void TestLib2dx::addTest(std::string testName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddTest;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddTest, "com/adjust/test/TestLibrary", "addTest", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTestName = jmiAddTest.env->NewStringUTF(testName.c_str());
    jmiAddTest.env->CallVoidMethod(testLibrary, jmiAddTest.methodID, jTestName);
    jmiAddTest.env->DeleteLocalRef(jTestName);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary.addTest(testName);
#endif
}

void TestLib2dx::addTestDirectory(std::string testDirectory) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddTestDir;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddTestDir, "com/adjust/test/TestLibrary", "addTestDirectory", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTestDir = jmiAddTestDir.env->NewStringUTF(testDirectory.c_str());
    jmiAddTestDir.env->CallVoidMethod(testLibrary, jmiAddTestDir.methodID, jTestDir);
    jmiAddTestDir.env->DeleteLocalRef(jTestDir);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary.addTestDirectory(testDirectory);
#endif
}

void TestLib2dx::startTestSession(std::string clientSdk) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiStartTestSession;
    if (!cocos2d::JniHelper::getMethodInfo(jmiStartTestSession, "com/adjust/test/TestLibrary", "startTestSession", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jClientSdk = jmiStartTestSession.env->NewStringUTF(clientSdk.c_str());
    jmiStartTestSession.env->CallVoidMethod(testLibrary, jmiStartTestSession.methodID, jClientSdk);
    jmiStartTestSession.env->DeleteLocalRef(jClientSdk);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary.startTestSession(clientSdk);
#endif
}

void TestLib2dx::addInfoToSend(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddInfoToSend;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddInfoToSend, "com/adjust/test/TestLibrary", "addInfoToSend", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddInfoToSend.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddInfoToSend.env->NewStringUTF(value.c_str());
    jmiAddInfoToSend.env->CallVoidMethod(testLibrary, jmiAddInfoToSend.methodID, jKey, jValue);
    jmiAddInfoToSend.env->DeleteLocalRef(jKey);
    jmiAddInfoToSend.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary.addInfoToSend(key, value);
#endif    
}

void TestLib2dx::sendInfoToServer(std::string basePath) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSendInfoToServer;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSendInfoToServer, "com/adjust/test/TestLibrary", "sendInfoToServer", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jBasePath = jmiSendInfoToServer.env->NewStringUTF(basePath.c_str());
    jmiSendInfoToServer.env->CallVoidMethod(testLibrary, jmiSendInfoToServer.methodID, jBasePath);
    jmiSendInfoToServer.env->DeleteLocalRef(jBasePath);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testLibrary.sendInfoToServer(basePath);
#endif
}
