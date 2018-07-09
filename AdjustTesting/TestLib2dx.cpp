//
//  TestLib2dx.cpp
//  Adjust SDK Test Library Wrapper
//
//  Created by Srdjan Tubin on 29/06/18.
//

#include "TestLib2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif

// using namespace std;

void TestLib2dx::initTestLibrary(std::string baseUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters)) {
    std::cout << "TestLib2dx Object is being created and initialized..." << std::endl;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	setExecuteTestLibCommandCallbackMethod(executeCommandCallback);

	//public TestLibrary(String baseUrl, ICommandJsonListener commandJsonListener)
	cocos2d::JniMethodInfo miInit;
    if (!cocos2d::JniHelper::getMethodInfo(miInit, "com/adjust/testlibrary/TestLibrary", "<init>", "(Ljava/lang/String;Lcom/adjust/testlibrary/ICommandJsonListener;)V")) {
        return;
    }

    jclass clsTestLibrary = miInit.env->FindClass("com/adjust/testlibrary/TestLibrary");
    jmethodID midInit = miInit.env->GetMethodID(clsTestLibrary, "<init>", "(Ljava/lang/String;Lcom/adjust/testlibrary/ICommandJsonListener;)V");
    
    // baseUrl
    jstring jBaseUrl = miInit.env->NewStringUTF(baseUrl.c_str());

    // command listener
    cocos2d::JniMethodInfo miInitCommJsonListener;
    if (!cocos2d::JniHelper::getMethodInfo(miInitCommJsonListener, "com/adjust/testlibrary/Adjust2dxCommandJsonListenerCallback", "<init>", "()V")) {
        return;
    }

    jclass clsAdjust2dxCommandJsonListenerCallback = miInitCommJsonListener.env->FindClass("com/adjust/testlibrary/Adjust2dxCommandJsonListenerCallback");
    jmethodID midInitCommJsonListener = miInitCommJsonListener.env->GetMethodID(clsAdjust2dxCommandJsonListenerCallback, "<init>", "()V");
    jobject jCommListenerCallbackProxy = miInitCommJsonListener.env->NewObject(clsAdjust2dxCommandJsonListenerCallback, midInitCommJsonListener);

    // tet library init
    testLibrary = miInit.env->NewObject(clsTestLibrary, midInit, jBaseUrl, jCommListenerCallbackProxy);

    miInit.env->DeleteLocalRef(jBaseUrl);
    miInit.env->DeleteLocalRef(jCommListenerCallbackProxy);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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
    miAddTestDir.env->CallVoidMethod(testLibrary, miStartTestSession.methodID, jClientSdk);
    miAddTestDir.env->DeleteLocalRef(jClientSdk);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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
    miAddTestDir.env->CallVoidMethod(testLibrary, miAddInfoToSend.methodID, jKey, jValue);
    miAddTestDir.env->DeleteLocalRef(jKey);
    miAddTestDir.env->DeleteLocalRef(jValue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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
    miAddTestDir.env->CallVoidMethod(testLibrary, miSendInfoToServer.methodID, jBasePath);
    miAddTestDir.env->DeleteLocalRef(jBasePath);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}