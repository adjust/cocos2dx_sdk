//
//  TestLib2dx.h
//  Adjust SDK Test Library Wrapper
//
//  Created by Srdjan Tubin on 29/06/18.
//

#ifndef ADJUST_TESTLIB2DX_H_
#define ADJUST_TESTLIB2DX_H_

#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif

class TestLib2dx {
private:
    void initTestLibrary(std::string baseUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters));

public:
    TestLib2dx(std::string baseUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters)) {
        initTestLibrary(baseUrl, executeCommandCallback);
    }

    void addTest(std::string testName);
    void addTestDirectory(std::string testDirectory);
    void startTestSession(std::string clientSdk);
    static void addInfoToSend(std::string key, std::string value);
    static void sendInfoToServer(std::string basePath);
};

#endif /* ADJUST_TESTLIB2DX_H_ */