//
//  TestLib2dx.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 29th June 2018.
//  Copyright © 2018 Adjust GmbH. All rights reserved.
//

#include "TestLib2dx.h"

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
static ATLTestLibrary2dx testlibrary;
#endif

void TestLib2dx::initTestLibrary(std::string baseUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setExecuteTestLibCommandCallbackMethod(executeCommandCallback);

    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/testlibrary/TestLibrary", "<init>", "(Ljava/lang/String;Lcom/adjust/testlibrary/ICommandJsonListener;)V")) {
        return;
    }

    jclass jclsTestLibrary = jmiInit.env->FindClass("com/adjust/testlibrary/TestLibrary");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsTestLibrary, "<init>", "(Ljava/lang/String;Lcom/adjust/testlibrary/ICommandJsonListener;)V");
    // Base URL.
    jstring jBaseUrl = jmiInit.env->NewStringUTF(baseUrl.c_str());
    // Command listener.
    cocos2d::JniMethodInfo jmiInitCommJsonListener;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInitCommJsonListener, "com/adjust/testlibrary/Adjust2dxCommandJsonListenerCallback", "<init>", "()V")) {
        return;
    }

    jclass jclsAdjust2dxCommandJsonListenerCallback = jmiInitCommJsonListener.env->FindClass("com/adjust/testlibrary/Adjust2dxCommandJsonListenerCallback");
    jmethodID jmidInitCommJsonListener = jmiInitCommJsonListener.env->GetMethodID(jclsAdjust2dxCommandJsonListenerCallback, "<init>", "()V");
    jobject jCommListenerCallbackProxy = jmiInitCommJsonListener.env->NewObject(jclsAdjust2dxCommandJsonListenerCallback, jmidInitCommJsonListener);

    // Initialise test library
    jobject jTestLib = jmiInit.env->NewObject(jclsTestLibrary, jmidInit, jBaseUrl, jCommListenerCallbackProxy);
    testLibrary = cocos2d::JniHelper::getEnv()->NewGlobalRef(jTestLib);

    jmiInit.env->DeleteLocalRef(jBaseUrl);
    jmiInit.env->DeleteLocalRef(jCommListenerCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary = ATLTestLibrary2dx(baseUrl, executeCommandCallback);
#endif
}

void TestLib2dx::addTest(std::string testName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddTest;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddTest, "com/adjust/testlibrary/TestLibrary", "addTest", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTestName = jmiAddTest.env->NewStringUTF(testName.c_str());
    jmiAddTest.env->CallVoidMethod(testLibrary, jmiAddTest.methodID, jTestName);
    jmiAddTest.env->DeleteLocalRef(jTestName);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.addTest(testName);
#endif
}

void TestLib2dx::addTestDirectory(std::string testDirectory) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddTestDir;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddTestDir, "com/adjust/testlibrary/TestLibrary", "addTestDirectory", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTestDir = jmiAddTestDir.env->NewStringUTF(testDirectory.c_str());
    jmiAddTestDir.env->CallVoidMethod(testLibrary, jmiAddTestDir.methodID, jTestDir);
    jmiAddTestDir.env->DeleteLocalRef(jTestDir);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.addTestDirectory(testDirectory);
#endif
}

void TestLib2dx::startTestSession(std::string clientSdk) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiStartTestSession;
    if (!cocos2d::JniHelper::getMethodInfo(jmiStartTestSession, "com/adjust/testlibrary/TestLibrary", "startTestSession", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jClientSdk = jmiStartTestSession.env->NewStringUTF(clientSdk.c_str());
    jmiStartTestSession.env->CallVoidMethod(testLibrary, jmiStartTestSession.methodID, jClientSdk);
    jmiStartTestSession.env->DeleteLocalRef(jClientSdk);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.startTestSession(clientSdk);
#endif
}

void TestLib2dx::addInfoToSend(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiAddInfoToSend;
    if (!cocos2d::JniHelper::getMethodInfo(jmiAddInfoToSend, "com/adjust/testlibrary/TestLibrary", "addInfoToSend", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = jmiAddInfoToSend.env->NewStringUTF(key.c_str());
    jstring jValue = jmiAddInfoToSend.env->NewStringUTF(value.c_str());
    jmiAddInfoToSend.env->CallVoidMethod(testLibrary, jmiAddInfoToSend.methodID, jKey, jValue);
    jmiAddInfoToSend.env->DeleteLocalRef(jKey);
    jmiAddInfoToSend.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.addInfoToSend(key, value);
#endif    
}

void TestLib2dx::sendInfoToServer(std::string basePath) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo jmiSendInfoToServer;
    if (!cocos2d::JniHelper::getMethodInfo(jmiSendInfoToServer, "com/adjust/testlibrary/TestLibrary", "sendInfoToServer", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jBasePath = jmiSendInfoToServer.env->NewStringUTF(basePath.c_str());
    jmiSendInfoToServer.env->CallVoidMethod(testLibrary, jmiSendInfoToServer.methodID, jBasePath);
    jmiSendInfoToServer.env->DeleteLocalRef(jBasePath);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.sendInfoToServer(basePath);
#endif
}