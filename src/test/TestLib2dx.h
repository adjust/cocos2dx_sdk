//
//  TestLib2dx.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 29th June 2018.
//  Copyright © 2018 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_TESTLIB2DX_H_
#define ADJUST_TESTLIB2DX_H_

#include <iostream>

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
