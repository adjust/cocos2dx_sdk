//
//  AdjustConfig2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#ifndef ADJUST_ADJUSTCONFIG2DX_H_
#define ADJUST_ADJUSTCONFIG2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJConfig2dx.h"
#endif

#include <iostream>
#include "AdjustAttribution2dx.h"

enum AdjustLogLevel2dx {
    AdjustLogLevel2dxVerbose = 1,
	AdjustLogLevel2dxDebug   = 2,
	AdjustLogLevel2dxInfo    = 3,
	AdjustLogLevel2dxWarn    = 4,
	AdjustLogLevel2dxError   = 5,
	AdjustLogLevel2dxAssert  = 6 };

class AdjustConfig2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject config;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJConfig2dx config;
    bool isConfigSet;
#endif
    void initConfig(std::string appToken, std::string environment);

public:
    AdjustConfig2dx() {}
    AdjustConfig2dx(std::string appToken, std::string environment) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initConfig(appToken, environment);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isConfigSet = true;
        initConfig(appToken, environment);
#endif
    }

    void setEventBufferingEnabled(bool isEnabled);
    void setLogLevel(AdjustLogLevel2dx logLevel);
    void setDefaultTracker(std::string defaultTracker);
    void setAttributionCallback(void (*callbackMethod)(AdjustAttribution2dx attribution));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getConfig();
    void setProcessName(std::string processName);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJConfig2dx getConfig();
    void setMacMd5TrackingEnabled(bool isEnabled);
#endif
};

#endif /* ADJUST_ADJUSTCONFIG2DX_H_ */
