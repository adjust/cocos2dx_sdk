//
//  AdjustTestOptions2dx.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_TESTOPTIONS2DX_H_
#define ADJUST_TESTOPTIONS2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#endif

#include <iostream>

class AdjustTestOptions2dx {
public:
    std::string baseUrl;
    std::string gdprUrl;
    std::string basePath;
    std::string gdprPath;
    long *timerIntervalInMilliseconds = NULL;
    long *timerStartInMilliseconds = NULL;
    long *sessionIntervalInMilliseconds = NULL;
    long *subsessionIntervalInMilliseconds = NULL;
    bool *teardown = NULL;
    bool *noBackoffWait = NULL;
    bool assignBasePath = false;
    bool assignGdprPath = false;

    // Android specific
    bool *setContext = NULL;
    bool *tryInstallReferrer = NULL;
    bool *useTestConnectionOptions = NULL;

    // iOS specific
    bool *iAdFrameworkEnabled = NULL;
    bool *deleteState = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getTestOptions();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void* getTestOptions();
#endif
};

#endif /* ADJUST_TESTOPTIONS2DX_H_ */
