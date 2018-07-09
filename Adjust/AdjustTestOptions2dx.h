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

#endif

#include <iostream>

class AdjustTestOptions2dx {
public:
    bool setContext;
    std::string baseUrl;
    std::string gdprUrl;
    std::string basePath;
    std::string gdprPath;
    bool useTestConnectionOptions;
    long timerIntervalInMilliseconds;
    long timerStartInMilliseconds;
    long sessionIntervalInMilliseconds;
    long subsessionIntervalInMilliseconds;
    bool teardown;
    bool tryInstallReferrer;
    bool noBackoffWait;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getTestOptions();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
};

#endif /* ADJUST_TESTOPTIONS2DX_H_ */
