//
//  AdjustTestOptions2dx.h
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#ifndef ADJUST_TESTOPTIONS2DX_H_
#define ADJUST_TESTOPTIONS2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdjustTesting/ATLAdjustTestOptions2dx.h"
#endif

#include <iostream>

class AdjustTestOptions2dx {
public:
    std::string baseUrl;
    std::string gdprUrl;
    std::string basePath;
    std::string gdprPath;
    bool assignBasePath = false;
    bool assignGdprPath = false;
    long *timerIntervalInMilliseconds = NULL;
    long *timerStartInMilliseconds = NULL;
    long *sessionIntervalInMilliseconds = NULL;
    long *subsessionIntervalInMilliseconds = NULL;
    bool *teardown = NULL;
    bool *noBackoffWait = NULL;

    // android specific
    bool *setContext = NULL;
    bool *tryInstallReferrer = NULL;
    bool *useTestConnectionOptions = NULL;

    // ios specific
    bool *iAdFrameworkEnabled = NULL;
    bool *deleteState = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getTestOptions();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ATLAdjustTestOptions2dx getTestOptions();
#endif
};

#endif /* ADJUST_TESTOPTIONS2DX_H_ */
