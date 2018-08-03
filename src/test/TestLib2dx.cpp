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
    //std::cout << "TestLib2dx Object is being created and initialized..." << std::endl;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    setExecuteTestLibCommandCallbackMethod(executeCommandCallback);

    cocos2d::JniMethodInfo miInit;
    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/testlibrary/TestLibrary", "<init>", "(Ljava/lang/String;Lcom/adjust/testlibrary/ICommandJsonListener;)V")) {
        return;
    }

    jclass clsTestLibrary = miInit.env->FindClass("com/adjust/testlibrary/TestLibrary");
    jmethodID midInit = miInit.env->GetMethodID(clsTestLibrary, "<init>", "(Ljava/lang/String;Lcom/adjust/testlibrary/ICommandJsonListener;)V");
    
    // Base URL
    jstring jBaseUrl = miInit.env->NewStringUTF(baseUrl.c_str());

    // Command listener
    cocos2d::JniMethodInfo miInitCommJsonListener;
    if (!cocos2d::JniHelper::getMethodInfo(miInitCommJsonListener, "com/adjust/testlibrary/Adjust2dxCommandJsonListenerCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxCommandJsonListenerCallback = miInitCommJsonListener.env->FindClass("com/adjust/testlibrary/Adjust2dxCommandJsonListenerCallback");
    jmethodID midInitCommJsonListener = miInitCommJsonListener.env->GetMethodID(clsAdjust2dxCommandJsonListenerCallback, "<init>", "()V");
    jobject jCommListenerCallbackProxy = miInitCommJsonListener.env->NewObject(clsAdjust2dxCommandJsonListenerCallback, midInitCommJsonListener);

    // Initialise test library
    jobject jobjTestLib = miInit.env->NewObject(clsTestLibrary, midInit, jBaseUrl, jCommListenerCallbackProxy);
    testLibrary = cocos2d::JniHelper::getEnv()->NewGlobalRef(jobjTestLib);

    miInit.env->DeleteLocalRef(jBaseUrl);
    miInit.env->DeleteLocalRef(jCommListenerCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary = ATLTestLibrary2dx(baseUrl, executeCommandCallback);
#endif
}

void TestLib2dx::addTest(std::string testName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo miAddTest;
    if (!cocos2d::JniHelper::getMethodInfo(miAddTest, "com/adjust/testlibrary/TestLibrary", "addTest", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTestName = miAddTest.env->NewStringUTF(testName.c_str());
    miAddTest.env->CallVoidMethod(testLibrary, miAddTest.methodID, jTestName);
    miAddTest.env->DeleteLocalRef(jTestName);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.addTest(testName);
#endif
}

void TestLib2dx::addTestDirectory(std::string testDirectory) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo miAddTestDir;
    if (!cocos2d::JniHelper::getMethodInfo(miAddTestDir, "com/adjust/testlibrary/TestLibrary", "addTestDirectory", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jTestDir = miAddTestDir.env->NewStringUTF(testDirectory.c_str());
    miAddTestDir.env->CallVoidMethod(testLibrary, miAddTestDir.methodID, jTestDir);
    miAddTestDir.env->DeleteLocalRef(jTestDir);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.addTestDirectory(testDirectory);
#endif
}

void TestLib2dx::startTestSession(std::string clientSdk) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo miStartTestSession;
    if (!cocos2d::JniHelper::getMethodInfo(miStartTestSession, "com/adjust/testlibrary/TestLibrary", "startTestSession", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jClientSdk = miStartTestSession.env->NewStringUTF(clientSdk.c_str());
    miStartTestSession.env->CallVoidMethod(testLibrary, miStartTestSession.methodID, jClientSdk);
    miStartTestSession.env->DeleteLocalRef(jClientSdk);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.startTestSession(clientSdk);
#endif
}

void TestLib2dx::addInfoToSend(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo miAddInfoToSend;
    if (!cocos2d::JniHelper::getMethodInfo(miAddInfoToSend, "com/adjust/testlibrary/TestLibrary", "addInfoToSend", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jstring jKey = miAddInfoToSend.env->NewStringUTF(key.c_str());
    jstring jValue = miAddInfoToSend.env->NewStringUTF(value.c_str());
    miAddInfoToSend.env->CallVoidMethod(testLibrary, miAddInfoToSend.methodID, jKey, jValue);
    miAddInfoToSend.env->DeleteLocalRef(jKey);
    miAddInfoToSend.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.addInfoToSend(key, value);
#endif    
}

void TestLib2dx::sendInfoToServer(std::string basePath) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (testLibrary == NULL) {
        return;
    }
    cocos2d::JniMethodInfo miSendInfoToServer;
    if (!cocos2d::JniHelper::getMethodInfo(miSendInfoToServer, "com/adjust/testlibrary/TestLibrary", "sendInfoToServer", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring jBasePath = miSendInfoToServer.env->NewStringUTF(basePath.c_str());
    miSendInfoToServer.env->CallVoidMethod(testLibrary, miSendInfoToServer.methodID, jBasePath);
    miSendInfoToServer.env->DeleteLocalRef(jBasePath);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    testlibrary.sendInfoToServer(basePath);
#endif
}